#include <bits/stdc++.h>
using namespace std;

using graph = vector<vector<int>>;
using solution = vector<int>;

bool is_valid(graph const &g, solution const &s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 0)
            continue;
        for (int j = i + 1; j < s.size(); j++)
        {
            if (s[j] == 0)
                continue;
            if (g[i][j] == 1)
                return false;
        }
    }
    return true;
}

int f(solution const &s)
{
    return accumulate(s.begin(), s.end(), 0);
}

default_random_engine generator;
uniform_int_distribution<int> distribution;

solution heuristic2(graph const &g)
{
    solution s(g.size());

    int failures = 0;
    int count = 0;
    while (count < g.size() and failures < 10)
    {
        int i = distribution(generator);
        while (s[i] == 1)
            i = distribution(generator);

        s[i] = 1;
        if (is_valid(g, s))
            count++;
        else
        {
            s[i] = 0;
            failures++;
        }
    }

    return s;
}

int main()
{
    unsigned seed = 0; //std::chrono::system_clock::now().time_since_epoch().count();
    generator = default_random_engine(seed);

    int n;
    cin >> n;

    distribution = uniform_int_distribution<int>(0, n - 1);

    graph g(n, vector<int>(n));

    for (auto &v : g)
        for (auto &i : v)
            cin >> i;

    auto s = heuristic2(g);
    cout << is_valid(g, s) << " ";
    cout << "f(S) = " << f(s) << "\n";

    return 0;
}