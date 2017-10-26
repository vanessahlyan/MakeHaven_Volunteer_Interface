from cs50 import get_int

# prompt user for height, keep reprompting if height is invalid
while True:
    h = get_int("Choose a height for the pyramids among integers from 0 to 23: ")
    if h >= 0 and h <= 23:
        break

# iterate by row
for i in range(h):
    # print h - 1 spaces for the left
    print((h - 1 - i) * " ", end='')
    # print i + 1 hashes for left
    print((i + 1) * "#", end='')

    # print 2 spaces for gap
    print("  ", end='')

    # print i + 1 hashes for right
    print((i + 1) * "#", end='')

    print()
