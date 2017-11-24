#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "strategy.hpp"

#ifndef PERSONALWIKI_STRATEGY_TEXT_H
#define PERSONALWIKI_STRATEGY_TEXT_H

enum PID_STATUS {
    ERROR = -1,
    CHILD = 0,
};

class TextStrategy: public Strategy {
private:
    std::string retrieveContent(const std::string &source) {
        const std::string FILE_NAME = "/tmp/wiki-entry.md";
        std::string buffer;

        auto file = fopen(FILE_NAME.c_str(), "w+");
        pid_t pid = fork();

        switch (pid) {
            case PID_STATUS::ERROR: {
                perror("fork");
                break;
            }

            case PID_STATUS::CHILD: {
                char *viArgs[] = {
                        const_cast<char *>("-E"),
                        const_cast<char *>("/tmp/wiki-entry.md"),
                        nullptr
                };

                if (execvp("/usr/bin/vim", viArgs) == -1) {
                    std::cout << ("failure to execute vim %s\n", strerror(errno));
                }
                break;
            }

            default: {
                waitpid(pid, nullptr, 0);
                std::ifstream ifs(FILE_NAME);
                buffer.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

                ifs.close();
                fclose(file);
                break;
            }
        }

        return buffer;
    }
 };

#endif