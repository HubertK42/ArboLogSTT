#include "GoogleSocketSTT.h"
#include "STTBobConstructor.h"

#include <iostream>

#define _NAME		"name"
#define _METATDATA	"metadata"
#define _TYPE		"@type"
#define _API_URL	"https://speech.googleapis.com/v1/speech:recognize"
#define _API_KEY	"AIzaSyCu0TUWxK8P-qzFDrWciDGnrvesvWGd-aM"


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

#include <iostream>
#include <curl/curl.h>



// Function to handle the response from cURL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

int GoogleSocketTTS::testG() 
{
	Base::String dataStr;
	dataStr.readAscii("./Testbase64.dat");
    // Google STT API endpoint
    std::string api_url = "https://speech.googleapis.com/v1/speech:recognize";

    // API Key or OAuth2 credentials (replace YOUR_API_KEY with your actual API key)
    std::string api_key = "YOUR_API_KEY";

    // File containing audio data to be transcribed
    std::string audio_file_path = "./pow.wav";

    // Recognition Metadata
    std::string recognition_metadata = createRecognitionMetadata("testchat").toJSON().c_str();
/* R"(
        {
            "interactionType": "DISCUSSION",
            "industryNaicsCodeOfAudio": 123456,
            "microphoneDistance": "NEARFIELD",
            "originalMediaType": "AUDIO",
            "recordingDeviceType": "SMARTPHONE",
            "recordingDeviceName": "Pixel 4",
            "originalMimeType": "audio/flac"
        }
    )";
*/
	//std::cout << recognition_metadata << std::endl;
	Base::Bob params;
	params["config"] = createRecogConfig("myts", 16000);
	params["audio"] = createRecognitionAudio("", dataStr.c_str());
/*	recognition_metadata = R"(
		{
		"config":{
		"languageCode":"LANGUAGE_CODE",
		"encoding":ENCODING",
		"sampleRateHertz":SAMPLE_RATE_HERTZ",
		"enableTimeWordOffsets":ENABLE_TIME_WORD_OFFSETS",
		},
		"audio":{"uri":"gs://STORAGE_BUCKET"},
		)";*/

	std::cout << params["config"].toJSON() << std::endl;
	recognition_metadata = params.toJSON();

    // Build the cURL command
    CURL* curl = curl_easy_init();
    if (curl) {
        // Set the URL
        std::string url_with_key = api_url + "?key=" + api_key;
        curl_easy_setopt(curl, CURLOPT_URL, url_with_key.c_str());

        // Set the audio file
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "@audio_file_path");

        // Set the Recognition Metadata
        curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, recognition_metadata.c_str());

        // Set the callback function to handle the response
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        // Print the response
        std::cout << "Response from Google STT API:\n" << response << std::endl;
    }

    return 0;
}
