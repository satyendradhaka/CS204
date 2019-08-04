/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include<bits/stdc++.h> 
using namespace std; 


string add(string s1, string s2) 
{ 

	if (s1.length() > s2.length()) 
		swap(s1, s2); 


	string p = ""; 
	
	reverse(s1.begin(), s1.end()); 
	reverse(s2.begin(), s2.end()); 

	int n1 = s1.length(), n2 = s2.length(); 




	int c = 0; 
	for (int i=0; i<n1; i++) 
	{ 
	
		int sum = ((s1[i]-'0')+(s2[i]-'0')+c); 
		p.push_back(sum%10 + '0'); 


		c = sum/10; 
	} 


	for (int i=n1; i<n2; i++) 
	{ 
		int sum = ((s2[i]-'0')+c); 
		p.push_back(sum%10 + '0'); 
		c = sum/10; 
	} 

	
	if (c) 
		p.push_back(c+'0'); 


	reverse(p.begin(), p.end()); 

	return p; 
} 

int main() 
{ 
	string s1; 
	string s2;
	getline(cin, s1);
	getline(cin, s2);
	cout << add(s1, s2); 
	return 0; 
} 
