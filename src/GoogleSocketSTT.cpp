#include "GoogleSocketSTT.h"
#include "STTBobConstructor.h"
#include "../../audiohelper/src/Base64_de_encode/base64.h"

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
int GoogleSocketTTS::requestTTSfromfile (const char* wavfile)
{
	std::string base64String = fileToBase64(wavfile);

	if (base64String.empty())
		std::cout << "file convert to base 64 failed: " << wavfile << std::endl;

	Base::Bob BRC = createRequest("dictate", 16000, "", base64String.c_str());

	std::cout << BRC["config"].toJSON() << std::endl;

	Base::String response;
	Base::String PostData = BRC.toJSON();
	// create header
 // Set the URL
        std::string url_with_key = _API_URL + std::string("?key=") + _API_KEY;
      //  curl_easy_setopt(curl, CURLOPT_URL, url_with_key.c_str());
 
        // Set the Recognition Metadata
        curl_slist* pHeaders = NULL;
        pHeaders = curl_slist_append(pHeaders, "Content-Type: application/json");
        pHeaders = curl_slist_append(pHeaders, "Accept: application/json");
        pHeaders = curl_slist_append(pHeaders, "charset: utf-8");
        pHeaders = curl_slist_append(pHeaders, "User-Agent: Mozilla/5.0");

		HttpsPostHeader(url_with_key, "", PostData, pHeaders, response);

		std::cout << response << std::endl;
      //  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	
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

int GoogleSocketTTS::testG(const char* file) 
{
	Base::String dataStr;
	bool bFile= dataStr.readAscii(file);

	if (!bFile)
		std::cout << "file not found:" << file << std::endl;

    // Google STT API endpoint
    std::string api_url = "https://speech.googleapis.com/v1/speech:recognize";

    // API Key or OAuth2 credentials (replace YOUR_API_KEY with your actual API key)
    std::string api_key = _API_KEY;

    // File containing audio data to be transcribed
    std::string audio_file_path = file;

    // Recognition Metadata
    std::string PostParams = createRecognitionMetadata("testchat").toJSON().c_str();

	Base::Bob params;
	//params["config"] = createRecogConfig("myts", 16000);
	//params["audio"] = createRecognitionAudio("", dataStr.c_str());

	params = createRequest("testi", 16000, "", dataStr.c_str());


	std::cout << params["config"].toJSON() << std::endl;
	//std::cout << params.toJSON() << std::endl;
	PostParams = params.toJSON();

    // Build the cURL command
    CURL* curl = curl_easy_init();
    if (curl) {
        // Set the URL
        std::string url_with_key = api_url + "?key=" + api_key;
        curl_easy_setopt(curl, CURLOPT_URL, url_with_key.c_str());

        // Set the audio file
        
        // Set the Recognition Metadata
        curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, PostParams.c_str());

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
/* coole art we man nen json string erzeugt
	recognition_metadata = R"(
		{
		"config":{
		"languageCode":"LANGUAGE_CODE",
		"encoding":ENCODING",
		"sampleRateHertz":SAMPLE_RATE_HERTZ",
		"enableTimeWordOffsets":ENABLE_TIME_WORD_OFFSETS",
		},
		"audio":{"uri":"gs://STORAGE_BUCKET"},
		)";
*/
