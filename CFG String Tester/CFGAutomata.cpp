 #include<iostream>  
#include<cstring>
#include<algorithm>
#include<string>
#include<cassert>
#include<iomanip>
#include<bits/stdc++.h>
using namespace std;

#define MAX 100
#define for(i,a,b) for(i=a;i<b; i++)

string gram[MAX][MAX];	
string dpr[MAX];
int p,np, Y=0,P;
string grammar[100];
void fileinput(){
  
	FILE*v=freopen("TestInput.txt","r",stdin);
	
	while(cin>>grammar[Y])
	{
		Y++;
	}
	for(P,0,Y)
	{	
		cout<<grammar[P]<<endl;
	}
        fclose(v);
	
        
 }


 string concat( string a, string b)	
{
	int i;
	string r=a;
	for(i,0,b.length())
		if(r.find(b[i]) > r.length())
			r+=b[i];
	return (r);
}

 void break_gram(string a)
{
	int i;
	p=0;
	while(a.length())
	{
		i=a.find("|");
		if(i>a.length())
		{
			dpr[p++] = a;
			a="";
		}
		else
		{
			dpr[p++] = a.substr(0,i);
			a=a.substr(i+1,a.length());
		}
	}
}

 int lchomsky(string a)	
{
	if(a.length()==1 && a[0]>='A' && a[0]<='Z')
		return 1;
	return 0;
}

inline int rchomsky(string a)	
{
	if (a.length() == 1 && a[0]>='a' && a[0] <='z')
		return 1;
	if (a.length()==2 && a[0]>='A' && a[0]<='Z' && a[1]>='A' && a[1]<='Z' )
		return 1;
	return 0;
}

 string search_prod(string p)
{
	int j,k;
	string r="";
	for(j,0,np)
	{
		k=1;
		while(gram[j][k] != "")
		{
			if(gram[j][k] == p)
			{
				r=concat(r,gram[j][0]);
			}
			k++;
		}
	}	
	return r;
}

 string gen_comb(string a, string b)	
{
	int i,j;
	string pri=a,re="";
	for(i,0,a.length())
		for(j,0,b.length())
		{
			pri="";
			pri=pri+a[i]+b[j];
			re=re+search_prod(pri);		
		}		
	return re;
}

int main()
{
	int i,pt,j,l,k,m=0,t=0;
	string a,str,r,pr,start;
       // char a[1000];
    	 cout<<"\nEnter string to be checked : ";
	cin >> str;
        fileinput();
        start = grammar[t].substr(0,grammar[0].length());
        while(grammar[m].length()!=0)
        {
           
        m++;
        }
        np=Y;
        for(i,0,np)
	{       
		a=grammar[t].substr(0,grammar[t].length());
		t++;
		pt=a.find("->");
		gram[i][0] = a.substr(0,pt);
		if (lchomsky(gram[i][0]) == 0)
		{
			cout<<"\nGrammar not in Chomsky Form";
			abort();
		}
		a = a.substr(pt+2, a.length());
		break_gram(a);
		for(j,0,p)
		{
			gram[i][j+1]=dpr[j];
			if (rchomsky(dpr[j]) == 0)
			{
				cout<<"\nGrammar not in Chomsky Form";
				abort();
			}
		}
	}


	string matrix[MAX][MAX],st;

	for(i,0,str.length())		
	{
		r="";
		st = "";
		st+=str[i];
		for(j,0,np)
		{
			k=1;
			while(gram[j][k] != "")
			{
				if(gram[j][k] == st)
				{
					r=concat(r,gram[j][0]);
				}
				k++;
			}
		}
		matrix[i][i]=r;
	}
	int ii,kk;
	for(k,1,str.length())		
	{
		for(j,k,str.length())
		{
			r="";
			for(l,j-k,j)
			{
				pr = gen_comb(matrix[j-k][l],matrix[l+1][j]);
				r = concat(r,pr);
			}
			matrix[j-k][j] = r;
		}
	}

	
			
	int f=0;
	//for(i,0,start.length())
		if(matrix[0][str.length()-1].find(start[0]) <= matrix[0][str.length()-1].length())
		{
			cout<<"Woww!!!! String can be generated\n";
			return 0;
		}
	cout<<" '_' String cannot be generated '_'\n";
	return 0;
}
