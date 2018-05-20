#pragma once

#include <al.h>
#include <alc.h>
#include <iostream>

#include <string>

#include <GLM\glm.hpp>

namespace OSRAM {
	namespace AUDIO {
		class AudioManager
		{
#define MAX_SCENES 15
#define MAX_AUDIO_OBJ 25
		private:
			ALCdevice *m_Device;

			class AudioObject {
			public:
				int _objID;
				std::string _name;
				glm::vec3 _pos;
				glm::vec3 _velocity;
				int _pitch;
				int _gain;
				bool _looping;
				bool _placeTaken = false;
			};

			class AudioScene {
			public:
				int _sceneID;
				std::string _name;
				ALCcontext *_context;
				AudioObject _audioObj[MAX_AUDIO_OBJ];
				int _audioCounter;
			};
			AudioScene *m_Scenes[MAX_SCENES];

			int SceneCounter = 0;
		public:

			AudioManager();
			~AudioManager();

			void DisplayDeviceList();

			void CheckError();

			// Scene Functions
			void AddScene(std::string name);
			void RemoveScene(std::string name);
			bool IsScene(std::string name);
			int GetSceneID(std::string name);

			// Audio Objects
			void AddAudioObject(int sceneID, std::string audioName, int pitch, glm::vec3 velocity, int gain,  bool looping, glm::vec3 pos);
			void RemoveAudioObject(int sceneID, std::string audioName);
			bool IsAudioObject(int sceneID, std::string audioName);
			int GetAudioObjectID(int sceneID, std::string audioName);
		};	
	}
}