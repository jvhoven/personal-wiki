#include <regex>
#include <iostream>
#include "wiki.hpp"
#include "util.hpp"
#include "CLI11.hpp"

auto main(int argc, char *argv[]) -> int {
    int id;
    std::string tag;
    std::string title;
    std::string source;
    std::vector<std::string> tags;
    Wiki wiki;

    CLI::App app("Personal wiki application");
    CLI::App *find = app.add_subcommand("find", "Finds an entry by a given id.");
    CLI::App *search = app.add_subcommand("search", "Finds an entry by a given tag.");
    CLI::App *text = app.add_subcommand("text", "Creates a new entry from text.");
    CLI::App *web = app.add_subcommand("web", "Creates a new entry from web.");

    find->add_option("id", id, "The id of the entry.")->required();
    search->add_option("tag", tag, "The tag you would like to search for.")->required();

    text->add_option("title", title, "Title of the entry")->required();
    text->add_option("tags", tags, "tags")->required();

    web->add_option("title", title, "Title of the entry")->required();
    web->add_option("url", source, "Url of the webpage")->required();
    web->add_option("tags", tags, "tags")->required();

    find->set_callback([&]() {
        auto entry = wiki.findEntry(id);
        std::cout << entry->content << std::endl;
    });

    search->set_callback([&]() {
        auto entries = wiki.findEntryByTag(tag);
        std::cout << "Found " << entries.size() << " entries with tag `" << tag << "`:\n";
        std::cout << "id\ttitle\n";

        for (auto &entry : entries) {
            std::cout << entry.id << "\t" << entry.title << std::endl;
        }
    });

    web->set_callback([&]() {
        // TODO: check if source is URL
        wiki.setType(EntryType::Web);
        auto entry = wiki.recordEntry(title, source, tags);

        std::cout << "Created new entry from web with id " << entry << std::endl;
    });

    text->set_callback([&]() {
        wiki.setType(EntryType::Text);
        auto entry = wiki.writeEntry(title, tags);

        std::cout << "Created new entry from text with id " << entry << std::endl;
    });

    app.require_subcommand(1);

    CLI11_PARSE(app, argc, argv);
}