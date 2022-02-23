/**
 * Very simple demo from
 * https://medium.com/programming-in-c/an-introduction-to-ncurses-in-c-d977efd706f8
 **/

#include <ncurses.h>
#include <math.h>
#include <stdlib.h>

void printing(void);
void moving_and_sleeping(void);
void coloring(void);

int main(void)
{
    initscr();

    addstr("\
+-------------------+\n\
|    @Chris_Webb    |\n\
| Mini-demo ncurses |\n\
+-------------------+\n\
");
    refresh();

    addstr("This line was printed using addstr (equivalent to puts)\n");
    refresh();

    addstr("Those characters were printed using addch (equivalent to putchar):\n");
    for (char c = 'a'; c <= 'e'; ++c) {
        addch(c);
    }
    addstr("\n");
    refresh();

    printw("These numbers where printed using printw (equivalent to printf):\n%d\n%.3f\n", 42, 116);
    refresh();

    // printing();
    
    moving_and_sleeping();

    // coloring();
    
    // Wait a key press to exit... (would terminate immediately otherwise)
    addstr("\nget any press to exit...");
    refresh();
    getch();
    endwin();

    return EXIT_SUCCESS;
}

void moving_and_sleeping(void) {
    unsigned short row = 10 + 5 + 2, col;

    curs_set(0);

    // cosine
    for (col = 0; col < 80; ++col) {
        move(row + 5*cos(2*6.28*col/80.), col);
        addch('+');
        refresh();
        napms(10);
    }

    // sine
    for (col = 0; col < 80; ++col) {
        move(row + 5*sin(2*6.28*col/80.), col);
        addch('x');
        refresh();
        napms(10);
    }

    move(22, 0);
}
