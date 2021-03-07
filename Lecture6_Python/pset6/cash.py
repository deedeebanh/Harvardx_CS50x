from cs50 import get_float
change = -1
while(change<0):
    change = get_float("Change owed: ")

count = 0
change *= 100
while(change >= 25):
    change -= 25
    count += 1

while(change >= 10):
    change -= 10
    count += 1

while(change >= 5):
    change -= 5
    count += 1

while(change >= 1):
    change -= 1
    count += 1

print(count)