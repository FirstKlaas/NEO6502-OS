import json

if __name__ == "__main__":
    with open("color.cpp", "w") as cpp:
        with open("256-colors.json") as f:
            data = json.load(f)
            for color in data:
                rgb = color["rgb"]
                cpp.write(
                    f"display.setColor({color['colorId']}, convertColor565({rgb['r']},{rgb['g']},{rgb['b']}));      // {color['name']}\n"
                )
            cpp.write("\n\n")
            cpp.write("\n\n")

            for color in data:
                s = f"#define {color['name'].upper()}".ljust(30, " ")
                cpp.write(f"{s}0x{format(color['colorId'], '02x')}\n")

            cpp.write("\n\n")
            cpp.write("\n\n")

            for color in data:
                s = f"#define {color['name'].upper()}".ljust(30, " ")
                cpp.write(
                    f"                .const COLOR_{color['name'].upper().ljust(16, ' ')} = ${format(color['colorId'], '02x')}\n"
                )
