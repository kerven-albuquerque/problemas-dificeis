#include "construction.cpp"

vector<int> positions;

void vnd(graph const &g, solution &s)
{
    shuffle(positions.begin(), positions.end(), generator);
    for (int k = 0; k < s.size(); k++)
    {
        int i = positions[k];
        if (s[i] == 1)
            continue;

        s[i] = 1;
        if (is_valid(g, s))
            return vnd(g, s);
        s[i] = 0;
    }

    shuffle(positions.begin(), positions.end(), generator);
    for (int k1 = 0; k1 < s.size(); k1++)
    {
        int i1 = positions[k1];
        if (s[i1] == 0)
            continue;

        s[i1] = 0;
        for (int k2 = 0; k2 < s.size(); k2++)
        {
            int i2 = positions[k2];
            if (s[i2] == 1)
                continue;

            s[i2] = 1;
            for (int k3 = 0; k3 < s.size(); k3++)
            {
                int i3 = positions[k3];
                if (s[i3] == 1)
                    continue;

                s[i3] = 1;
                if (is_valid(g, s))
                    return vnd(g, s);
                s[i3] = 0;
            }
            s[i2] = 0;
        }
        s[i1] = 1;
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

    cout << "\nVND\n";

    auto s = random_construction(g);
    cout << "f(" << s << ") = " << f(s) << "\n";

    vnd(g, s);
    cout << "f(" << s << ") = " << f(s) << "\n";

    return 0;
}