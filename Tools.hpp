#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template<typename typC>
istream &operator >> (istream &_cin,vector<typC> &_vec) {
	for (size_t i = 0; i < _vec.size(); i++)
		_cin >> _vec[i];
	return (_cin);
}

template<typename typC>
ostream &operator << (ostream &_cout,vector<typC> &_vec) {
	if (_vec.size() == 0) return (_cout);

	for (size_t i = 0; i < _vec.size() - 1; i++)
		_cout << _vec[i] << " ";
	_cout << _vec[_vec.size() - 1] << endl;
	return (_cout);
}

void fatal_error(string msg) {
	cerr << msg << endl;
	exit(1);
}


string hashVector(vector<vector<short>> &puzzle) {
	string hash = "";
	for (auto &line : puzzle)
		for (auto &val : line)
			hash += to_string(val) + " ";
	return hash;
}	
