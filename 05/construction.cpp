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

solution random_construction(graph const &g)
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

void init_construction(int seed)
{
    generator = default_random_engine(seed);
    distribution = uniform_int_distribution<int>(0, 1);
}

ostream &operator<<(ostream &os, solution const &s)
{
    static int max_size = 30;
    if (s.size() > max_size)
    {
        for (int i = 0; i < max_size / 2; i++)
            os << s[i];
        os << "...";
        for (int i = s.size() - max_size / 2; i < s.size(); i++)
            os << s[i];
        return os;
    }
    for (int i = 0; i < s.size(); i++)
        os << s[i];
    return os;
}
