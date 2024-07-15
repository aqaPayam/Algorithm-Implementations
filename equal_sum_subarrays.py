n = int(input())
a = list(map(int, input().strip().split()))[:n]
ap = 0
suma = 0

m = int(input())
b = list(map(int, input().strip().split()))[:m]
bp = 0
sumb = 0

res = 0

while bp < m and ap < n:
    sumb += b[bp]
    suma += a[ap]

    if sumb == suma:
        ap += 1
        bp += 1
        res += 1
        suma = 0
        sumb = 0
    elif sumb > suma:
        ap += 1
        sumb -= b[bp]
    else:
        bp += 1
        suma -= a[ap]


if ap == len(a) and bp == len(b):
    print(res)
else:
    print(-1)
