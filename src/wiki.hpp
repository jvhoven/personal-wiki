#ifndef PERSONALWIKI_WIKI_H
#define PERSONALWIKI_WIKI_H

#include <memory>
#include <fstream>

#include "strategy/strategy.hpp"
#include "strategy/web.hpp"
#include "strategy/text.hpp"
#include "tty/termcolor.hpp"

class Wiki {
public:
    Wiki() : _strategy(nullptr) {}

    enum EntryType {
        Web, Text
    };

    void writeEntry(const std::string &title, std::vector<std::string> tags) {
        const auto entry = _strategy->createEntry("", title, tags);
    }

    void recordEntry(const std::string &title, const std::string &fromSource, std::vector<std::string> tags) {
        const auto entry = _strategy->createEntry(fromSource, title, tags);

        // TODO: implement ostream on Entry for this
        std::cout
                << termcolor::blink << "Test"
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
                strategy = new TextStrategy();
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
