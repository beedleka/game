import io
import sys
from PIL import Image

if len(sys.argv) > 2:
    try:
        img = Image.open(sys.argv[1])
        output = open(sys.argv[2], "wb")
        width = img.width.to_bytes(4, byteorder="big")
        height = img.height.to_bytes(4, byteorder="big")
        depth = 0
        if img.mode == "RGB":
            depth = 24
        if img.mode == "RGBA":
            depth = 32
        depth = depth.to_bytes(1, byteorder="big")
        header = [b"TEX", width, height, depth]
        for e in header:
            output.write(bytes(e))
        output.write(img.tobytes())
        output.close()
    except FileNotFoundError:
        print("[ERROR] File", sys.argv[1], "not found")
else:
    print("[ERROR] Not enough arguments")