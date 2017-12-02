//
// Created by Jeffrey on 02/12/2017.
//

#ifndef PERSONALWIKI_STORAGE_H
#define PERSONALWIKI_STORAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

class Storage {
public:
    Storage() {
        sqlite3 *db;
        int status = sqlite3_open(DATABASE.c_str(), &db);
        if (status) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            exit(1);
        } else {
            _db = db;
            setup();

            if (error) {
                fprintf(stderr, "SQL error: %s\n", error);
                exit(1);
            }
        }
    }

    ~Storage() {
        sqlite3_close(_db);
    }
private:
    void setup() {
        std::string sql =
            "CREATE TABLE IF NOT EXISTS entry(id INTEGER PRIMARY KEY, title TEXT, content TEXT, timestamp INTEGER);"
            "CREATE TABLE IF NOT EXISTS tag(id INTEGER PRIMARY KEY, name TEXT);"
            "CREATE TABLE IF NOT EXISTS entry_tag("
                    "entry_id INTEGER,"
                    "tag_id INTEGER,"
                    "FOREIGN KEY(entry_id) REFERENCES entry(id),"
                    "FOREIGN KEY(tag_id) REFERENCES tag(id)"
            ");";

        sqlite3_exec(_db, sql.c_str(), nullptr, 0, &error);
    }

    sqlite3 *_db;
    const std::string DATABASE = "/Users/jeffrey/.wiki";
    char* error = 0;
};


#endif //PERSONALWIKI_STORAGE_H
