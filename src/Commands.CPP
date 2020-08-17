#include "Commands.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


///understands input.
void Commands::identifier(char *order, char *path, char **drive){

     char first_part[100] = "\0";
     char second_part[100] = "\0";
     char third_part[100] = "\0";
     char forth_part[100] = "\0";

    sscanf(order,"%s%s%s%s", first_part, second_part, third_part, forth_part);

    if(!strcmp(first_part, "cls"))
            system("CLS");

    if(!strcmp(first_part, "date")){
        if(!strcmp(second_part, ""))
            info.date();
        else
             printf("'%s' is not recognized as an internal or external command,\n"
            "operable program or batch file.\n", order);
    }

    if(!strcmp(first_part, "help")){
        if(!strcmp(second_part, ""))
            info.help();
        else
            printf("This command is not supported by the help utility.\n");
    }

    if(!strcmp(first_part, "copy"))
        file.copyRec(second_part, third_part, forth_part, path);

    if(!strcmp(first_part, "del")){
        file.delRec(second_part, third_part, path);
    }

    if(!strcmp(first_part, "rename"))
        file.reName(second_part, third_part, path);

    if(!strcmp(first_part, "cd"))
        directory.cdRec(second_part, third_part, path,drive);

    if(!strcmp(first_part, "dir")){
        char *path2 = new char[100];
        strcpy(path2, path);   ///yek copy az currentPath sakhte va be dirRec pas midahim ta currentPathe asli ra taghir nadahad va az path2 estefade konad.
        directory.dirRec(path2, second_part, third_part, forth_part);
        delete path2;
    }

    if(!strcmp(first_part, "chdir")){
        char *path2 = new char[100];
        strcpy(path2, path);   ///yek copy az currentPath sakhte va be chdirRec pas midahim ta currentPathe asli ra taghir nadahad va az path2 estefade konad.
        directory.chdirRec(path2, second_part, drive);
        delete path2;
    }

    if(!strcmp(first_part, "exit"))
        exit(EXIT_FAILURE);

    if(!strcmp(first_part,"find"))
        file.findRec(second_part, third_part, path);

    if(!strcmp(first_part,"tree"))
        directory.treeRec(second_part, third_part, path);
}
