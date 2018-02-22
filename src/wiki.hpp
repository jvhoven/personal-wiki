#ifndef PERSONALWIKI_WIKI_H
#define PERSONALWIKI_WIKI_H

#include <memory>
#include <fstream>
#include <cassert>

#include "types/type.hpp"
#include "types/web.hpp"
#include "types/text.hpp"
#include "util.hpp"
#include "services/storage.h"

class Wiki {
public:
    Wiki() : _type(nullptr) {
        _storage = StorageService::getStorage();
        _storage->sync_schema();
    }

    int writeEntry(const std::string &title, const std::vector<std::string> tags) {
        auto entry = _type->createEntry("", title);
        auto id = _storage->insert(entry);

        this->saveTags(id, tags);
        return id;
    }

    int recordEntry(const std::string &title, const std::string &fromSource, const std::vector<std::string> tags) {
        auto entry = _type->createEntry(fromSource, title);
        auto id = _storage->insert(entry);

        this->saveTags(id, tags);
        return id;
    }

    std::shared_ptr<Entry> findEntry(const int id) {
        if(auto entry = _storage->get_no_throw<Entry>(id)){
            return entry;
        } else {
            std::cout << "no user with id " << id << std::endl;
        }

        return std::make_shared<Entry>(Entry{});
    }

    auto findEntryByTag(const std::string tag) {
        auto entries = _storage->get_all<Entry>(
                left_join<Tag>(on(c(&Entry::id) == &Tag::entry_id)),
                where(like(&Tag::title, "%" + tag + "%"))
        );

        return entries;
    }

    void setType(int type) {
        Type *entryType = nullptr;

        switch (type) {
            case EntryType::Web:
                entryType = new class::Web();
                break;
            case EntryType::Text:
                entryType = new class::Text();
                break;
            default:
                std::cout << "Not sure what to do with that source" << std::endl;
                break;
        }

        _type.reset(entryType);
    }
private:
    void saveTags(const int id, const std::vector<std::string> tags) {
        for (auto tag: tags) {
            auto t = Tag { -1, std::make_shared<int>(id), tag };
            _storage->insert(t);
        }
    }

    std::shared_ptr<Storage> _storage;
    std::unique_ptr<Type> _type{};
};

#endif
