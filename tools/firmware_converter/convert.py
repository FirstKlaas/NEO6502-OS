

if __name__ == "__main__":

    number_of_bytes = 0

    with open('../asm/kernal.prg', 'rb') as file:
        with open('kernal.cpp', 'w') as out:
            out.write('#include <Arduino.h>\n\n\n')
            base_address = file.read(2) # Skip the first two bytes
            
            out.write(f"uint8_t kernal_start_l(0x{format(base_address[0], '02x')});\n")
            out.write(f"uint8_t kernal_start_h(0x{format(base_address[1], '02x')});\n\n")
            
            out.write("uint8_t kernal_bin[] = {\n")
            
            while True:
                chunk = file.read(16)
                if not chunk:
                    out.write("    0x00\n}\n")
                    break
                else:
                    number_of_bytes = number_of_bytes + len(chunk) 
                    res = ''.join(f"0x{format(x, '02x')}, " for x in chunk)
                    out.write("    "+res+'\n')
            out.write(f"\nuint8_t kernal_size({number_of_bytes})\n)")
