#pragma once
#include <string>
#include <iostream>
#include <fstream>

namespace OSRAM	{
	namespace UTILS {
		inline std::string read_file(std::string filename) 
		{
			std::cout << "[FILE] Reading File : " << filename << std::endl;
			
			std::ifstream stream(filename, std::ifstream::in);
			std::string str;

			if (stream) {
				// get length of file:
				stream.seekg(0, stream.end);
				int length = (const int)stream.tellg();
				stream.seekg(0, stream.beg);

				char * buffer = new char[length];

				// read data as a block:
				stream.read(buffer, length);
				std::cout << "[FILE] All characters read successfully." << std::endl;
				stream.close();

				// ...buffer contains the entire file...
				str = buffer;


				delete[] buffer;
			}
			std::cout << "[FILE] Successfully Read File: " << filename << std::endl;
			return str;
		}
	}
}