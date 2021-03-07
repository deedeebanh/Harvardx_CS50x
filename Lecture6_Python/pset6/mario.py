from cs50 import get_int
num = 0
while (num < 1 or num > 8):
    num = get_int("Height: ")

for i in range(num):
    print(" "*(num-i-1) + "#"*(i+1))
