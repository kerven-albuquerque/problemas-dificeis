#include <bits/stdc++.h>
using namespace std;

default_random_engine gen;
uniform_int_distribution<int> distN;
uniform_int_distribution<int> distP;
uniform_int_distribution<int> dist2;
vector<int> perm;

using solution = vector<bool>;
using graph = vector<vector<int>>;

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

solution build(graph const &g)
{
    while (true)
    {
        int n = distN(gen) + 1;
        shuffle(perm.begin(), perm.end(), gen);

        solution s(g.size());
        for (int i = 0; i < n; i++)
            s[perm[i]] = true;

        if (is_valid(g, s))
            return s;
    }
}

vector<solution> init_population(graph const &g)
{
    vector<solution> p(100);
    for (auto &s : p)
        s = build(g);
    return p;
}

void local_search(graph const &g, solution &s)
{
    shuffle(perm.begin(), perm.end(), gen);

    for (int k = 0; k < s.size(); k++)
    {
        int i = perm[k];

        if (s[i] == 1)
            continue;

        s[i] = 1;
        if (is_valid(g, s))
            return local_search(g, s);
        s[i] = 0;
    }
}

void combine(graph const &g, vector<solution> &p, int s1, int s2)
{
    int k = g.size() / 2;
    solution c1 = p[s1], c2 = p[s2];

    for (int i = k; i < g.size(); i++)
        swap(c1[i], c2[i]);

    // Mutation in C1
    k = distN(gen);
    c1[k] = !c1[k];

    // Mutation in C2
    k = distN(gen);
    c2[k] = !c2[k];

    if (is_valid(g, c1))
    {
        local_search(g, c1); // Local search in C1
        p.push_back(c1);
    }
    if (is_valid(g, c2))
    {
        local_search(g, c2); // Local search in C2
        p.push_back(c2);
    }
}

int f(solution const &s, vector<int> const &w)
{
    int total = 0;
    for (int i = 0; i < s.size(); i++)
        if (s[i])
            total += w[i];
    return total;
}

solution genetic(graph const &g, vector<int> const &w)
{
    auto p = init_population(g);

    for (int i = 0; i < 1000; i++)
    {
        for (int i = 0; i < 100; i++)
            combine(g, p, distP(gen), distP(gen));

        sort(p.begin(), p.end(), [&](auto a, auto b) {
            return f(a, w) > f(b, w);
        });

        p.resize(100);
        cout << f(p.front(), w) << "\n";
    }

    return p.front();
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

int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    gen = default_random_engine(seed);
    dist2 = uniform_int_distribution<int>(0, 1);
    distP = uniform_int_distribution<int>(0, 99);

    int n;
    cin >> n;
    distN = uniform_int_distribution<int>(0, n - 1);
    perm.assign(n, 0);
    iota(perm.begin(), perm.end(), 0);

    graph g(n, vector<int>(n));
    vector<int> w(n);

    for (auto &i : w)
        cin >> i;

    for (auto &v : g)
        for (auto &i : v)
            cin >> i;

    auto best = genetic(g, w);
    cout << best << ": " << f(best, w) << "\n";

    return 0;
}