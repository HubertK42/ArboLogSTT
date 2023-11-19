
//#include "../../audiohelper/src/audiohelper.h"
#include "ttsrec.h"
#include <cassert>
#include <iostream>
#include <locale.h>

#include <chrono>


//#############################################################################
//! MAIN
///
///	1) scan command line parameters
///	2) create source image either from file or via image constructor
///	3) create eye scene parameters, either from command line parameter or via createEyeparams()
///	4) construct scene
///	5) create tracer
/// 6) 	a) run once and terminate
///		b) do other stuff like optimizations
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

    audio::ttsrec test;
    
    char file[20]= "./pow.wav";

    test.testrec(file);
    test.testrec(file);

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
