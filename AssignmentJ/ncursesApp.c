#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

static void initialiseCurses();
static void loadStartScreen();
static void loadMenu();
static void generateMenuOptions(WINDOW*);
static void runCredits(WINDOW*);
static void runHack(WINDOW*);
static void printOnScreenCenter (WINDOW*, char*, int);

int main (int argc, char* argv[])
{	
    /* Load necessary ncurses options */
    initialiseCurses();
    /* Initialise first screen onto terminal */
    loadStartScreen(); 
    /* wait for user input */      
    getch();
    /* Load option menu */
    loadMenu();
    /* wait for user input */
    /* End ncurses session */
	endwin();
	return 0;
}

static void initialiseCurses()
{
    /* Initialize curses */
	initscr();
    /* Do not buffer, but display directly onto screen */
	cbreak();
    /* Do not display raw key inputs on terminal */
	noecho();
    /* enable arrow keys */
	keypad(stdscr, TRUE);
    /* Enable colors */
    start_color();  
    /* Hide cursor by default */
    curs_set(0);
    /* Define red color */
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);     
    return;
}

static void loadStartScreen()
{
    /* Print welcome text with blining attrbiute with red color in the middle of the screen */
    attron(COLOR_PAIR(2));
    printOnScreenCenter(stdscr, "Welcome to this hack client\n", 0);
    attroff(COLOR_PAIR(2));
    attron(A_BLINK);
    printOnScreenCenter(stdscr, "Enter a key to continue...\n", 2);    
    return;
}

static void loadMenu()
{
    /* Create new window */
    WINDOW *w;
    int terminalWidth, terminalHeight;
    /* With the size of the current terminal */
    getmaxyx(stdscr, terminalHeight, terminalWidth);
	w = newwin(terminalHeight, terminalWidth, 0, 0);
    /* Border decoration for new window */
	box(w, '|' , '=');				
	wrefresh(w);	
    /* generate options */
    generateMenuOptions(w);
    return;
}

static void generateMenuOptions(WINDOW *mainWindow)
{
    WINDOW* w;
    char* list[3] = { "Credits", "Hack the system", "Quit"};
    char item[20];
    int ch, i = 0, width = 7;

    int terminalWidth, terminalHeight;
    /* With the size of the current terminal */
    getmaxyx(stdscr, terminalHeight, terminalWidth);
 
    w = newwin(terminalHeight / 2, terminalWidth / 2, terminalHeight - terminalHeight / 1.3, terminalWidth - terminalWidth / 1.3);
    box( w, 0, 0 );

    /* enable arrow keys */
	keypad(w, TRUE);
     
    /* Highlight the first item in list */
    for(i = 0; i < 3; i++) 
    {
        if(i == 0) wattron( w, A_STANDOUT );
        else wattroff( w, A_STANDOUT );
        /* Store item temporarily and print in line with offset */
        sprintf(item, "%-7s",  list[i]);
        mvwprintw(w, i+1, 2, "%s", item);
    }    
    /* Update information */
    wrefresh(w); 
    /* Reset counter */
    i = 0;     
    /* Keep evaluating items */
    while(( ch = wgetch(w)) != 'q')
    {         
    sprintf(item, "%-7s",  list[i]); 
    mvwprintw( w, i+1, 2, "%s", item ); 
    switch( ch ) {
        /* Evalute key press and highlight appropiate option */
        case KEY_UP:
            i--;
            i = (i < 0) ? 2: i;
            break;
        case KEY_DOWN:
            i++;
            i = (i > 2) ? 0 : i;
            break;
        case 10:
            /* When pressing enter, check which option is selected and take the proper action */
            switch (i)
            {
            case 0:  
                werase(w);      
                runCredits(w);
                return;
            case 1:
                werase(w);      
                runHack(w);
                return;                            
            case 2:
                endwin();
                exit(0);
                break;                            
            default:
                break;
            }
        }
        // now highlight the next item in the list.
        wattron( w, A_STANDOUT );
            
        sprintf(item, "%-7s",  list[i]);
        mvwprintw( w, i+1, 2, "%s", item);
        wattroff( w, A_STANDOUT );
    }
    return;
}

static void runCredits(WINDOW* w)
{    
    int sleepTime = 0;
    scrollok(w, TRUE);
    printOnScreenCenter(w, "Producer 1 Valerian", 0);
    printOnScreenCenter(w, "Producer 2 Berend", 2);

    /* Per second, move credit text one up */
    while (1)
    {
        wrefresh(w);
        scroll(w);
        delay_output(2);
        sleep(1);
        if (sleepTime++ >= 7) 
        {
            endwin();
            exit(0);
        }
    }    
}

static void runHack(WINDOW* w)
{
    /* Execute text sequence */
    printOnScreenCenter(w, "Hacking...", 0);
    wrefresh(w);
    sleep(2);
    printOnScreenCenter(w, "Hack completed! :D", 1);
    wrefresh(w);
    sleep(1);
    printOnScreenCenter(w, "Press a key to return to menu", 3);
    wrefresh(w);
    getch();
    endwin();
    loadMenu();

    return;
}

static void printOnScreenCenter (WINDOW* w, char* content, int offset)
{
    int row, col;
    /* Get width and height of screen */
    getmaxyx(w, row, col);
    /* print in the middle of the screen */
    mvwprintw(w, row / 2 + offset, (col - strlen(content)) / 2, content);
    return;
}