/*
*   Loading the menu for the client
*/

#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

/* In order to list the files send by the server */
#include "Client.h"

/* Formula to calculate the size of the array. This calculation divides the total amount of bytes by the amount of bytes of an individual element. */
#define SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))

/* Array of string holding the different menu options */
char* choices[] = {
    "Download",
    "Upload",
    "Help",
    "Exit"
};

/* Gets called from the main client program */
int load_menu (char* name)
{
    /* Create new window variable */
    //WINDOW* main_window;
    /* Menu contains the amount of rows and columns */
    MENU* main_menu;
    int user_input, menu_options, selected_option = 0;
     /* Amount of elements in menu */
    menu_options = SIZE_OF_ARRAY(choices);
    /* Item is a struct about a menu item, such as name, position and index */
    ITEM** menu_items;
    
    /* Load and initialise ncurses screen */
    initscr();

    /* Disable line buffering */
    cbreak();

    /* Do not echo key input directly onto the screen */   
    noecho(); 

    /* Enable special keys (arrow, space, F keys) */
    keypad(stdscr, TRUE);

    /* Reserve memory for menu_items */
    menu_items = (ITEM**) calloc(menu_options + 1, sizeof(ITEM*));

    /* For all elements, configurate their names */
    for (size_t i = 0; i < menu_options; i++)
    {
        menu_items[i] = new_item (" ", choices[i]);
    } 
    /* Initialise menu screen */
    main_menu = new_menu (menu_items);
    
    /*  */
    post_menu (main_menu);
    refresh();
    
    /* Check user input and when enter was pressed, return corresponding integer. */
    while((user_input = getch()) != KEY_F(1))
	{   
        switch(user_input)
	    {	
            case KEY_DOWN:
		        menu_driver(main_menu, REQ_DOWN_ITEM);
                if (selected_option < menu_options - 1) selected_option++;
				break;
			case KEY_UP:
				menu_driver(main_menu, REQ_UP_ITEM);
                if (selected_option > 0) selected_option--;
				break;
                /* Equivalent of pressing enter key */
            case 10:
                /* End ncurses mode */
                endwin();
                unpost_menu (main_menu);
                return selected_option;
		}
	}
    return 1;
}

int load_list_of_files ()
{
    
    return 0;
}

// WINDOW* contruct_window (int h, int w, int starty, int startx)
// {	
//     WINDOW* local_win;

//     int terminalWidth, terminalHeight;
//     /* With the size of the current terminal */
//     getmaxyx(stdscr, terminalHeight, terminalWidth);
// 	w = newwin(terminalHeight, terminalWidth, 0, 0);
//     /* Border decoration for new window */
// 	box(w, '*', '=');				
// 	wrefresh(w);	

// 	local_win = newwin(h, w, starty, startx);
// 	box(local_win, 0 , 0);
					
// 	wrefresh(local_win);	

// 	return local_win;
// }
