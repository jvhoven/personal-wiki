#include "src/wiki.hpp"
#include <ncurses.h>
#include <menu.h>

//    Wiki wiki;
//
//    wiki.setStrategy(0);
//    wiki.recordEntry("https://www.engadget.com/2011/02/08/dear-apple-thank-you-for-pulling-out/");


#include <stdio.h>
#include <ncurses.h>

#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

char *choices[] = {
        "Web",
        "Choice 2",
        "Choice 3",
        "Choice 4",
        "Exit",
};
int n_choices = sizeof(choices) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight);

int main() {
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();    /* Line buffering disabled. pass on everything */

    menu_win = newwin(10, 15, 2, 2);
    keypad(menu_win, TRUE);
    mvprintw(1, 1, "Select the type of the entry:");
    refresh();
    print_menu(menu_win, highlight);

    // Wait for input
    while (1) {
        c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                refresh();
                break;
        }

        print_menu(menu_win, highlight);
        if (choice != 0)    /* User did a choice come out of the infinite loop */
            break;
    }

    mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
    clrtoeol();
    refresh();
    endwin();
    std::cout << choices[choice - 1] << std::endl;
    return 0;
}


void print_menu(WINDOW *menu_win, int highlight) {
    int x, y, i;

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for (i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) /* High light the present choice */
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}