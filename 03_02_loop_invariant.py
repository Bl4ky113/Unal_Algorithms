
def funct (b: int, n: int):
    d = 0
    a = 1
    c = n

    while (c >= 1):
        a = a * b
        d = d + a
        c = c - 1

    print("D = ", d)
