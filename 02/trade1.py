
def optimal_trade_naive(v):
    best = 0
    for buy in range(len(v)):
        for sell in range(buy, len(v)):
            profit = v[sell] - v[buy]
            if profit > best:
                best = profit
    return best


n = int(input())
v = [0] * n
for i in range(n):
    v[i] = int(input())

print(optimal_trade_naive(v))
