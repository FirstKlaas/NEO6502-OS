if __name__ == "__main__":
    number_of_bytes = 0

    with open("../../assembler/kernel.prg", "rb") as file:
        with open("kernel.cpp", "w") as out:
            gen_msg = "// THIS FILE IS AUTO GENERATED. DO NOT CHANGE\n//\n\n"
            out.write(gen_msg)

            out.write("#include <Arduino.h>\n")
            out.write('#include "kernel.h"\n\n\n')

            base_address = file.read(2)  # Skip the first two bytes

            highByte = format(base_address[1], "02X")
            lowByte = format(base_address[0], "02X")
            out.write(f"uint16_t kernel_start(0x{highByte}{lowByte});\n\n")

            out.write("uint8_t kernel_data[] = {\n")

            while True:
                chunk = file.read(16)
                if not chunk:
                    out.write("    0x00\n};\n")
                    break
                else:
                    number_of_bytes = number_of_bytes + len(chunk)
                    res = "".join(f"0x{format(x, '02x')}, " for x in chunk)
                    out.write("    " + res + "\n")
            out.write(f"\nuint16_t kernel_size({number_of_bytes});\n")
