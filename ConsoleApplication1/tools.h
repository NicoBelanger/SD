#pragma once
#include <string>
#include <vector>
#include <array>
#include <sstream>

using namespace std;

class tools
{
	public:
		static vector<string> split(string string2split, char delimiter);
		static int string2int(string p_str);

	private:
		tools() {}
};

