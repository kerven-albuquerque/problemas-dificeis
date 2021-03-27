#include "construction.cpp"

void first_improvement(graph const &g, solution &s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 1)
            continue;

        s[i] = 1;
        if (is_valid(g, s))
            return first_improvement(g, s);
        s[i] = 0;
    }
    return;
}

int main()
{
    unsigned seed = 0;
    init_construction(seed);

    int n;
    cin >> n;

    graph g(n, vector<int>(n));

    for (auto &v : g)
        for (auto &i : v)
            cin >> i;

    cout << "\nFirst improvement\n";

    auto s = random_construction(g);
    cout << "f(" << s << ") = " << f(s) << "\n";

    first_improvement(g, s);
    cout << "f(" << s << ") = " << f(s) << "\n";

    return 0;
}