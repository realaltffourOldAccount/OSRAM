#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include "fileutils.h"
#include "Timer.h"

#define LOG_FILE_PATH "Log.txt"

namespace OSRAM
{
	namespace UTILS
	{
		class Log
		{
		private:
			std::vector<std::string> m_Log;

			bool m_OnErrorFlushToFile = true;
			Timer m_Timer;
			struct PREFIX
			{
				std::string _Window = "[WINDOW]";
				std::string _Shaders = "[SHADERS]";
				std::string _MVP = "[MVP]";
				std::string _Sprite2D = "[SPRITE]";
				std::string _Sprite2DTex = "[TEXTURE]";
				std::string _Input = "[INPUT]";
				std::string _Audio = "[AUDIO]";
				std::string _FileUtil = "[FILE]";
			};
		public:
		
			PREFIX _prefix;
			enum TYPE
			{
				MSG_NORMAL = 0,
				MSG_WARNING,
				MSG_ERROR
			};

			Log(bool flushToFileERROR = true);
			void LogMSG(TYPE type, std::string prefix, std::string msg);
			
			void FlushAllToScreen();
			void FlushToFile();
			void ClearLog();
			void ClearCMD();
			void ClearLogFile();
		};
	}
}