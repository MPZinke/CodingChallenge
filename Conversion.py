
def toDigits(n, b):
    """Convert a positive number n to its digit representation in base b."""
    digits = []
    while n > 0:
        digits.insert(0, MAPPING[n % b])
        n  = n // b
    return digits



def fromDigits(digits, b):
    """Compute the number given by digits in base b."""
    n = 0
    for d in digits:
        # print([x for x in range(len(MAPPING)) if(d == MAPPING[x])])
        int_value = [x for x in range(len(MAPPING)) if(d == MAPPING[x])][0]
        n = b * n + int_value
        print(f"{MAPPING[int_value]} [{int_value:2} of {b}] {n}")
    return n


MAPPING = " ABCDEFGHIJKLMNOPQRSTUVWXYZ"


value = fromDigits("WAYNEWANTEDTHISTOBEHARDER", 27)
print(value)
value = toDigits(value, 27)
print(value)