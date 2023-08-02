from pathlib import Path


typedef = """
typedef struct {
  uint16_t address;
  uint16_t size;
  uint8_t *data;
} TSegment;
"""


class Segment:
    def __init__(self, prgfile) -> None:
        with prgfile.open(mode="rb") as prg:
            parts = prgfile.name.split(".")
            full_name = parts[0].split("_")
            self.name = (full_name[1]).lower().replace(" ", "_")
            adr = prg.read(2)  # Skip the first two bytes
            self.address = adr[0] + (adr[1] * 256)
            self.data = bytearray()
            while True:
                chunk = prg.read(16)
                if chunk:
                    self.data += chunk
                else:
                    break

    @property
    def size(self):
        return len(self.data)

    def __str__(self):
        return f"{self.name}[{hex(self.address).upper().replace('X','x')}"

    def write_data(self, out):
        out.write(f"// SEGMENT: {self.name} @ 0x{format(self.address, '04x')}\n")

        out.write(f"uint8_t {self.name}_data[] = ")
        out.write("{\n")
        index = 0
        view = memoryview(self.data)
        while True:
            chunk = view[index : index + 16]
            if len(chunk) > 0:
                line = "".join(f"0x{format(x, '02x')}, " for x in chunk)
                out.write(f"    {line}\n")
                index += 16

            if len(chunk) < 16:
                break

        out.write("    0x00 };\n\n")


def create_bin_block(index, outfile, prgfile):
    file_name = prgfile.name
    with prgfile.open(mode="rb") as prg:
        number_of_bytes = 0
        parts = file_name.split(".")
        full_name = parts[0].split("_")
        name = (full_name[1]).lower().replace(" ", "_")
        out.write(f"    // SEGMENT: {name}\n")
        base_address = prg.read(2)  # Skip the first two bytes
        highByte = format(base_address[1], "02X")
        lowByte = format(base_address[0], "02X")
        out.write(f"    segment[{index}].address = 0x{highByte}{lowByte};\n")
        out.write(f"    uint8_t {name}_data[] = ")
        out.write("    {\n")

        while True:
            chunk = prg.read(16)
            if not chunk:
                out.write("        0x00\n    };\n")
                break
            else:
                number_of_bytes = number_of_bytes + len(chunk)
                res = "".join(f"0x{format(x, '02x')}, " for x in chunk)
                out.write("    " + res + "\n")
        out.write(f"    segment[{index}].data = {name}_data;\n")
        out.write(f"    segment[{index}].size = {number_of_bytes};\n\n")


def write_loader_function(out, segments):
    out.write("void load_kernel_to_memory(uint8_t *memory) {\n")
    index = 0
    for segment in segments:
        out.write(
            f"    segment[{index}].address = 0x{format(segment.address, '04x')};\n"
        )
        out.write(f"    segment[{index}].size = {segment.size};\n")
        out.write(f"    segment[{index}].data = {segment.name}_data;\n")
        index = index + 1

    out.write(
        f"""
    for (uint8_t i=0; i<{len(segments)}; i++) {{
        Serial.printf("Loading segment [%02d] at [%04x]. %d bytes", i+1, segment[i].address, segment[i].size);
        // Better use memcpy
        for (uint16_t mem_index=0; i<segment[i].size; mem_index++) {{
            memory[segment[i].address + mem_index] = segment[i].data[mem_index];
        }};
    }};
}}\n
\n"""
    )


if __name__ == "__main__":
    p = Path("../../assembler/")
    with open("kernel.cpp", "w") as out:
        gen_msg = "// THIS FILE IS AUTO GENERATED. DO NOT CHANGE\n//\n\n"
        out.write(gen_msg)
        out.write("#include <pico/stdlib.h>\n")
        out.write("#include <Arduino.h>\n")

        # At this point we do not know how many segments we have
        # So for the sake of ease (and until we reworked the code)
        # We define a fxed number as the maximum
        out.write(typedef)

        segments = [Segment(prg) for prg in p.glob("*.prg*")]

        out.write(f"TSegment segment[{len(segments)}];\n\n")

        for segment in segments:
            segment.write_data(out)

        # Now for the loader function
        write_loader_function(out, segments)
