#pragma once
#include <string>
#include <iostream>
#include <fstream>

namespace OSRAM {
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
				std::cout << "[FILE] File Reading: " + filename << " . . . SUCCESS" << std::endl;;
				return str1;
			}
			else
				std::cout << "[FILE] File Reading: " + filename << " . . . FAIL" << std::endl;
			return nullptr;
		}

		inline void write_file(std::string filename, std::string data, bool clearfile)
		{
			std::cout << "[FILE] Writing File: " << filename << std::endl;

			std::ofstream write(filename);

			if (clearfile)
				write.clear(0);

			if (write.is_open())
			{
				write << data;
				write.close();

				std::cout << "[FILE] File Writing: " + filename << " . . . SUCCESS" << std::endl;
			}
			else
			{
				std::cout << "[FILE] File Writing: " + filename << " . . . FAIL" << std::endl;
			}
		}
	};
}