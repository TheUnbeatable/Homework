import sys
def ask(x, y) :
    print("1", x, y)
    sys.stdout.flush()
    return input()

def solve(L, R) :
    while L < R :
        mid = (L + R) >> 1
        if ask(mid, mid + 1) == "TAK" :
            R = mid
        else :
            L = mid + 1
    return L
        
n, k = list(map(int, input().split()))
a = solve(1, n)
b, c = a, a
if a > 1 :
    b = solve(1, a - 1)
if a < n :
    c = solve(a + 1, n)
if ask(b, c) == "NIE" :
    b, c = c, b
if a == b :
    b, c = c, b
print("2", a, b)
sys.stdout.flush()
