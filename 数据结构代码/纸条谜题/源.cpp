#include <iostream>
#include <string>
using namespace std;

int pos;

string f(string x)
{
	int i = 0, end = x.length(), times = 0;
	string res = "";
	for (int i = 0; i < end; ++i)
	{
		if (x[i] >= '0' && x[i] <= '9')
		{
			times = 10 * times + x[i] - '0';
		}
		else
		{
			string tmp = "";
			if (x[i] == '[')
			{
				tmp = x.substr(++i);
				tmp = f(tmp);
				while (times--)
					res.append(tmp);
				times = 0;
				i += pos;
			}
			else if (x[i] == ']')
			{
				pos = i;
				return res;
			}
			else
			{
				res += x[i];
			}
		}
	}
	return res;
}


int main()
{
	string a, b = "1[";
	cin >> a;
	b.append(a);
	b.append("]");
	b = f(b);
	b.erase(b.length());
	cout << b;

	return 0;
}
