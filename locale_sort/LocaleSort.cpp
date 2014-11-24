// LocaleSort.cpp : Defines the entry point for the console application.
// M.Dorman Feb 28, 2012
//

#include "stdafx.h"
#include<string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <locale>

using namespace std;

static locale loc;

bool compareFunction(string a, string b){
 const collate<char>& coll = use_facet<collate<char> >(loc);
 int result = coll.compare ( a.data(), a.data()+a.length(), b.data(), b.data()+b.length());
 if(result==1)
		return false;
 return true;
}

int _tmain(int argc, _TCHAR* argv[])
	{

	vector<locale> vec_loc;
	vector<string> str_vec;
	vector<string>::iterator it;
	vector<locale>::iterator lit;
	string str_arr[5] = {"Ab", "bc", "ch", "cz", "cb"};
		//Note that ch will appear in a different order in Spanish due to the Spanish alphabet.

	for(int i = 0; i<5; i++){
		str_vec.push_back(str_arr[i]);
	}
	vec_loc.push_back( locale("English"));
	vec_loc.push_back( locale("German"));
	vec_loc.push_back( locale("Danish"));
	vec_loc.push_back( locale("Spanish"));

	for(lit = vec_loc.begin(); lit!=vec_loc.end(); ++lit){
		loc = *lit;
			sort (str_vec.begin(), str_vec.end(), compareFunction);
			for (it=str_vec.begin(); it!=str_vec.end(); ++it)
					cout << " " << *it;
	 cout << endl;
	}
	return 0;
}





