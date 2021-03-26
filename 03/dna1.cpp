#include <bits/stdc++.h>
using namespace std;

using person = vector<bool>;

istream &operator>>(istream &is, person &p)
{
    string s;
    while (s.empty() and getline(is, s))
        ;
    stringstream ss(s);
    int c;
    while (ss >> c)
        p[c] = true;
    return is;
}

bool join(person& out, person const &p)
{
    bool inter = false;
    for (int i = 0; i < out.size(); i++)
    {
        if (out[i] and p[i])
        {
            inter = true;
            break;
        }
        out[i] = out[i] or p[i];
    }
    return not inter;
}

bool next_comb(person &p)
{
    int i = 0;
    while (i < p.size())
    {
        p[i] = not p[i];
        if (p[i])
            break;
        i++;
    }
    return i != p.size();
}

bool disjoint_set_cover(vector<person> const &v)
{
    person comb(v.size());

    while (next_comb(comb))
    {
        person ans(v.size());
        bool inter = false;
        for (int i = 0; i < v.size(); i++)
            if (comb[i] and not join(ans, v[i]))
            {
                inter = true;
                break;
            }

        if (not inter)
        {
            bool all = true;
            for (auto b : ans)
                if (not b)
                {
                    all = false;
                    break;
                }
            if (all)
            {
                for (auto i : comb)
                    cout << i;
                cout << "\n";
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int n;
    cin >> n;

    vector<person> v(n, vector<bool>(n));
    for (auto &p : v)
        cin >> p;

    if (disjoint_set_cover(v))
        cout << "YES\n";
    else
        cout << "NO\n";


    return 0;
}