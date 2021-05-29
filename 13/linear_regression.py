from random import random, randint

X = []
Y = []
for i in range(100):
    x, y = map(float, input().split())
    X.append(x)
    Y.append(y)


def error(a, b):
    global X, Y

    err = 0
    for i in range(len(X)):
        err += (a*X[i] + b - Y[i]) ** 2
    return err / len(X)


best_a = 0
best_b = 0
min_err = 1e9

for i in range(10000):
    a = random() * (10 ** randint(0, 5))
    b = random() * (10 ** randint(0, 5))

    err = error(a, b)
    if err < min_err:
        min_err = err
        best_a = a
        best_b = b

print(f'f(x) = {best_a} x + {best_b}')
print(f'err(f) = {min_err}')


# Código para plotar

# import matplotlib.pyplot as plt
# import numpy as np

# func = lambda x:1.263296932133322*x + 153.14899662306115
# x = np.arange(0,10000,1)
# y = func(x)
# plt.plot(x,y)
# plt.grid()
# X_ = []
# Y_ = []
# for i in range(100):
#     X,Y = map(float,input().split())
#     X_.append(X)
#     Y_.append(Y)
# plt.scatter(X_,Y_)
# plt.show()
