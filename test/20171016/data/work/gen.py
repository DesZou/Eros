import sys
import random

sys.stdout = open('work' + sys.argv[1] + '.in', 'w')

n, m = int(sys.argv[2]), random.randint(10 ** 2, 2 * 10 ** 4)

print(n, m)
for i in range(n):
    print(random.randint(1, 10 ** 9), random.randint(1, 10 ** 5))
