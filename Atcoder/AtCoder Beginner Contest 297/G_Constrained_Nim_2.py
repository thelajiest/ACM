n, L, R = map(int, input().split())
a = list(map(int, input().split()))


def compute_sg(x):
    g = x % (L + R) // L
    return g


x = 0
for i in range(n):
    x ^= compute_sg(a[i])

if x != 0:
    print("First")
else:
    print("Second")
