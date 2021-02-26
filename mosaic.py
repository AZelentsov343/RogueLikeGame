import random

pixels = []
for i in range(1024):
    for j in range(1024):
        pixels.append((i, j))

random.shuffle(pixels)
print('{')
for i in range(1024 * 1024):

    print('{' + str(pixels[i][0]) + ', ' + str(pixels[i][1]) + '},')
print('}')