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

int blocked(graph const &g, solution const &s)
{
    int b = 0;
    for (int i = 0; i < g.size(); i++)
    {
        if (s[b] == 1)
            continue;
        for (int j = 0; j < s.size(); j++)
            if (s[j] == 1 and g[i][j] == 1)
            {
                b++;
                break;
            }
    }
    return b;
}

solution heuristic3(graph const &g)
{
    solution s(g.size());

    while (true)
    {
        int best = -1;
        int best_val = INT_MAX;

        for (int i = 0; i < g.size(); i++)
        {
            if (s[i] == 1)
                continue;

            s[i] = 1;
            if (not is_valid(g, s))
            {
                s[i] = 0;
                continue;
            }

            int v = blocked(g, s);
            s[i] = 0;

            if (v < best_val)
            {
                best = i;
                best_val = v;
            }
        }

        if (best == -1)
            break;

        s[best] = 1;
    }

    return s;
}

int main()
{
    int n;
    cin >> n;

    graph g(n, vector<int>(n));

    for (auto &v : g)
        for (auto &i : v)
            cin >> i;

    auto s = heuristic3(g);
    cout << is_valid(g, s) << " ";
    cout << "f(S) = " << f(s) << "\n";

    return 0;
}