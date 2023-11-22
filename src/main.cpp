
//#include "../../audiohelper/src/audiohelper.h"
#include "ttsrec.h"
#include "GoogleSocketSTT.h"

#include <cassert>
#include <iostream>
#include <locale.h>

#include <chrono>


//#############################################################################
//! MAIN
///

int main(int argc, char *argv[])

{
	//--- Set Locale
	setlocale(LC_ALL, "");
	std::setlocale(LC_ALL, "C");
	char filepath[245];
	//sprintf(filepath, "%s", "./test.flac");
	sprintf(filepath, "%s", "./test2.wav");
//---------------------------------------------------------		
//-------------------- scan start params

    audio::ttsrec testA;
    
    char file[20]= "./pow.wav";

	//testA.testrec(file);

	testA.playFromFile(file);

	GoogleSocketTTS stt("MEYAPIKEY");

	stt.requestTTSfromfile("NoFile");

   
/*
	
	audiohelper AH;
	//AH.init_recIntoFile(filepath, ma_encoding_format_flac, ma_device_type_capture, 16000, 1, ma_format_s16);
	AH.init_recIntoFile(filepath, ma_encoding_format_wav, ma_device_type_capture, 16000, 1, ma_format_s16);

	std::cout << "start rec!" << std::endl;
	AH.start_rec();						//!< capture sound from e.g. micro 
		sleep(3);
	AH.stop();
	std::cout << "start stopped!" << std::endl;

	//AH.start_play(void *pBbuffer);		//!< play sound from pBuffer
*/
	return 0;
}
