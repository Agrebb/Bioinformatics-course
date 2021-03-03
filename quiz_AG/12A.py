ans = 0
summ = 0
for x in input().split(','):
    ans += int(x)**2
    summ += int(x);
print(round(ans / summ, 2))
