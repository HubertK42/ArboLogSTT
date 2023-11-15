
#include "../../audiohelper/src/audiohelper.h"
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
	sprintf(filepath, "%s", "./test.flac");
//---------------------------------------------------------		
//-------------------- scan start params
	std::cout << "TOLL!" << std::endl;
	audiohelper AH;
	AH.init_recIntoFile(filepath, ma_encoding_format_flac, ma_device_type_capture, 16000, 1, ma_format_s16);


	AH.start_rec();						//!< capture sound from e.g. micro 
		sleep(1);
	AH.stop();

	//AH.start_play(void *pBbuffer);		//!< play sound from pBuffer

	return 0;
}
