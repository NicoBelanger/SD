#include "tools.h"

vector<string> tools::split(string string2split, char delimiter)
{
	std::replace(string2split.begin(), string2split.end(), delimiter, ' ');  // replace ':' by ' '

	vector<string> array;
	stringstream ss(string2split);
	string temp;

	while (ss >> temp)
		array.push_back(temp);
	
	return array;
}

int tools::string2int(string p_str)
{
	stringstream ss(p_str);

	int x = 0;
	ss >> x;

	return x;
}
