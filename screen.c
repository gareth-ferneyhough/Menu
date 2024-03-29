/*

  CURHELL2.C
  ==========
  (c) Copyright Paul Griffiths 1999
  Email: mail@paulgriffiths.net

  "Hello, world!", ncurses style (now in colour!)

*/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <curses.h>
#include <string.h>

#include "screen.h"

WINDOW * mainwin;

int cursor_line = 1;
int cursor_col = 1;

void set_cursor_position(int line_number, int column)
{
	cursor_line = line_number;
	cursor_col = column;
}

void write_line(int line_number, const char* text)
{
	int row = 6 + line_number;
	int col = 32;

	int cursor_start = cursor_col -1;
	int cursor_end = cursor_start;

	// clear line
	wmove(mainwin, row, 0);
	clrtoeol();

	for(unsigned int i = 0; i < strlen(text); ++i)
	{
		if(i >= cursor_start && i <= cursor_end && line_number == cursor_line)
		{
			color_set(2, NULL);
		}
		else
		{
			color_set(1, NULL);
		}
		mvaddch(row, col + i, text[i]);		
	}
	refresh();
}

int init_screen() 
{
    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) {
	fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
    }

    curs_set(0);
	noecho();
	cbreak();

    start_color();                    /*  Initialize colours  */

    /*  Make sure we are able to do what we want. If
	has_colors() returns FALSE, we cannot use colours.
	COLOR_PAIRS is the maximum number of colour pairs
	we can use. We use 13 in this program, so we check
	to make sure we have enough available.               */

    if ( has_colors() && COLOR_PAIRS >= 13 ) 
    {

	int n = 1;


	/*  Initialize a bunch of colour pairs, where:

	        init_pair(pair number, foreground, background);

	    specifies the pair.                                  */

	init_pair(1,  COLOR_WHITE,   COLOR_BLACK);
	init_pair(2,  COLOR_BLACK,   COLOR_WHITE);
	init_pair(3,  COLOR_YELLOW,  COLOR_BLACK);
	init_pair(4,  COLOR_BLUE,    COLOR_BLACK);
	init_pair(5,  COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6,  COLOR_CYAN,    COLOR_BLACK);
	init_pair(7,  COLOR_BLUE,    COLOR_WHITE);
	init_pair(8,  COLOR_WHITE,   COLOR_RED);
	init_pair(9,  COLOR_BLACK,   COLOR_GREEN);
	init_pair(10, COLOR_BLUE,    COLOR_YELLOW);
	init_pair(11, COLOR_WHITE,   COLOR_BLUE);
	init_pair(12, COLOR_WHITE,   COLOR_MAGENTA);
	init_pair(13, COLOR_BLACK,   COLOR_CYAN);
	}

    return EXIT_SUCCESS;
}

int get_char()
{
	int c = wgetch(mainwin);
	switch(c)
	{	
		case 'w': //27
			return 1;
		case 's':
			return 2;
		case 'a':
			return 3;
		case 'd':
			return 4;
		default:
			return -1;
	}
}

int destroy_screen()
{
    /*  Clean up after ourselves  */

    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}