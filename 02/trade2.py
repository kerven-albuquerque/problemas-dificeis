
def optimal_trade(v):
    best = 0
    min_val = v[0]
    for sell in range(len(v)):
        profit = v[sell] - min_val
        if profit > best:
            best = profit
        if v[sell] < min_val:
            min_val = v[sell]
    return best


n = int(input())
v = [0] * n
for i in range(n):
    v[i] = int(input())

print(optimal_trade(v))
