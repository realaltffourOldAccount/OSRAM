#include "AudioManager.h"


OSRAM::AUDIO::AudioManager::AudioManager()
{
	init();
}

OSRAM::AUDIO::AudioManager::~AudioManager()
{
	for (int i = 0; i < m_BufferObjects.size(); i++)
	{
		alDeleteBuffers(1, &m_BufferObjects[i]._bufferOBJ);
	}

	for (int i = 0; i < m_AudioObjects.size(); i++)
	{
		alDeleteBuffers(1, &m_AudioObjects[i]._sourceOBJ);
	}

	m_BufferObjects.clear();
	m_AudioObjects.clear();

	alcMakeContextCurrent(NULL);
	alcDestroyContext(m_Context);
	alcCloseDevice(m_Device);
}

void OSRAM::AUDIO::AudioManager::Update()
{
	checkError();
}

void OSRAM::AUDIO::AudioManager::SetListener(ListenerDATA data)
{
	m_ListenerPOS = data._pos;
	m_ListenerVEL = data._velocity;
	m_ListenerORI = data._ori;

	alListener3f(AL_POSITION, m_ListenerPOS.x, m_ListenerPOS.y, m_ListenerPOS.z);
	checkError("Set Listener Position . . . FAIL", "Set Listener Position . . . SUCCESS");
	alListener3f(AL_VELOCITY, m_ListenerVEL.x, m_ListenerVEL.y, m_ListenerVEL.z);
	checkError("Set Listener Velocity . . . FAIL", "Set Listener Velocity . . . SUCCESS");
	alListenerfv(AL_ORIENTATION, m_ListenerORI);
	checkError("Set Listener Orientation . . . FAIL", "Set Listener Orientation . . . SUCCESS");
}

void OSRAM::AUDIO::AudioManager::AddAudioObject(AudioObject obj)
{
	alGenSources(1, &obj._sourceOBJ);
	checkError("Generate Audio Source For: " + obj._name + " . . . FAIL",
		"Generate Audio Source For: " + obj._name + " . . . SUCCESS");
	alSourcef(obj._sourceOBJ, AL_PITCH, obj._pitch);
	checkError("Set Audio Pitch For: " + obj._name + " . . . FAIL", 
		"Set Audio Pitch For: " + obj._name + " . . . SUCCESS");
	alSourcef(obj._sourceOBJ, AL_GAIN, obj._gain);
	checkError("Set Audio Gain For: " + obj._name + " . . . FAIL",
		"Set Audio Gain For: " + obj._name + " . . . SUCCESS");
	alSource3f(obj._sourceOBJ, AL_POSITION, obj._pos.x, obj._pos.y, obj._pos.z);
	checkError("Set Audio Position For: " + obj._name + " . . . FAIL",
		"Set Audio Position For: " + obj._name + " . . . SUCCESS");
	alSource3f(obj._sourceOBJ, AL_VELOCITY, obj._velocity.x, obj._velocity.y, obj._velocity.z);
	checkError("Set Audio Velocity For: " + obj._name + " . . . FAIL", 
		"Set Audio Velocity For: " + obj._name + " . . . SUCCESS");
	alSourcei(obj._sourceOBJ, AL_LOOPING, (int)obj._looping);
	checkError("Set Audio Looping For: " + obj._name + " . . . FAIL",
		"Set Audio Looping For: " + obj._name + " . . . SUCCESS");

	m_AudioObjects.push_back(obj);
}

void OSRAM::AUDIO::AudioManager::RemoveAudioObject(std::string name)
{
	for (int i = 0; i < m_AudioObjects.size(); i++)
	{
		if (m_AudioObjects[i]._name == name)
		{
			m_AudioObjects.erase(m_AudioObjects.begin() + i);
			break;
		}
	}
}

void OSRAM::AUDIO::AudioManager::AddBufferObject(BufferObject obj)
{
	alGenBuffers(1, &obj._bufferOBJ);
	checkError("Buffer Generation For: " + obj._name + " . . . FAIL",
		"Buffer Generation For: " + obj._name + " . . . SUCCESS");

	std::cout << "[AUDIO] Reading File: " << obj._PATH << " . . . " << std::endl;
	alutLoadWAVFile(obj._PATH, &obj._format, &obj._data, &obj._size, &obj._freq, &obj._loop);
	
	if (obj._data != NULL)
		std::cout << "[AUDIO] Reading File: " << obj._PATH << ". . . SUCCESS" << std::endl;
	else std::cout << "[AUDIO] Reading File: " << obj._PATH << ". . . FAIL" << std::endl;
	checkError();

	alBufferData(obj._bufferOBJ, obj._format, obj._data, obj._size, obj._freq);
	checkError("Buffering Data For: " + obj._name + " . . . FAIL",
		"Buffering Data For: " + obj._name + " . . . SUCCESS");

	m_BufferObjects.push_back(obj);
}

void OSRAM::AUDIO::AudioManager::RemoveBufferObject(std::string name)
{
	for (int i = 0; i < m_BufferObjects.size(); i++)
	{
		if (m_BufferObjects[i]._name == name)
		{
			m_BufferObjects.erase(m_BufferObjects.begin() + i);
		}
	}
}

void OSRAM::AUDIO::AudioManager::SetBufferOBJForAudioOBJ(std::string _audioOBJ, std::string _bufferOBJ)
{
	int audio_ID;
	for (int i = 0; i < m_AudioObjects.size(); i++)
	{
		if (m_AudioObjects[i]._name == _audioOBJ)
		{
			audio_ID = i;
			break;
		}
	}

	int buffer_ID;
	for (int i = 0; i < m_BufferObjects.size(); i++)
	{
		if (m_BufferObjects[i]._name == _bufferOBJ)
		{
			buffer_ID = i;
			break;
		}
	}

	m_AudioObjects[audio_ID]._bindedBuffer = &m_BufferObjects[buffer_ID];
	alSourcei(m_AudioObjects[audio_ID]._sourceOBJ, AL_BUFFER, m_BufferObjects[buffer_ID]._bufferOBJ);
	checkError("Buffer: " + m_AudioObjects[audio_ID]._name + " set for Audio OBJ: " +
		m_BufferObjects[buffer_ID]._name + ". . . ERROR",
		"Buffer: " + m_AudioObjects[audio_ID]._name + " set for Audio OBJ: " +
		m_BufferObjects[buffer_ID]._name + ". . . SUCCESS");
}

void OSRAM::AUDIO::AudioManager::PlayAudioOBJ(std::string name)
{
	int audioID;
	for (int i = 0; i < m_AudioObjects.size(); i++)
	{
		if (m_AudioObjects[i]._name == name)
		{
			audioID = i;
			break;
		}
	}

	alSourcePlay(m_AudioObjects[audioID]._sourceOBJ);
	checkError("Object " + m_AudioObjects[audioID]._name + " Play . . . ERROR"
		,"Object " + m_AudioObjects[audioID]._name + " Play . . . SUCCESS");
}

void OSRAM::AUDIO::AudioManager::StopAudioOBJ(std::string name)
{
	int audioID;
	for (int i = 0; i < m_AudioObjects.size(); i++)
	{
		if (m_AudioObjects[i]._name == name)
		{
			audioID = i;
			break;
		}
	}
	alSourceStop(m_AudioObjects[audioID]._sourceOBJ);
}

void OSRAM::AUDIO::AudioManager::checkError(std::string errorMSG, std::string noERRORMSG)
{
	ALenum error;
	error = alGetError();
	if (error != AL_NO_ERROR)
	{
		std::cout << "[AUDIO] Error Happened . . . " << std::endl;
		if (errorMSG == "")
			std::cout << "[AUDIO] " << errorMSG << std::endl;
	}

	else if (noERRORMSG != "")
		std::cout << "[AUDIO] " << noERRORMSG << std::endl;
}

void OSRAM::AUDIO::AudioManager::list_device(const char* devices)
{
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;

	fprintf(stdout, "[AUIDO] Devices list:\n");
	fprintf(stdout, "-----------------------------------\n");
	while (device && *device != '\0' && next && *next != '\0') {
		fprintf(stdout, "[AUIDO] %s\n", device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	fprintf(stdout, "-----------------------------------\n");
}

void OSRAM::AUDIO::AudioManager::init()
{
	m_Device = alcOpenDevice(NULL);


	m_SupportsEnumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	if (m_SupportsEnumeration == AL_FALSE)
		std::cout << "[AUDIO] Enumeration not supported . . ." << std::endl;
	else std::cout << "[AUDIO] Enumeration supported . . ." << std::endl;

	list_device(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

	m_Context = alcCreateContext(m_Device, NULL);
	if (!alcMakeContextCurrent(m_Context))
		std::cout << "[AUDIO] Make Context Current . . . FAIL " << std::endl;
	else std::cout << "[AUDIO] Make Context Current . . . SUCCESS" << std::endl;
}