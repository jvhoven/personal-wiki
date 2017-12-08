#include <regex>
#include <iostream>
#include "wiki.hpp"
#include "util.hpp"

auto main(int argc, char *argv[]) -> int {
    if (argc < 3) {
        std::cout << "should be run with arguments: <title> <type|source> <tags...>";
        return -1;
    }

    Wiki wiki;
    std::string title = argv[1];
    std::string source = argv[2];
    std::regex url_regex = std::regex(".*\\..*", std::regex::extended);

    if (std::regex_match(argv[2], url_regex)) {
        //std::vector<std::string> tags(&argv[3], argc + argv);

        wiki.setType(EntryType::Web);
        auto entry = wiki.recordEntry(title, source);
    } else {
        //std::vector<std::string> tags(&argv[2], argc + argv);

        wiki.setType(EntryType::Text);
        auto entryId = wiki.writeEntry(title);
        auto entry = wiki.findEntry(entryId);
        std::string test = Util::decompress_string(entry->content);

        std::cout << entry->title << "\n" << test << std::endl;
    }
}