#ifndef PERSONALWIKI_WIKI_H
#define PERSONALWIKI_WIKI_H

#include <memory>
#include <fstream>

#include "strategy/strategy.hpp"
#include "strategy/web.hpp"
#include "tty/termcolor.hpp"

class Wiki {
public:
    Wiki() = default;

    enum EntryType {
        Web, Text
    };

    void recordEntry(const std::string &title, const std::string &fromSource, std::vector<std::string> tags) {
        const auto entry = _strategy->createEntry(fromSource, title, tags);

        std::cout
                << termcolor::blink << "Test"
                << "Entry tags: \n"
                << entry->getTags()
                << "Content size in bytes: \n"
                << entry->getContentInBytes()
                << std::endl;
    }

    void readEntry() {

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

Wiki::Wiki() : _strategy(nullptr) {}

#endif
