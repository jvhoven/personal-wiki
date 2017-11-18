#ifndef PERSONALWIKI_WIKI_H
#define PERSONALWIKI_WIKI_H

#include <memory>

#include "strategy/strategy.hpp"
#include "strategy/web.hpp"

class Wiki {
public:
    Wiki(): _strategy(nullptr) {}

    enum EntryType {
        Web, Text
    };

    void recordEntry(std::string fromSource) {
        std::vector<std::string> tags = { "Test", "Nog een test" };
        auto entry = _strategy->createEntry(fromSource, "Title", tags);

        std::cout
                << "Entry tags: \n"
                << entry->getTags()
                << "Content size in bytes: \n"
                << entry->getContentInBytes()
                << std::endl;
    }

    void setStrategy(int type) {
        Strategy* strategy;

        switch (type) {
            case Web:
                strategy = new WebStrategy();
                break;
            case Text:
                strategy = new WebStrategy();
                break;
            default:
                std::cout << "Not sure what to do with that source" << std::endl;
                break;
        }

        _strategy.reset(strategy);
    }
private:
    std::unique_ptr<Strategy> _strategy;
};

#endif
