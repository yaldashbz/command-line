#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Commands.h"

void lowercase(char *);
void slash(char *);

int main(){

    char currentPath[100] = "C:";  ///current address.
    lowercase(currentPath);

    char *order = new char[100];
    char **drive = new char *[100];

    for(int i=0; i<100; i++)
        drive[i] = new char[100];


    Commands cmd;

    while (1){

        printf("%s>", currentPath);
        scanf(" %[^\n]", order);
        lowercase(order);
        slash(order);
        cmd.identifier(order, currentPath, drive);
        printf("\n");
    }

    delete order;
    for (int i=0; i<100; i++)
        delete drive[i];
    delete drive;


    return 0;
}

/// in tabe tamamie charachter haye dakhele char* vorudi ra lowercase mikonad.
void lowercase(char *str){
    int i;
    int size = strlen(str);
    for(i = 0; i < size; i++){
        if(str[i] >= 65 && str[i] <= 90)
            str[i] += 32;
    }
}

/// in tabe tamamie \ haye dakhele char* vorudi ra be \ tabdil mikonad.
void slash(char *order){
    int i = 0;
    while(order[i]){
        if(order[i] == '/'){
            order[i] = '\\';
        }
        i++;
    }
}
