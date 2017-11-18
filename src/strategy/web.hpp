#include "strategy.hpp"
#include <curl/curl.h>
#include <iostream>

#ifndef PERSONALWIKI_STRATEGY_WEB_H
#define PERSONALWIKI_STRATEGY_WEB_H

std::string buffer;

class WebStrategy: public Strategy {
private:
    static size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata) {
        size_t realsize = size * nmemb;
        buffer.append(ptr, realsize);

        return realsize;
    }

    std::string retrieveContent(std::string fromSource) {
        std::string BASE_URL = "http://fuckyeahmarkdown.com/go/?u=";
        std::string URL = BASE_URL + fromSource;
        CURL *curl = curl_easy_init();
        CURLcode res;

        if (curl) {
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        return buffer;
    }
};

#endif