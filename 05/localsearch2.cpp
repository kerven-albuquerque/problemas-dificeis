#include "construction.cpp"

vector<int> positions;

void random_descent(graph const &g, solution &s)
{
    shuffle(positions.begin(), positions.end(), generator);

    for (int k = 0; k < s.size(); k++)
    {
        int i = positions[k];

        if (s[i] == 1)
            continue;

        s[i] = 1;
        if (is_valid(g, s))
            return random_descent(g, s);
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

    positions.assign(n, 0);
    iota(positions.begin(), positions.end(), 0);

    graph g(n, vector<int>(n));

    for (auto &v : g)
        for (auto &i : v)
            cin >> i;

    cout << "\nRandom descent\n";

    auto s = random_construction(g);
    cout << "f(" << s << ") = " << f(s) << "\n";

    random_descent(g, s);
    cout << "f(" << s << ") = " << f(s) << "\n";

    return 0;
}