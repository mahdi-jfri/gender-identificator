#include <bits/stdc++.h>

#define IGNORE_T_COST 6
#define IGNORE_S_COST 1

namespace std {   };
using namespace std;

size_t levenshtein_distance(const char* s, size_t n, const char* t, size_t m)
{
	++n; ++m;
	size_t* d = new size_t[n * m];

	memset(d, 0, sizeof(size_t) * n * m);

	for (size_t i = 1, im = 0; i < m; ++i, ++im)
	{
		for (size_t j = 1, jn = 0; j < n; ++j, ++jn)
		{
			if (s[jn] == t[im])
			{
				d[(i * n) + j] = d[((i - 1) * n) + (j - 1)];
			}
			else
			{
				d[(i * n) + j] = min(d[(i - 1) * n + j] + 1, /* A deletion. */
						min(d[i * n + (j - 1)] + 1, /* An insertion. */
							d[(i - 1) * n + (j - 1)] + 1)); /* A substitution. */
			}
		}
	}

#ifdef DEBUG_PRINT
	for (size_t i = 0; i < m; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			cout << d[(i * n) + j] << " ";
		}
		cout << endl;
	}
#endif

	size_t r = d[n * m - 1];

	delete [] d;

	return r;
}

int dp[200][200];

int manual_distance(const string &s, const string &t)
{
    int n = s.size(), m = t.size();
    if(!n) {
//        cerr << "found!" << endl;
    }
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= m; j++)
        {
            if(!i)
                dp[i][j] = j * IGNORE_T_COST;
            else if(!j)
                dp[i][j] = 0;
            else
                dp[i][j] = 1e9;
        }

    int mn = 1e9;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {
            dp[i][j] = min(
                dp[i][j - 1] + IGNORE_T_COST,
                dp[i - 1][j] + IGNORE_S_COST
            );
            if(s[i - 1] == t[j - 1])
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
            if(j == m)
                mn = min(mn, dp[i][j]);
        }

    return mn;
}

int main(int argc, char* argv[])
{
	int usernames, names_count;
	cin >> usernames >> names_count;

	vector<string> names;
	long long sum = 0;
	for(int i = 0; i < names_count; i++)
	{
		string s;
		cin >> s;
		names.push_back(s);
		sum += s.size() * s.size();
	}
	for(int i = 0; i < usernames; i++)
	{
		string username;
		cin >> username;
		sum += username.size() * username.size();
		for(const auto &name : names)
		{
			cout << manual_distance(username, name) << " ";
//            cout << levenshtein_distance(username.data(), username.size(), name.data(), name.size()) << " ";
		}
		cout << endl;
	}

	cerr << (double)sum / 1e8 << endl;

	return 0;
}

