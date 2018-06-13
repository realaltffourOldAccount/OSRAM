#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <GLM\glm.hpp>
#include "..\utils\ALUT\alut.h"
#include <AL\al.h>
#include <AL\alc.h>


namespace OSRAM
{
	namespace AUDIO
	{
		class AudioManager
		{
		public:
			struct ListenerDATA
			{
				ALfloat _ori[6];
				glm::vec3 _pos;
				glm::vec3 _velocity;
			};
			struct BufferObject
			{
				std::string _name;
				ALuint _bufferOBJ;
				ALsizei _size;
				ALsizei _freq;
				ALenum _format;
				ALvoid *_data;
				char* _PATH;
				ALboolean _loop;
			};
			struct AudioObject
			{
				std::string _name;
				ALuint _sourceOBJ;
				int _pitch;
				int _gain;
				glm::vec3 _pos;
				glm::vec3 _velocity;
				ALboolean _looping;
				BufferObject *_bindedBuffer;
			};
		private:
			ALCdevice *m_Device;
			ALCcontext *m_Context;
			bool m_SupportsEnumeration;

			
			void list_device(const char *devices);
			void checkError(std::string errorMSG = "", std::string noERRORMSG = "");

			void init();


			std::vector<AudioObject> m_AudioObjects;
			std::vector<BufferObject> m_BufferObjects;

			glm::vec3 m_ListenerPOS;
			glm::vec3 m_ListenerVEL;
			float* m_ListenerORI;
		public:
			AudioManager();
			~AudioManager();

			void Update();
			void SetListener(ListenerDATA data);

			void AddAudioObject(AudioObject obj);
			void RemoveAudioObject(std::string name);

			void AddBufferObject(BufferObject obj);
			void RemoveBufferObject(std::string name);

			void SetBufferOBJForAudioOBJ(std::string _audioOBJ, std::string _bufferOBJ);

			void PlayAudioOBJ(std::string name);
			void StopAudioOBJ(std::string name);
		};
	}
}