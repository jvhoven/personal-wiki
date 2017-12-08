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

    int writeEntry(const std::string &title) {
        auto entry = _type->createEntry("", title);
        return  _storage->insert(entry);
    }

    int recordEntry(const std::string &title, const std::string &fromSource) {
        auto entry = _type->createEntry(fromSource, title);
        return _storage->insert(entry);
    }

    std::shared_ptr<Entry> findEntry(const int id) {
        if(auto entry = _storage->get_no_throw<Entry>(id)){
            return entry;
        } else {
            std::cout << "no user with id " << id << std::endl;
        }

        return std::make_shared<Entry>(Entry{});
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
    std::shared_ptr<Storage> _storage;
    std::unique_ptr<Type> _type{};
};

#endif
