#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "type.hpp"

#ifndef PERSONALWIKI_STRATEGY_TEXT_H
#define PERSONALWIKI_STRATEGY_TEXT_H

enum PID_STATUS {
    ERROR = -1,
    CHILD = 0,
};

class Text: public Type {
private:
    std::shared_ptr<std::string> retrieveContent(const std::string &source) {
        const std::string FILE_NAME = "/tmp/wiki-entry.md";

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
                _buffer->assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

                ifs.close();
                fclose(file);
                break;
            }
        }

        std::cout << *_buffer.get() << std::endl;
        return _buffer;
    }

    std::shared_ptr<std::string> _buffer = std::make_shared<std::string>("");
 };

#endif