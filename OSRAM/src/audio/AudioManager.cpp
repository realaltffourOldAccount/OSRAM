#include "AudioManager.h" 

OSRAM::AUDIO::AudioManager::AudioManager()
{
	std::cout << "[AUDIO] Loading Audio PlaceHolders, this may take time . . . . " << std::endl;
	for (int i = 0; i < MAX_SCENES; i++)
	{
		m_Scenes[i] = new AudioScene;
		m_Scenes[i]->_audioCounter = 0;
		m_Scenes[i]->_context = 0;
		m_Scenes[i]->_name = "";
		m_Scenes[i]->_sceneID = MAX_SCENES + 1;

		for (int j = 0; j < MAX_AUDIO_OBJ; j++)
		{
			m_Scenes[i]->_audioObj[j]._gain = 0;
			m_Scenes[i]->_audioObj[j]._looping = 0;
			m_Scenes[i]->_audioObj[j]._name = "";
			m_Scenes[i]->_audioObj[j]._objID = MAX_AUDIO_OBJ + 1;
			m_Scenes[i]->_audioObj[j]._pitch = 0;
			m_Scenes[i]->_audioObj[j]._placeTaken = false;
			m_Scenes[i]->_audioObj[j]._pos = glm::vec3(0.0f);
			m_Scenes[i]->_audioObj[j]._velocity = glm::vec3(0.0f);
		}
	}

	m_Device = alcOpenDevice(nullptr);
	if (!m_Device)
	{
		std::cout << "[AUDIO] Device Creation . . . FAILED" << std::endl;
		return;
	}
	else
		std::cout << "[AUDIO] Device Creation . . . SUCCESS" << std::endl;
}

OSRAM::AUDIO::AudioManager::~AudioManager()
{

}

void OSRAM::AUDIO::AudioManager::DisplayDeviceList()
{
	std::cout << "[AUDIO] Testing Device Enumeration . . . " << std::endl;
	ALboolean enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT"); 
	if (enumeration == AL_FALSE)
	{
		std::cout << "[AUDIO] Device Enumeration . . . FAILED" << std::endl;
	}
	else
	{
		std::cout << "[AUDIO] Device Enumeration . . . SUCCESS" << std::endl << "[AUDIO] Listing Devices . . . " << std::endl;;
			const ALCchar *device = alcGetString(NULL, ALC_DEVICE_SPECIFIER), *next = alcGetString(NULL, ALC_DEVICE_SPECIFIER) + 1;
			size_t len = 0;

			fprintf(stdout, "[AUDIO] Devices list:\n");
			fprintf(stdout, "------------------------\n");
			while (device && *device != '\0' && next && *next != '\0') {
				fprintf(stdout, "[AUDIO] %s\n", device);
				len = strlen(device);
				device += (len + 1);
				next += (len + 2);
			}
			fprintf(stdout, "------------------------\n");
	}
}

void OSRAM::AUDIO::AudioManager::CheckError()
{
	ALCenum error =  alGetError();
	if (error != ALC_NO_ERROR)
	{
		std::cout << "[AUDIO] Error . . . " << std::endl;
	}
}

void OSRAM::AUDIO::AudioManager::AddScene(std::string name)
{
	m_Scenes[SceneCounter] = new AudioScene;
	m_Scenes[SceneCounter]->_name = name;
	m_Scenes[SceneCounter]->_sceneID = SceneCounter;
	m_Scenes[SceneCounter]->_audioCounter = 0;
	m_Scenes[SceneCounter]->_context = alcCreateContext(m_Device, NULL);



	SceneCounter++;
}

void OSRAM::AUDIO::AudioManager::RemoveScene(std::string name)
{
	for (int i = 0; i < MAX_SCENES; i++)
	{
		if (m_Scenes[i]->_name == name)
		{
			delete m_Scenes[i];
		}
	}
}

bool OSRAM::AUDIO::AudioManager::IsScene(std::string name)
{
	for (int i = 0; i < MAX_SCENES; i++)
	{
		if (m_Scenes[i]->_name == name)
		{
			return true;
		}
	}
	return false;
}

int OSRAM::AUDIO::AudioManager::GetSceneID(std::string name)
{
	for (int i = 0; i < MAX_SCENES; i++)
	{
		if (m_Scenes[i]->_name == name)
			return m_Scenes[i]->_sceneID;
	}
	return -1;
}

void OSRAM::AUDIO::AudioManager::AddAudioObject(int sceneID, std::string audioName, int pitch, glm::vec3 velocity, int gain, bool looping, glm::vec3 pos)
{
	int sceneID_array;
	for (int i = 0; i < MAX_SCENES; i++)
	{
		if (m_Scenes[i]->_sceneID == sceneID)
			sceneID_array = i;
	}

	AUDIO::AudioManager::AudioObject obj;
	obj._gain = gain;
	obj._looping = looping;
	obj._name = audioName;
	obj._objID = m_Scenes[sceneID_array]->_audioCounter;
	obj._pitch = pitch;
	obj._pos = pos;
	obj._velocity = velocity;
	obj._placeTaken = true;

	for (int i = 0; i < MAX_AUDIO_OBJ; i++)
	{
		if (m_Scenes[sceneID_array]->_audioObj[i]._placeTaken == false)
		{
			memcpy(&m_Scenes[sceneID_array]->_audioObj[i], &obj, sizeof(obj));
		}
	}

	m_Scenes[sceneID_array]->_audioCounter++;
}

bool OSRAM::AUDIO::AudioManager::IsAudioObject(int sceneID, std::string audioName)
{
	int sceneID_array;
	for (int i = 0; i < MAX_SCENES; i++)
	{
		if (m_Scenes[i]->_sceneID = sceneID)
			sceneID_array = i;
	}
	for (int i = 0; i < MAX_AUDIO_OBJ; i++)
	{
		if (m_Scenes[sceneID_array]->_audioObj[i]._name == audioName)
			return true;
		else return false;
	}
}

int OSRAM::AUDIO::AudioManager::GetAudioObjectID(int sceneID, std::string audioName)
{
	int sceneID_array;
	for (int i = 0; i < MAX_SCENES; i++)
	{
		if (m_Scenes[i]->_sceneID = sceneID)
			sceneID_array = i;
	}
	for (int i = 0; i < MAX_AUDIO_OBJ; i++)
	{
		if (m_Scenes[sceneID_array]->_audioObj[i]._name == audioName)
			return m_Scenes[sceneID_array]->_audioObj[i]._objID;
	}
}

void OSRAM::AUDIO::AudioManager::RemoveAudioObject(int sceneID, std::string audioName)
{
	int sceneID_array;
	for (int i = 0; i < MAX_SCENES; i++)
	{
		if (m_Scenes[i]->_sceneID == sceneID)
			sceneID_array = i;
	}

	for (int i = 0; i <MAX_AUDIO_OBJ; i++)
	{
		if (m_Scenes[sceneID_array]->_audioObj[i]._name == audioName)
		{
			m_Scenes[sceneID_array]->_audioObj[i]._gain = 0;
			m_Scenes[sceneID_array]->_audioObj[i]._looping = 0;
			m_Scenes[sceneID_array]->_audioObj[i]._name = "";
			m_Scenes[sceneID_array]->_audioObj[i]._objID = MAX_AUDIO_OBJ + 1;
			m_Scenes[sceneID_array]->_audioObj[i]._pitch = 0;
			m_Scenes[sceneID_array]->_audioObj[i]._placeTaken = false;
			m_Scenes[sceneID_array]->_audioObj[i]._pos = glm::vec3(0.0f);
			m_Scenes[sceneID_array]->_audioObj[i]._velocity = glm::vec3(0.0f);
		}
	}
}
