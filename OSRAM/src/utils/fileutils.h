#pragma once
#include <string>
#include <iostream>
#include <fstream>

namespace OSRAM	{
	namespace UTILS {
		inline std::string read_file(std::string filename)
		{
			std::cout << "[FILE] Reading File : " << filename << std::endl;

			std::ifstream read(filename);
			std::string str, str1;

			int index = 0;
			if (read.is_open())
			{
				getline(read, str);
				while (read)
				{
					str1 += str + "\n";
					getline(read, str);
				}
				//cout << str1 << endl;
				return str1;
			}
			else
				std::cout << "[FILE]File Could Not Be Opened . . . " + filename << std::endl;
		}
	}
}