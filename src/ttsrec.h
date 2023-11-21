#pragma once

//!< class to capture and play audio for tts

namespace audio
{
    class ttsrec
    {
        public:
            
            ttsrec(){;}
            //int test(int argc, char** argv);
            int testrec(char* file);

			int playFromFile(const char* file); //!< play sound from file
    };
}