#include "GoogleSocketSTT.h"
#include "STTBobConstructor.h"

#include <iostream>

#define _NAME		"name"
#define _METATDATA	"metadata"
#define _TYPE		"@type"
#define _API_URL	"https://speech.googleapis.com/v1/speech:recognize"
#define _API_KEY	"yourgoolge api key"


//! constructor
GoogleSocketTTS::GoogleSocketTTS(Base::String APIKey):
	Base::LogFileSupport("GoogleSocketTTS", Base::eMajor), 
	TInherited("GoogleSocketTTS", Base::eMajor),  
	 m_ApiKey(APIKey)		
{
			
}

//! destructor
GoogleSocketTTS::~GoogleSocketTTS()
{
}

//#############################################################################
//! sends the audio file to google STT and waits for the answer
/// WARNING: this file must be shorter than 60 s, otherwise use Google Cloud Storage
///
///	\param file path to the file to be transcripted
///	\return 	error code
///
int GoogleSocketTTS::requestTTSfromfile (const char* file)
{
	Base::Bob BRC = createRequest("dictate", 16000,"UIR", NULL);

	std::cout << BRC.toJSON() << std::endl;
	
//	Base::Bob BRC = createRecogConfig("dictate", 16000);		// "outputConfig"
	return 0;
} 

/*
{
  "config": {
    object (RecognitionConfig)
  },
  "audio": {
    object (RecognitionAudio)
  },
  "outputConfig": {
    object (TranscriptOutputConfig)
  }
}*/