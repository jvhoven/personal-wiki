#ifndef PERSONALWIKI_ABSTRACT_H
#define PERSONALWIKI_ABSTRACT_H

#include <vector>
#include "../entry.hpp"

class Strategy {
public:
    std::shared_ptr<Entry> createEntry(std::string fromSource, std::string title, std::vector<std::string> tags) {
        std::shared_ptr<Entry> entry;
        std::string content = retrieveContent(fromSource);

        entry = std::make_shared<Entry>(title, tags, content);
        return entry;
    }
private:
    virtual std::string retrieveContent(const std::string &source) = 0;
};

#endif
