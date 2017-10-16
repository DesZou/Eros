import sys
import random

sys.stdout = open('sequence' + sys.argv[1] + '.in', 'w')

n, k = int(sys.argv[2]), random.randint(1, int(sys.argv[3]))
m = random.randint(1, 2 * 10 ** 8)

print(n, m, k)
for i in range(n):
    print(random.randint(1, 10 ** 9), end = ' ')
print()

q = int(sys.argv[4])
print(q)
if q == 1:
    print(1, n)
    exit()
for i in range(q):
    L = random.randint(1, n)
    R = random.randint(L, n)
    print(L, R)
