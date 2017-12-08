#ifndef PERSONALWIKI_STORAGE_H
#define PERSONALWIKI_STORAGE_H

#include "sqlite_orm/sqlite_orm.h"
#include "../entry.hpp"

using namespace sqlite_orm;

const std::string DATABASE = "/Users/jeffrey/Documents/test.db";

auto initStorage(const std::string &path) {
    return make_storage(path,
        make_table("entry",
            make_column("id", &Entry::id, autoincrement(), primary_key()),
            make_column("title", &Entry::title),
            make_column("content", &Entry::content)
        )
    );
}

typedef decltype(initStorage("")) Storage;

static std::shared_ptr<Storage> storage;

class StorageService {
public:
    static std::shared_ptr<Storage> getStorage() {
        return std::make_shared<Storage>(initStorage(DATABASE));
    }
};


#endif //PERSONALWIKI_STORAGE_H