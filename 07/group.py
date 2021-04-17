from random import randint


class pt:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def __repr__(self):
        return f'({self.x}, {self.y})'


def randpt():
    return pt(randint(100, 500), randint(100, 500))


def dist(a, b):
    return ((a.x - b.x) ** 2 + (a.y - b.y) ** 2) ** 0.5


def closest(point, centroids):
    ans = 0
    d = dist(point, centroids[0])

    for i in range(1, len(centroids)):
        d2 = dist(point, centroids[i])
        if d2 < d:
            d = d2
            ans = i

    return ans


def updateCentroids(points, groups, centroids):
    for g in range(len(centroids)):
        count = 0
        x = 0
        y = 0

        for i in range(len(points)):
            if groups[i] == g:
                count += 1
                x += points[i].x
                y += points[i].y

        if count > 0:
            centroids[g].x = x/count
            centroids[g].y = y/count


def kmeans(points, centroids, groups):
    changed = True
    while changed:
        changed = False
        for i in range(len(points)):
            g = closest(points[i], centroids)
            if g != groups[i]:
                groups[i] = closest(points[i], centroids)
                changed = True

        updateCentroids(points, groups, centroids)
        # print(groups, centroids, sep='\n', end='\n\n')


def obj(points, groups, centroids):
    s = 0
    for i in range(len(points)):
        s += dist(points[i], centroids[groups[i]])
    return s/len(points)


def singlerun(points):
    centroids = [randpt() for i in range(3)]
    groups = [0] * len(points)
    kmeans(points, centroids, groups)

    with open('a.txt', 'w') as f:
        for i in range(len(points)):
            if groups[i] == 0:
                f.write(f'{points[i].x} {points[i].y}\n')

    with open('b.txt', 'w') as f:
        for i in range(len(points)):
            if groups[i] == 1:
                f.write(f'{points[i].x} {points[i].y}\n')

    with open('c.txt', 'w') as f:
        for i in range(len(points)):
            if groups[i] == 2:
                f.write(f'{points[i].x} {points[i].y}\n')

    return obj(points, groups, centroids)


def multistart(points):
    best = float('inf')

    for i in range(50):
        centroids = [randpt() for i in range(3)]
        groups = [0] * len(points)
        kmeans(points, centroids, groups)
        best = min(best, obj(points, groups, centroids))

    with open('a.txt', 'w') as f:
        for i in range(len(points)):
            if groups[i] == 0:
                f.write(f'{points[i].x} {points[i].y}\n')

    with open('b.txt', 'w') as f:
        for i in range(len(points)):
            if groups[i] == 1:
                f.write(f'{points[i].x} {points[i].y}\n')

    with open('c.txt', 'w') as f:
        for i in range(len(points)):
            if groups[i] == 2:
                f.write(f'{points[i].x} {points[i].y}\n')

    return best


n = int(input())
points = []

for i in range(n):
    x, y = map(int, input().split())
    points.append(pt(x, y))
