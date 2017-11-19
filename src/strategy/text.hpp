#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "strategy.hpp"

#ifndef PERSONALWIKI_STRATEGY_TEXT_H
#define PERSONALWIKI_STRATEGY_TEXT_H

class TextStrategy: public Strategy {
private:
    std::string retrieveContent(std::string source) {
        FILE *file = fopen("/tmp/wiki-entry.md", "w+");
        const std::string FILE_NAME = "/tmp/wiki-entry.md";
        std::string program = "open -a typora";
        std::string buffer;

        if (file) {
            std::cout << "Opened file for appending, press a key if you're done!";
            std::system((program + " " + FILE_NAME).c_str());

            std::cin.get();
            std::ifstream ifs(FILE_NAME, std::ifstream::binary);

            while(!ifs.eof()) {
                getline(ifs, buffer);
            }

            std::cout << buffer;
            ifs.close();
            fclose(file);
        }

        return buffer;
    }
 };

#endif