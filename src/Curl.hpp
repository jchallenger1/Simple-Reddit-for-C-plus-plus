#ifndef CURLCLASS
#define CURLCLASS

#include <string>
#include <fstream>

#include <curl/curl.h>
#include "RedditUser.hpp"

namespace redd {

    class Curl {
    public:
        Curl();
        ~Curl();

        std::string requestToken(redd::RedditUser&);

    private:
        static size_t writeToString(void* buffer, size_t size, size_t nmemb, std::string* userp);
        static size_t writeToFile(void* buffer, size_t size, size_t nmemb, std::ofstream* userp);
        void emptyErrors();
        std::string data;
        CURL* curl;//managed curl object
        char curl_error[CURL_ERROR_SIZE];

    };

}


#endif

