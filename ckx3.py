from PIL import Image
import os
i=os.listdir("./zp")
im=Image.open("zp/"+i[0])
im.save("zh.png")

