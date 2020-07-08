#!/usr/bin/env python3
import sys

def parse_file(input_path, output_path):
    with open(input_path, "r") as input_file:
        with open(output_path, "w") as output_file:
            output_enabled = False
            for line in input_file:
                if line == "{\n":
                    output_enabled = True
                if line == "}\n":
                    output_enabled = False
                    output_file.write(line)
                if output_enabled:
                    output_file.write(line)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Uso: {} <archivo.log> <salida.supp>".format(__FILE__))
    else:
        parse_file(sys.argv[1], sys.argv[2])

