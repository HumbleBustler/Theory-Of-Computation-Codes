#include<bits/stdc++.h>
using namespace std;
set<string> ss;
map<char,int> nullHash;
map<char,int> useless;
map<char,set<string>> mp3;
void func(int i,int l,string s,string cur)
{
	if(i>l-1)
	{
		ss.insert(s);
		return;
	}
	char cc=cur[i];
	if(useless[cc]==1)
	{
		func(i+1,l,s,cur);
	}

	else if(nullHash[cc]==0)
	{
		func(i+1,l,s+cur[i],cur);
	}
	else
	{
		func(i+1,l,s+cur[i],cur);
		func(i+1,l,s,cur);
	}
}
int main()
{
	cout<<"Enter the number of rules in the grammar : ";
	int noRules;
	cin>>noRules;
	map<char,set<string>> prodMap;
	for(int i=0;i<noRules;i++)
	{
		cout<<"Enter the symbol from which production rule is to be given : ";
		char variable;
		cin>>variable;
		cout<<"Enter the number of productions from this non-terminal : ";
		int t;
		cin>>t;
//		set<string> prod;
		cout<<"Enter the productions in space separated format : ";
		for(int y=0;y<t;y++)
		{
			string s;
			cin>>s;
			string nullProd="#";
			if((t==1)&&(s.compare(nullProd)==0))
			{
				useless[variable]=1;
			}
			if(s.compare(nullProd)==0)
			{
				nullHash[variable]=1;
				continue;
			}
			else
			{
				nullHash[variable]=0;
			}
			prodMap[variable].insert(s);
		}
	}
	map<char,set<string>> :: iterator it;
	map<char,int> :: iterator itnew;
	for(int j=0;j<300;j++)
	{
		for(itnew=nullHash.begin();itnew!=nullHash.end();itnew++)
		{
			char tempo=itnew->first;
			//string f(1,tempo);
			if(nullHash[tempo]!=1)
			{
				//set<string> tmpry=prodMap[tempo];
				set<string> :: iterator itt;
				for(itt=prodMap[tempo].begin();itt!=prodMap[tempo].end();itt++)
				{
					string d=*itt;
					if(d.size()==1&&(d[0]<='Z')&&(d[0]>='A'))
					{
//						char fun=d[0];
						if(nullHash[d[0]]==1);
						{
						    nullHash[tempo]=1;
						}
					}
				}
			}
		}
	}	
	for(it=prodMap.begin();it!=prodMap.end();it++)
	{
		set<string> :: iterator it2=(it->second).begin(),it3;
		//prodMap[it->first].clear();
		for(;it2!=(it->second).end();it2++)
		{
			string temp=*it2;
			int l=temp.size();
			string empty="";//string thats going to be filled
			func(0,l,empty,temp);
			// prodMap[teprodMaporary].clear();
			for(it3=ss.begin();it3!=ss.end();it3++)
			{
				string buffer=*it3;
	//			char temporary=it->first;
               
				mp3[it->first].insert(buffer);
				
			}
		}
		ss.clear();
	}
	for(it=mp3.begin();it!=mp3.end();it++)
	{
		set<string> :: iterator it2;
		cout<<"The productions for   "<<it->first<<" are : "<<endl;
		for(it2=((it->second).begin());it2!=(it->second).end();it2++)
		{
			string temp=*it2;
			char var = it->first;
			if(var=='S')
			{
				if(temp=="")
				{
					cout<<"#"<<endl;
				}
			}
			cout<<temp<<endl;
		}
	}
	return 0;
}
