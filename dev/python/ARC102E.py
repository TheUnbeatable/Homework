mod = 998244353
k, n = list(map(int, input().split()))
C = [ [0 for i in range(n + k + 1)] for j in range(n + k + 1) ]
pw = [0 for i in range(n + k + 1)]

for i in range(0, n + k + 1) :
    C[i][0] = 1
    if i == 0 : pw[i] = 1
    else : pw[i] = (pw[i - 1] << 1) % mod
    for j in range(1, i + 1) :
        C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod

def calc(tot, seg) :
    if tot < 0 : return 0
    return C[tot + seg - 1][tot]

for i in range(2, k + k + 1) :
    ans = su = 0
    if i <= k : su = i - 1
    else : su = k + k - i + 1
    if i & 1 :
        for j in range(0, (su >> 1) + 1) :
            ans = ( ans + calc(n - j, k - su + j) * pw[j] % mod * C[su >> 1][j] ) % mod
    else :
        for j in range(0, (su >> 1) + 1) :
            ans = ( ans + calc(n - j - 1, k - su + j) * pw[j] % mod * C[su >> 1][j] ) % mod
            ans = ( ans + calc(n - j, k - su + j) * pw[j] % mod * C[su >> 1][j] ) % mod
    print(ans)
