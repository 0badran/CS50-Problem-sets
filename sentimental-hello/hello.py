from cs50 import get_string

name = get_string("What's your name? ")

if name:
    print("hello,", name)
else:
    print("hello, world")
