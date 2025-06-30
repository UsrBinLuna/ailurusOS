
import sys

if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} fontfile")
    sys.exit(1)

fontfile = sys.argv[1]

with open(fontfile, "rb") as f:
    data = f.read()

glyph_size = 16
num_glyphs = len(data) // glyph_size

print(f"// Converted font data: {num_glyphs} glyphs, {glyph_size} bytes each\n")
print("const unsigned char font[][16] = {")
for i in range(num_glyphs):
    glyph = data[i * glyph_size:(i + 1) * glyph_size]
    print("    {", end="")
    print(", ".join(f"0x{b:02X}" for b in glyph), end="")
    print("},")
print("};")
