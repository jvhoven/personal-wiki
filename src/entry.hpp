#ifndef PERSONALWIKI_ENTRY_H
#define PERSONALWIKI_ENTRY_H

struct Tag {
    int id;
    std::shared_ptr<int> entry_id;
    std::string title;
};

struct Entry {
    int id;
    std::string title;
    std::string content;
};

enum EntryType {
    Web,
    Text
};

#endif
