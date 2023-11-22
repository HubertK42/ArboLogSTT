#pragma once

#include "../../HTMLSocket/src/HTMLSocket.h"

//#############################################################################
//! soket class to send audio files to google STT cloud services and recieve
//! its transcriptitption to text
///
class GoogleSocketTTS : public HTML::HTMLSocket
{
	typedef HTML::HTMLSocket TInherited; 

	public:

		GoogleSocketTTS(Base::String APIKey);			//constructor
  		virtual ~GoogleSocketTTS();

	int requestTTSfromfile (const char* file); //!< sends the audio file to google STT and waits for the answer

	protected:

		Base::String m_ApiKey;		// google api key for excess
};