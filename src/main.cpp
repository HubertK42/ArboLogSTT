
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

	//-- disable logfile output
	Base::LogFile::disableConsoleOutput(true);
	Base::LogFile::disableFile(true);
//---------------------------------------------------------		
//-------------------- scan start params

	//--- read api key
	//Base::String key, keyfile = "/home/hubert/.keys/googleApi.txt";
	Base::String key, keyfile = "~/.keys/googleApi.txt";
	if (!key.readAscii(keyfile))
		std::cerr << "GoogleSocketTTS()::Key could not be read, File [" << keyfile << "]" << std::endl;

	key = key.substr(0, key.size()-1);
    audio::ttsrec testA;
    
    char file[50] = "/home/hubert/projects/baum16000.wav";
	// char file[50]= "/home/hubert/projects/baum1600base64.dat";

	//testA.testrec(file);

	//testA.playFromFile(file);

	GoogleSocketTTS stt(key);

//	stt.requestTTSfromfile("NoFile");
	//stt.testG(file);
	stt.requestTTSfromfile(file);
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
