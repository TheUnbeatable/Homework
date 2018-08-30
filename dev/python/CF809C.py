mod = 1000000007

def sum(x, y, k, add) :
    if k < add : return 0
    up = x + add
    if up > k : up = k
    add = add + 1
    return y * ( ( (add + up) * (up - add + 1) // 2 ) % mod ) % mod

def solve(x, y, k, add = 0) :
    if x == 0 or y == 0 : return 0
    if x > y :
        x, y = y, x
    pw = 1
    while (pw << 1) <= y :
        pw <<= 1
    if pw <= x :
        return ( sum(pw, pw, k, add)\
                 + sum(pw, x + y - pw - pw, k, add + pw)\
                 + solve(x - pw, y - pw, k, add) ) % mod
    else :
        return ( sum(pw, x, k, add)\
                 + solve(x, y - pw, k, add + pw) ) % mod

q = int(input())
for i in range(0, q) :
    x1, y1, x2, y2, k = list(map(int, input().split()))    
    ans = ( solve(x2, y2, k)\
            - solve(x1 - 1, y2, k)\
            - solve(x2, y1 - 1, k)\
            + solve(x1 - 1, y1 - 1, k) ) % mod
    if ans < 0 : ans += mod
    print(ans)
