#ifndef PERSONALWIKI_ENTRY_H
#define PERSONALWIKI_ENTRY_H

#include <vector>
#include <string>
#include <ctime>

class Entry {
public:
    Entry(const std::string &title, const std::vector<std::string> &tags, const std::string &content):
        m_title("A title"), m_tags(std::vector<std::string>(1, "test")), m_content(content) {
        setTimestamp();
    }

    time_t getTimestamp() {
        return m_date;
    }

    const std::string getTags() {
        std::string tags;
        for (const auto& tag: m_tags) {
            tags.append("\t" + tag + "\n");
        }

        return tags;
    }

    size_t getContentInBytes() {
        return m_content.size();
    }
private:
    void setTimestamp() {
        time_t seconds_from_epoch = std::time(nullptr);
        m_date = seconds_from_epoch;
    }

    std::vector<std::string> m_tags;
    std::string m_title;
    time_t m_date;
    std::string m_content;
};

#endif
