//
// Created by Jeffrey on 02/12/2017.
//

#ifndef PERSONALWIKI_STORAGE_H
#define PERSONALWIKI_STORAGE_H

#include "../libs/sqlite_orm/include/sqlite_orm/sqlite_orm.h"
#include <stdio.h>
#include <stdlib.h>

using namespace sqlite_orm;

class Storage {
public:
    Storage() {
        auto storage = make_storage(DATABASE,
            make_table("entry",
                 make_column("id", &Entry::id, autoincrement(), primary_key()),
                 make_column("title", &Entry::title),
                 make_column("content", &Entry::content)
            )
        );
        storage.sync_schema();

        Entry entry { -1, "A title", "something" };

        auto id = storage.insert(entry);
        auto test = storage.get<Entry>(id);
        std::cout << "insertedId = " << id << std::endl;
        std::cout << test.title << test.content << std::endl;
    }
private:
    const std::string DATABASE = "/Users/jeffrey/.wiki";
};


#endif //PERSONALWIKI_STORAGE_H
