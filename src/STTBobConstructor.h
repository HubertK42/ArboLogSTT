#pragma once
#include "../../BaseLib/src/Bob.h"

//----- helper to cunstruct STT needed bob structurs

//! create the whole request to be send to googles STT
Base::Bob createRequest(Base::String topic, int samplerate,Base::String uri, const char* pBuffer);

//! create the recognition config data 
Base::Bob createRecogConfig(Base::String topic, int samplerate);


//! create the recognition meta data specifing the source
Base::Bob createRecognitionMetadata(Base::String topic); 

//! create the RecognitionAudio meta data specifing the source of the audio either file or cloud storage
Base::Bob createRecognitionAudio(Base::String uri, const char* pBuffer); 