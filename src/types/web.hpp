#include "type.hpp"
#include <curl/curl.h>
#include <iostream>

#ifndef PERSONALWIKI_STRATEGY_WEB_H
#define PERSONALWIKI_STRATEGY_WEB_H

std::shared_ptr<std::string> buffer = std::make_shared<std::string>("");

class Web: public Type {
private:
    static size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata) {
        size_t realsize = size * nmemb;
        buffer->append(ptr, realsize);

        return realsize;
    }

    std::shared_ptr<std::string> retrieveContent(const std::string &fromSource) {
        std::string BASE_URL = "http://fuckyeahmarkdown.com/go/?u=";
        std::string URL = BASE_URL + fromSource;
        auto curl = curl_easy_init();

        if (curl != nullptr) {
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        return buffer;
    }
};

#endif