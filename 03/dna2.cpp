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

bool join(person &out, person const &p)
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

bool disjoint_set_cover(vector<person> const &v, person acc, int pos = 0)
{
    if (pos == v.size())
    {
        for (auto b : acc)
            if (not b)
                return false;
        return true;
    }
    if (disjoint_set_cover(v, acc, pos + 1))
        return true;
    if (join(acc, v[pos]))
        return disjoint_set_cover(v, acc, pos + 1);
    return false;
}

int main()
{
    int n;
    cin >> n;

    vector<person> v(n, vector<bool>(n));
    for (auto &p : v)
        cin >> p;

    person acc(n);
    if (disjoint_set_cover(v, acc))
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}