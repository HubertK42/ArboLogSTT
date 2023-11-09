
#include "../BaseLib/src/String.h"
#include <cassert>
#include <iostream>
#include <locale.h>

#include <chrono>



//! scanned command line parameters
struct _startparams
{
	std::string json_string;					// will contain the json string with eyescene parametes
	std::string image_path;						// will contain the path to a source image
	int 		width = -1;						// width of image if we use the image constructor
	int 		type  = -1;						// type of image if we use the image constructor
	int 		bshowPreviewImages = -1; 		// -1 not set, 0 do not display, 1 display inbetween images during tracing
	std::string previewPath;					// path for the images which are generated while tracing aka progress
	int			progressAdvancementStep = 0;	// advancement step of progress output in [%], e.g. 1 every 1%, 2 ever 2%, etc...
	bool 		runOnce = 0; 					// if true run once and terminate
	bool 		debuginfos = false;				// out put debug info as json
};

//#############################################################################
//! output source and destination image to console
_startparams  handleConsoleInput(int argc, char *argv[])
{	
	_startparams StartParams;
	Base::String scannedParams;
	scannedParams.format("proceesing cmd (argc: %i) ->", argc);
	// out put command an scan for parameters and store parameters
	
	for (int i = 0 ; i < argc; i++)
	{
		std::string arg = argv[i];
		scannedParams += Base::String::_format ("%s, ", arg.c_str());
		
		// check output progress percentage steps
		if (arg.find("-a") != std::string::npos &&
			argc > i+1)
		{
			i++;
			StartParams.progressAdvancementStep = atoi(argv[i]);
			scannedParams += Base::String::_format ("%s, ", argv[i]);
		}
		else
		// check run once mode
		if (arg.find("-O") != std::string::npos)
		{
			StartParams.runOnce = true;
		}
		else
		// check for debug mode
		if (arg.find("-b") != std::string::npos)
		{
			StartParams.debuginfos = true;
		}
		else
		// check if preview images should be displayed
		if (arg.find("-i") != std::string::npos &&
			argc > i+1)
		{
			i++;
			StartParams.bshowPreviewImages = atoi(argv[i]);
			scannedParams += Base::String::_format ("%s, ", argv[i]);
		}
		else
		// check for json string
		if (arg.find("-j") != std::string::npos &&
			argc > i+1 )  // do we have at least one more argument
		{
			i++;
			StartParams.json_string = argv[i];
			scannedParams += Base::String::_format ("%s, ", argv[i]);
		}
		else
		// check for source image file path
		if (arg.find("-f") != std::string::npos &&
			argc > i+1 )  // do we have at least one more argument
		{
			i++;
			StartParams.image_path = argv[i];
			scannedParams += Base::String::_format ("%s, ", argv[i]);
		}
		else
		// check for image width for constructor
		if (arg.find("-w") != std::string::npos &&
			argc > i+1 )  // do we have at least one more argument
		{
			i++;
			StartParams.width = atoi(argv[i]);
			//scannedParams += Base::String::_format ("%s, ", argv[i]);
			scannedParams += argv[i];
		}
		else
		// check for image type for constructor
		if (arg.find("-t") != std::string::npos &&
			argc > i+1 )  // do we have at least one more argument
		{
			i++;
			StartParams.type = atoi(argv[i]);
			scannedParams += Base::String::_format ("%s, ", argv[i]);
		}
		else

		if(	arg.find("-p") != std::string::npos &&
			argc > i+1)
		{
			i++;
			StartParams.previewPath = argv[i];
			scannedParams += Base::String::_format ("%s, ", argv[i]);
		}
		else
		// display info help
		if (arg.find("-h") != std::string::npos)
		{
			std::cout << "\nUsage: " << std::endl;
			std::cout << "-h\t: show this help info" << std::endl;
			std::cout << "-a [int]: advancement step of progress output in [%], e.g. 1 every 1%, 2 ever 2%, etc..." << std::endl;
			std::cout << "-j [str]: json string with eye prameters" << std::endl;
			std::cout << "-b \t: output debug info as json string" << std::endl;
			std::cout << "-f [str]: file path to source image" << std::endl;
			std::cout << "-w [int]: width of image for using the image constructor" << std::endl;
			std::cout << "-O\t: set the run once method, a single trace run will be executed" << std::endl;
			std::cout << "-r [int]: number of rays per pixel in the source image" << std::endl;
			std::cout << "-p [str]: path for the preview images" << std::endl;
			std::cout << "-i [int]: show preview pictures [0,1] " << std::endl;
			std::cout << "-s [str]: path to store the traced imag to overwriting default \"./Destination.png\"" << std::endl;
			std::cout << "-t [int]: image constr. type:" << std::endl;
			std::cout << "\t\t\t\t0 = plain image with center dot" << std::endl;
			std::cout << "\t\t\t\t1 = cross" << std::endl;
			std::cout << "\t\t\t\t2 = circle" << std::endl;
			std::cout << "\t\t\t\t3 = horizontal line" << std::endl;
			std::cout << "\t\t\t\t4 = vertical line" << std::endl;
			std::cout << "\t\t\t\t5 = point" << std::endl;
			std::cout << "\t\t\t\t6 = filled white circle" << std::endl;
		}
	} // end-for-arguments

	std::cout << std::endl;
	return StartParams;

}
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

//---------------------------------------------------------		
//-------------------- scan start params
	_startparams StartParams;
	StartParams = handleConsoleInput(argc, argv);

	return 0;
}
