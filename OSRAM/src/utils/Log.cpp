#include "Log.h"

OSRAM::UTILS::Log::Log(bool flushToFileError)
{
	m_OnErrorFlushToFile = flushToFileError;

	m_Timer.Start();
}

void OSRAM::UTILS::Log::LogMSG(TYPE type, std::string prefix, std::string msg)
{
	std::string final_MSG;

	float time = m_Timer.get();
	final_MSG =  "[" + std::to_string(time) + "] " + prefix + " " + msg;

	switch (type)
	{
	case OSRAM::UTILS::Log::MSG_NORMAL:
		std::cout << final_MSG << std::endl;
		break;
	case OSRAM::UTILS::Log::MSG_WARNING:
		std::clog << final_MSG << std::endl;
		break;
	case OSRAM::UTILS::Log::MSG_ERROR:
	{
		std::cerr << final_MSG << std::endl; 
		if (m_OnErrorFlushToFile)
		{
			m_Log.push_back(final_MSG);
			this->FlushToFile();
		}
	}
		break;
	default:
		std::cerr << "[LOG] Stream Specifier Missing . . . " << std::endl;
		break;
	}

	m_Log.push_back(final_MSG);
}

void OSRAM::UTILS::Log::FlushAllToScreen()
{
	for (int i = 0; i < m_Log.size(); i++)
	{
		std::cout << m_Log[i] << std::endl;
	}
}

void OSRAM::UTILS::Log::FlushToFile()
{
	std::string data;
	for (int i = 0; i < m_Log.size(); i++)
	{
		data.append(m_Log[i] + "\n");
	}

	write_file(LOG_FILE_PATH, data, true);
}

void OSRAM::UTILS::Log::ClearLog()
{
	m_Log.clear();
}

void OSRAM::UTILS::Log::ClearCMD()
{
	system("CLS");
}

void OSRAM::UTILS::Log::ClearLogFile()
{
	OSRAM::UTILS::write_file(LOG_FILE_PATH, "", true);
}