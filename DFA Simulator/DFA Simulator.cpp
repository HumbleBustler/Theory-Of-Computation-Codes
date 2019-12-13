//Implementing dfa on input string (a,b)
//string starting with ab and ends with a
//As dfa do not remembers its previous state we have check chacterwise
#include<bits/stdc++.h>
using namespace std;

void dfa1(){
	
	//here we are taking buffer input from user and checking it as it is accepted by dfa or not
	//dfa do not remembers previous state hence we are reading the input buffer chacracterwise
	cout<<"Enter number of test cases "; //test cases
	int testcase;
	cin>>testcase;

	for(int j=0;j<testcase;j++){
		cout<<"Enter the string ";
		char buff[100000];
		cin>>buff;
		int size = strlen(buff);
		

		if(size==0)
		   cout<<"\nstring not accepted by dfa\n";

		int i = 0;
		while (i < size) {


			char c = buff[i];// input buffer
			cout << c;
			i++;


			if (c == 'a') {
			   c = buff[i];;
			   cout << c;
			   i++;
			   if (c == 'b'){

					if (i == size)
					    cout << "\nstring not accepted by dfa\n";

					while (i < size) {
						c = buff[i];
						cout << c;
						i++;


						if (c == 'a' && i == size) {
						  cout << "\nWowww!!! string is accepted by dfa\n";  //string accepted
						}


						else if (i == size) {
						   cout << "\nstring not accepted by dfa\n";
						}
					}
			    }

				else {        //dead state
					while (i < size) {
						c = buff[i];;
						cout << c;
						i++;
					}
					cout << "\nstring not accepted by dfa\n";
				}
			}

			else {    //dead state
				while (i < size) {

					c = buff[i];;
					cout << c;
					i++;
				}
				cout << "\nstring not accepted by dfa\n";
			}
		}
	}

}

void dfa2(){   //random chacter is generated and checked if it is accepted by dfa or not

	srand(time(0));
	cout<<"Enter number of test cases "; //test cases
	int testcase;
	cin>>testcase;

	for(int j=0;j<testcase;j++){
		cout<<"Enter the size of the random string generated ";
		int size;
		cin>>size;
		if(size>0)
		   cout<<"Random string of size "<<size<<" is ";
		else
		   cout<<"\nstring not accepted by dfa\n";

		int i = 0;
		while (i < size) {


			char c = 'a' + rand() % 2;//Generating random character a or b
			cout << c;
			i++;


			if (c == 'a') {
			   c = 'a' + rand() % 2;
			   cout << c;
			   i++;
			   if (c == 'b'){

					if (i == size)
					    cout << "\nstring not accepted by dfa\n";

					while (i < size) {
						c = 'a' + rand() % 2;
						cout << c;
						i++;


						if (c == 'a' && i == size) {
						  cout << "\nWowww!!! string is accepted by dfa\n";  //string accepted
						}


						else if (i == size) {
						   cout << "\nstring not accepted by dfa\n";
						}
					}
			    }

				else {        //dead state
					while (i < size) {
						c = 'a' + rand() % 2;
						cout << c;
						i++;
					}
					cout << "\nstring not accepted by dfa\n";
				}
			}

			else {    //dead state
				while (i < size) {

					c = 'a' + rand() % 2;
					cout << c;
					i++;
				}
				cout << "\nstring not accepted by dfa\n";
			}
		}
	}
}

int main()
{
		 cout<<"It is a dfa that accept the string starting with ab and ending with a\n";
		 cout<<"Enter 1 :- if you want to give string input to dfa\nEnter 2 :- if you want to generate random string for dfa\n";
		 int o;
		 cin>>o;
		 if(o==1)
		 	dfa1();
		 else if(o==2)
		 	dfa2();
		 else
		 	cout<<"wrong input";
			
			return 0;
}

