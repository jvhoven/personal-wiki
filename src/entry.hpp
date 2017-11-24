#ifndef PERSONALWIKI_ENTRY_H
#define PERSONALWIKI_ENTRY_H

#include <vector>
#include <string>
#include <ctime>
#include <iostream>

#include "tty/termcolor.hpp"

class Entry {
public:
    Entry(const std::string &title, const std::vector<std::string> &tags, const std::string &content):
        m_title(title), m_tags(tags), m_content(content) {
        setTimestamp();
    }

    time_t getTimestamp() {
        return m_date;
    }

    const std::string getTitle() {
        return m_title;
    }

    const std::string getTags() {
        std::string tags;
        for (const auto& tag: m_tags) {
            tags.append("  ➜ " + tag + "\n");
        }

        return tags;
    }

    void print() {
        // TODO: implement ostream on Entry for this
        std::cout
                << termcolor::bold << termcolor::green << "Succesfully created entry "
                << termcolor::red << "`" << getTitle() << "`" << termcolor::green << ".\n"
                << termcolor::green << "You can find it in the following categories:\n"
                << termcolor::reset << getTags()
                << std::endl;
    }

private:
    void setTimestamp() {
        time_t seconds_from_epoch = std::time(nullptr);
        m_date = seconds_from_epoch;
    }

    std::vector<std::string> m_tags;
    std::string m_title;
    time_t m_date{};
    std::string m_content;
};

#endif
