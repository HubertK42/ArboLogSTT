#define MINIAUDIO_IMPLEMENTATION
#include "ttsrec.h"
//#include "../../audiohelper/src/audiohelper.h"
#include "../../audiohelper/src/miniAudio.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

//#define SAMPLE_RATE		44100  			//!<  sample rate used for recording and playback
#define SAMPLE_RATE		16000  			//!<  sample rate used for recording and playback
//#define BIT_DEPTH		ma_format_f32 	//!< bits per samples
#define BIT_DEPTH		ma_format_s16 	//!< bits per samples
#define MIC_CHANNELS	1				//!< only use mono for recording
#define OUT_CHANNELS	1				//!< use stereo for playback

namespace audio
{
	//######################################################################	
	//! callback routine of mini audio
	void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
	{
		ma_encoder* pEncoder = (ma_encoder*)pDevice->pUserData;
		ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;

		if (pOutput && pDecoder)
		{
			ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);
		}
		else
		if (pInput && pEncoder)
		{
			ma_encoder_write_pcm_frames(pEncoder, pInput, frameCount, NULL);
		}
		else
		{
			
			std::cerr << "audio:: pOutput:" << &pOutput << "  pIutput:" << &pInput << std::endl;  
			std::cerr << "audio:: pDecoder:" << &pDecoder << "  pEncoder:" << &pInput << std::endl;
			exit (1);
		}	


		(void)pOutput; //@@ TODO  what is the purpose of this??
	}

	//#########################################################################
	int ttsrec::testrec(char* file)
	{
		ma_result 			result;
		ma_encoder_config 	encoderConfig;
		ma_encoder 			encoder;
		ma_device_config 	deviceConfig;
		ma_device 			device;

		encoderConfig = ma_encoder_config_init(ma_encoding_format_wav, BIT_DEPTH, MIC_CHANNELS, SAMPLE_RATE);

		if (ma_encoder_init_file(file, &encoderConfig, &encoder) != MA_SUCCESS) 
		{
			printf("Failed to initialize output file.\n");
			return -1;
		}

		deviceConfig = ma_device_config_init(ma_device_type_capture);
		deviceConfig.capture.format   = encoder.config.format;
		deviceConfig.capture.channels = encoder.config.channels;
		deviceConfig.sampleRate       = encoder.config.sampleRate;
		deviceConfig.dataCallback     = data_callback;
		deviceConfig.pUserData        = &encoder;

		result = ma_device_init(NULL, &deviceConfig, &device);
		if (result != MA_SUCCESS) {
			printf("Failed to initialize capture device.\n");
			return -2;
		}

		result = ma_device_start(&device);
		if (result != MA_SUCCESS) {
			ma_device_uninit(&device);
			printf("Failed to start device.\n");
			return -3;
		}

		printf("Press Enter to stop recording...\n");
		getchar();
		
		ma_device_uninit(&device);
		ma_encoder_uninit(&encoder);

		return 0;
	}

//#########################################################################
	int ttsrec::playFromFile(const char* file)
	{
		ma_result 			result;
		ma_decoder 			decoder;
		ma_device_config 	deviceConfig;
		ma_device 			device;

		result = ma_decoder_init_file(file, NULL, &decoder);
		if ( result != MA_SUCCESS) 
		{
			std::cerr << "could not load file[: " << file << "] . Err-Code:" << result << std::endl;
			return -1;
		}
		deviceConfig 					= ma_device_config_init(ma_device_type_playback);
    	deviceConfig.playback.format	= decoder.outputFormat;
    	deviceConfig.playback.channels	= decoder.outputChannels;
    	deviceConfig.sampleRate			= decoder.outputSampleRate;
    	//deviceConfig.sampleRate		= SAMPLE_RATE;
		deviceConfig.dataCallback		= data_callback;
    	deviceConfig.pUserData			= &decoder;
		
		result = ma_device_init(NULL, &deviceConfig, &device);
		if (result != MA_SUCCESS) 
		{
			std::cerr << "Failed to open playback. Err-Code:" << result << std::endl;
			return -2;
		}

		result = ma_device_start(&device);
		if (result != MA_SUCCESS) 
		{
			ma_device_uninit(&device);
			
			std::cerr << "Failed to start playback device. Err-Code:" << result << std::endl;
			return -3;
		}
		
		ma_device_uninit(&device);
		ma_decoder_uninit(&decoder);

		return 0;
	}
}