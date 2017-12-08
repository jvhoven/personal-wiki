#ifndef PERSONALWIKI_ENTRY_H
#define PERSONALWIKI_ENTRY_H

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
