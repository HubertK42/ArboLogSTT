#include "STTBobConstructor.h"

#define _ENCODING 								"encoding"					// : enum (AudioEncoding),
#define _SAMPLERATEHERTZ						"sampleRateHertz"			//: integer,
#define _AUDIOCHANNELCOUNT						"audioChannelCount"			//: integer,
#define _ENABLESEPERATERECOGNITIONPERCHANNEL	"enableSeparateRecognitionPerChannel"	//: boolean,
#define _LANGUAGECODE							"languageCode"				//: string,
#define _ALTERNATIVELANGUAGECODES				"alternativeLanguageCodes"	//: [string ],
#define _MAXALTERNATIVES						"maxAlternatives"			//: integer,
#define _PROFANITYFILTER						"profanityFilter"			//: boolean,
#define _ADAPTIONS								"adaptation"				//: {object (SpeechAdaptation) },
#define _SPEECHCONTEXTES						"speechContexts"			//: [{object (SpeechContext)}  ],
#define _ENABLEWORLDTIMEOFFSETS					"enableWordTimeOffsets"		//: boolean,
#define _ENABLEWORLDCONFIDENCE					"enableWordConfidence"		//: boolean,
#define _ENABLEAUTOMATICPUNCTATION				"enableAutomaticPunctuation" //: boolean,
#define _ENABLESPOKENPUNCTION					"enableSpokenPunctuation"	//: boolean,
#define _ENABLESPOKENEMOJIS						"enableSpokenEmojis"		//: boolean,
#define _DIAARIZATIONCONFIG						"diarizationConfig"			//: { object (SpeakerDiarizationConfig)  },
#define _METADATA								"metadata" 					// {   object (RecognitionMetadata) },
#define _MODEL 									"model"						//: string,
#define _USEENHANCED							"useEnhanced"				//: boolean

//! create the whole request to be send to googles STT 
///
/// this only for for Method: speech.longrunningrecognize
///
///	\param topic 		description/name of the text
///	\param samplerate	sample rate of audio buffer/file
/// \param uri			a google cloud storge address (pBuffer must be null)
///	\param pBuffer		binary aufio bufffer
/// \return 			bob object with request
///
Base::Bob createRequest(Base::String topic, int samplerate,Base::String uri, const char* pBuffer)

{
	Base::Bob BRequest;

	BRequest["config"]		= createRecogConfig(topic, samplerate);	// : {object (RecognitionConfig) },
	BRequest["audio"]		= createRecognitionAudio(uri, pBuffer);	// : {object (RecognitionAudio)  },
 	//BRequest["outputConfig"]										// : {object (TranscriptOutputConfig)

	return BRequest;
}
//#############################################################################
//! create the recognition config data 
///
//@@TODO add different languages
///
///	\param topic 		description/name of the text
///	\param samplerate	sample rate of audio buffer/file
/// \return 			bob object with metadata
///
Base::Bob createRecogConfig(Base::String topic, int samplerate)
{
	Base::Bob BSTT;

	BSTT[_LANGUAGECODE]							= "de-DE";			//: string,
	// BSTT[_ENCODING] =		"wav" not needed for wav
	BSTT[_SAMPLERATEHERTZ]						= samplerate;		//: integer,
	
	
/*

	//BSTT[_AUDIOCHANNELCOUNT]					= channels;			//: integer,		// only needed for multi channel recognition
	BSTT[_ENABLESEPERATERECOGNITIONPERCHANNEL]	= false;			//: boolean,		// only set to true for multi channel recognition
	
	//BSTT[_ALTERNATIVELANGUAGECODES]			= 					//: [string ],		A list of up to 3 additional languages
	BSTT[_MAXALTERNATIVES]						= 1;				//: integer,		number of max alternative transcriptions
	BSTT[_PROFANITYFILTER]						= false;			//: boolean,		replace dirty words with ****

	//@@TODO include this for speech recog improvements BSTT[_ADAPTIONS]						"adaptation"				//: {object (SpeechAdaptation) },
	//@@TODO include this for speech recog improvements BSTT[_SPEECHCONTEXTES]					"speechContexts"			//: [{object (SpeechContext)}  ],
	//BSTT[_ENABLEWORLDTIMEOFFSETS]				"enableWordTimeOffsets"		//: boolean,		// if activated single word list will be added to the result
	//BSTT[_ENABLEWORLDCONFIDENCE]				"enableWordConfidence"		//: boolean,		// if activated single word list will be added to the result + confidence

	BSTT[_ENABLEAUTOMATICPUNCTATION]			= true;	//@@TODO check if this works punctations added   //: boolean,
	BSTT[_ENABLESPOKENPUNCTION]					= true;	//@@TODO check if this works punctations added   //: boolean,

//	BSTT[_ENABLESPOKENEMOJIS]					"enableSpokenEmojis"		//: boolean,
//@@TODO include this for speech recog improvements BSTT[_DIAARIZATIONCONFIG]						"diarizationConfig"			//: { object (SpeakerDiarizationConfig)  },

	BSTT[_METADATA]								= createRecognitionMetadata(topic); 					// {   object (RecognitionMetadata) },
	BSTT[_MODEL] 								= "latest_long";	// for long speech passages					//: string,
	BSTT[_USEENHANCED]							= true;				//: boolean
*/
	return BSTT;
}

//#############################################################################
//! create the recognition meta data specifing the source
///
///	\param topic description/name of the text
/// \return bob object with metadata
///
Base::Bob createRecognitionMetadata(Base::String topic) 
{
	if (topic.empty())
		topic ="no title";

	Base::Bob BRM;
	BRM["interactionType"]			= "DICTATION";	// enum (InteractionType),
	BRM["industryNaicsCodeOfAudio"]	= 113210;		//integer,  113210 Forest Nurseries and Gathering of Forest Products, Fishing and Hunting NAICS Code
	BRM["microphoneDistance"]		= "NEARFIELD";	// enum (MicrophoneDistance),
	BRM["originalMediaType"]		= "AUDIO"; 		// enum (OriginalMediaType),
//	BRM["recordingDeviceType"]		=  "PIXEL4";	// (RecordingDeviceType),
	BRM["recordingDeviceName"]		= "SMARTPHONE";	//string,
//	BRM["originalMimeType"]			=  string,		//@@TODO what is wav???
	BRM["audioTopic"]				=  topic;		//string

	return BRM;

};

//! create the RecognitionAudio meta data specifing the source of the audio either file or cloud storage
/// if uri is emtpy pure audio data will be assumed (smallerthan 60 s)
///	else a google cloud storge address should be given
///
/// \param uri		a google cloud storge address (pBuffer must be null)
///	\param pBuffer	binary aufio bufffer
///	\return 		RecognitionAudio as a bob object
///
Base::Bob createRecognitionAudio(Base::String uri, const char* pBuffer)
{
	Base::Bob BRM;
	if (pBuffer)
		BRM["content"]	= pBuffer;	// : string,
  	else
		BRM["uri"]		= uri;			//: string

	//@@TODO add error handling

	return BRM;
} 