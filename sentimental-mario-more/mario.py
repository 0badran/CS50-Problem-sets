from cs50 import get_int

height = None

while True:
    height = get_int("Height: ")
    if height <= 8 and height >= 1:
        break
count = height-1
for i in range(height):
    print(' '*count, end='')
    print('#'*(i+1), end="")
    print('  ', end="")
    print('#'*(i+1))
    count -= 1
