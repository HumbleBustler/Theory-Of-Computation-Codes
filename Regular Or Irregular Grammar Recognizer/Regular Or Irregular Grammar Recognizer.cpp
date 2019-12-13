#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;

int upper(int c)
{
    if((c > 64) && (c < 91))
        return 1;
    return 0;
}

int lower(int c)
{
    if((c > 96) && (c < 123))
        return 1;
    return 0;
}

int main()
{
	freopen("testcase01.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	long long n,i,j;        // gram = 'r' for right linear  &&   gram = 'l' for left linear
	char gram = 'n';
	int regular = 1;
	string s;
	vector<string> input;
	while(getline(cin,s))
	{
		input.push_back(s);
		n=s.size();
		if(upper(s[0]) && s[1]==' ')
		{
			for(i=2;s[i]!=' ';i++);
			i++;
			if(upper(s[i]) && lower(s[n-1]))
			{
				if(gram == 'r')
				{
					cout<<"Not a Regular Grammar\n";
					regular = 0;
					break;
				}
				else gram = 'l';
			}
			else if(upper(s[n-1]) && lower(s[i]))
			{
				if(gram == 'l')
				{
					cout<<"Not a Regular Grammar\n";
					regular = 0;
					break;
				}
				else gram = 'r';
			}
			else if(upper(s[i]) && upper(s[n-1]) && i!=(n-1))
			{
				cout<<"Not a Regular Grammar\n";
				regular = 0;
				break;
			}
			
			for(j=i+1;j<n-1;j++)
			{
				if(upper(s[j]))
				{
					break;
				}
			}
			if(j==n-1 || j==n) continue;
			else
			{
				cout<<"Not a Regular Grammar\n";
				regular = 0;
				break;
			}
		}
		else
		{
			cout<<"Not a Regular Grammar\n";
			regular = 0;
			break;
		}
		
	}
	long long count=0;
	if(regular == 1)
	{
		set<char> var;
		var.insert('S');
		for(string s:input)
		{
		    n = s.size();
		    if(var.find(s[0]) != var.end())
			{
				if(gram == 'l')
				{
					for(i=2;s[i]!=' ';i++);
					i++;
					if(lower(s[i]) || s[i] == '$')
					{
						cout<<"Regular Grammar :";
						cout<<" Left Linear Grammar\n";
						break;
					}
					else var.insert(s[i]);
				}
				else if(gram == 'r')
				{
					if(lower(s[n-1]) || s[n-1] == '$')
					{
						cout<<"Regular Grammar :";
						cout<<" Right Linear Grammar\n";
						break;
					}
					else var.insert(s[n-1]);
				}
			}
			count++;
		}
		if(count==input.size()) cout<<"Not a Regular Grammar\n";
	}
	return 0;
}

