#include <regex>
#include "src/wiki.hpp"

auto main(int argc, char *argv[]) -> int {
    if (argc < 3) {
        std::cout << "should be run with arguments: <title> <type|source> <tags...>";
        return -1;
    }

    Wiki wiki;
    std::string title = argv[1];
    std::string source = argv[2];

    std::regex url_regex = std::regex(".*\\..*", std::regex::extended);
    std::cout << std::regex_match(argv[2], url_regex);

    if (std::regex_match(argv[2], url_regex)) {
        std::vector<std::string> tags(&argv[3], argc + argv);

        wiki.setStrategy(0);
        wiki.recordEntry(title, source, tags);
    } else {
        std::vector<std::string> tags(&argv[2], argc + argv);

        wiki.setStrategy(1);
        wiki.writeEntry(title, tags);
    }

//    Wiki wiki;
//    wiki.setStrategy(0);
//    wiki.recordEntry("https://www.engadget.com/2011/02/08/dear-apple-thank-you-for-pulling-out/");
}