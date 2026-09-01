import random


width = 1600
height = 1200

# even divisors...

#1600,800,400,200,100,50,25
#1200,600,300,150,75




# 200 bytes packet payload = 800 2 bit samples (uncompressed)

# 1600x1200 pixels
# 100x16 pixels wide
# 75x16 pixels tall

# 1-10
# gridpos   





# 16*16 = 256 samples per 'frame' with 100 pixels between each sampled pixel

# 1600*0 +  0,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,
# 1600*1 +  ...
# 1600*16 + ...





from PIL import Image

# Open an existing image or create a new one
img = Image.new("RGB", (width, height), color=(20,20,20))

# Load the pixel map
pixels = img.load()

fiddle = []
for i in range(16):
    for j in range(16):
        fiddle.append(i+j*1600)


random.seed(1)
random.shuffle(fiddle)
print(fiddle)

def setpixel(i,val):
    grid_position_index = (i & 0x1fff) % 7500    # 13 bits 0-7500
    offset              = (i >> 13) & 0xff      # 6  bits

    gridpos = fiddle[offset] + ((grid_position_index%100) * 16) + ((grid_position_index//100) * 1600*16)
    



    x = (gridpos%1600)
    y = (gridpos//1600)
    pixels[x,y] = val

for i in range(1000000):
    setpixel(i,(255,255,255))



# Save the changes
img.save("pixel_modified.png")

