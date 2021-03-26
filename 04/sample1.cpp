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

solution heuristic1(graph const &g)
{
    for (int i = 0; i < 100; i++)
    {
        solution s(g.size());
        for (int &i : s)
            i = distribution(generator);
        if (is_valid(g, s))
            return s;
    }
    return solution(g.size());
}

int main()
{
    unsigned seed = 0; //std::chrono::system_clock::now().time_since_epoch().count();
    generator = default_random_engine(seed);
    distribution = uniform_int_distribution<int>(0, 1);

    int n;
    cin >> n;

    graph g(n, vector<int>(n));

    for (auto &v : g)
        for (auto &i : v)
            cin >> i;

    auto s = heuristic1(g);
    cout << is_valid(g, s) << " ";
    cout << "f(S) = " << f(s) << "\n";

    return 0;
}