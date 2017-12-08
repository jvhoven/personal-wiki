#ifndef PERSONALWIKI_ABSTRACT_H
#define PERSONALWIKI_ABSTRACT_H

#include <vector>
#include "../entry.hpp"
#include "../util.hpp"

class Type {
public:
    auto createEntry(std::string fromSource, std::string title) -> Entry& {
        auto content = retrieveContent(fromSource);
        std::string compressed = Util::compress_string(*content.get());

        auto entry = Entry{ -1, title, compressed };
        return entry;
    }
private:
    virtual std::shared_ptr<std::string> retrieveContent(const std::string &source) = 0;
};

#endif
