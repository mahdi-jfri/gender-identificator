#include <bits/stdc++.h>
using namespace std;

const int base[] = {4001, 737};
const int mod[] = {1000 * 1000 * 1000 + 7, 1000 * 1000 * 1000 + 9};
const int maxn = 1e2 + 20;

int h[2];
int pw[maxn][2];

int main()
{
    h[0] = h[1] = 1;
    for(int i = 1; i < maxn; i++)
        for(int j = 0; j < 2; j++)
            pw[i][j] = 1LL * pw[i - 1][j] * base[j] % mod[j];
	int usernames_count, names_count;
	cin >> usernames_count >> names_count;

	vector<string> names;
	vector<int> indexes;
	vector<string> usernames;
	vector<set<pair<int, int>>> st;
	long long sum = 0;
	for(int i = 0; i < names_count; i++)
	{
        indexes.push_back(i);
		string s;
		cin >> s;
		names.push_back(s);
		set<pair<int, int>> tmp;
        h[0] = 0, h[1] = 0;
        for(int y = 0; y < s.size(); y++)
        {
            for(int k = 0; k < 2; k++)
                h[k] = (1LL * h[k] * base[k] + s[y]) % mod[k];
            tmp.insert(make_pair(h[0], h[1]));
        }
		st.push_back(tmp);
		sum += s.size() * s.size() * s.size();
	}
	for(int i = 0; i < usernames_count; i++)
	{
	    string username;
	    cin >> username;
	    usernames.push_back(username);
	}
	sort(indexes.begin(), indexes.end(), [names](const int a, const int b) -> bool {
	    return names[a].size() > names[b].size();
	});
	for(int i = 0; i < usernames_count; i++)
	{
	    string username = usernames[i];
		if(i % 1000 == 0)
		    cerr << (double)i / (double)usernames_count << endl;
		bool do_continue = 1;
		vector<double> results(names_count, 0);
		for(int _ = 0; _ < names_count && do_continue; _++)
		{
		    int j = indexes[_];
            int res = 0;
            int h[2] = {0, 0};
            int y = 0;
            for(int x = 0; x < username.size(); x++)
            {
                string sub;
                if(y <= x)
                {
                    h[0] = h[1] = username[x];
                    y = x + 1;
                }
                while(st[j].count(make_pair(h[0], h[1])) && y <= (int)username.size())
                {
                    for(int k = 0; k < 2 && y < (int)username.size(); k++)
                        h[k] = (1LL * h[k] * base[k] + username[y]) % mod[k];
                    y++;
                }
                int prev_res = res;
                res = max(res, y - x - 1);
                if(y - x - 1 == (int)names[j].size())
                {
                    if(y + 1 < (int)username.size() && username[y + 1] == 'i')
                        res = prev_res;
                    if(!x && (y > (int)username.size() || username[y - 1] == '_'))
                    {
                        do_continue = 0;
                        break;
                    }
                    if(x > 0 && username[x - 1] == '_' && y > (int)username.size())
                    {
                        do_continue = 0;
                        break;
                    }
                }
                for(int k = 0; k < 2; k++)
                    h[k] = (((h[k] - 1LL * pw[y - x - 1][k] * username[y]) % mod[k]) + mod[k]) % mod[k];
            }
            if(!do_continue)
                for(auto &x : results)
                    x = 0;
            results[j] = (double) res / (double)names[j].size();
//            cout << res << endl;
		}
		for(const auto &x : results)
		    cout << x << " ";
		cout << "\n";
		sum += username.size() * username.size() * username.size();
	}

//	cerr << (double)sum / 1e8 << endl;

	return 0;
}

