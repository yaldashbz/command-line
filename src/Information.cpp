#include "Information.h"
#include <stdio.h>
#include <time.h>


void Information::date(){
    int day, mon, year;
    time_t now;
    time(&now);

    struct tm *local = localtime(&now);

    day = local->tm_mday;
    mon = local->tm_mon + 1;
    year = local->tm_year + 1900;

    printf("The current date is : %02d/%02d/%d\n", day, mon, year);
}

void Information::help(){
    printf("CD             Displays the name of or changes the current directory.\n"
           "    [.]        Displays the current directory in the specified drive.\n"
           "    [..]       Specifies that you want to change to the parent directory.\n"
           "    [/D]       Changes current drive in addition to changing current\n"
           "               directory for a drive.\n"
           "    [/?]       Provides Help information for CD commands.\n"
           "CHDIR          Displays the name of or changes the current directory.\n"
           "CLS            Clears the screen.\n"
           "COPY           Copies one or more files to another location.\n"
           "    [/X]       Moves one or more files from one directory to another\n"
           "               directory.\n"
           "DATE           Displays the date.\n"
           "DEL            Deletes one or more files.\n"
           "    [/P]       Gets permission from user.\n"
           "    [/F]       Deletes a folder.\n"
           "    [/?]       Provides Help information for DEL commands.\n"
           "DIR            Displays a list of files in a directory.\n"
           "    [/O]       Lists by files in alphabetical order.(By name)\n"
           "    [/E]       List by files in alphabetical order.(By extension)\n"
           "    [/S]       Displays files in specified directory and all subdirectories.\n"
           "    [>]        Prints the list of files and subdirectories in a specified file.\n"

           "EXIT           Quits the program.\n"
           "FIND           Searches for a text string in a file or files.\n"
           "HELP           Provides Help information for commands.\n"
           "TREE           Graphically displays the directory structure of a drive or path.\n"
           "    [>]        Prints the graphical directory structure in a specified file.\n");
}
