#include "Directories.h"
#include <string.h>
#include <dirent.h>
#include <stdio.h>


void Directories::dirRec(char *path, char *second_part, char *third_part, char *forth_part){

    if(!strcmp(second_part, ""))
        showDir(path);

    else if(!strcmp(second_part, ">"))
        dirInFile(path, third_part);

    else if(!strcmp(second_part, "\\o") || !strcmp(second_part, "-o"))
        nameSort(path);

    else if(!strcmp(second_part, "\\e") || !strcmp(second_part, "-e"))
        suffixSort(path);

    else if(!strcmp(second_part, "\\s") || !strcmp(second_part, "-s"))
        recursiveDir(path);

    else{
        char *aux = new char [100];
        strcpy(aux, path);


        if(isAbsolute(second_part))
            strcpy(path, second_part);
        else{
            strcat(path,"\\");
            strcat(path, second_part);
        }


        if(!strcmp(third_part, ""))
            showDir(path);

        else if(!strcmp(third_part, ">"))
            dirInFile(aux, forth_part);

        else if(!strcmp(third_part, "\\o") || !strcmp(third_part, "-o"))
            nameSort(path);

        else if(!strcmp(third_part, "\\e") || !strcmp(third_part, "-e"))
            suffixSort(path);

        else if(!strcmp(third_part, "\\s") || !strcmp(third_part, "-s"))
            recursiveDir(path);

        delete aux;
    }
}


void nameSort(char *path){

    char **str = new char *[100];
    int i;
    for(i = 0; i < 100; i++)
        str [i] = new char[100];

    DIR *dirptr;
    dirptr = opendir(path);
    struct dirent *entry;
    i = 0;
    while(entry = readdir(dirptr)){
        strcpy(str[i], entry->d_name);
        i++;
    }

    int number = i,j;

    for (i = 0; i < number - 1; i++){
        for (j = i + 1; j < number; j++)
            strsort(str[i], str[j]);
    }

    for (i = 0; i < number; i++)
        puts(str[i]);

    for(i = 0; i < number; i++)
        delete str[i];
    delete str;

    closedir(dirptr);
}

void strsort(char *str1, char *str2){

    char *temp = new char[100];
    if(strcmp(str1, str2) > 0){
        strcpy(temp, str1);
        strcpy(str1, str2);
        strcpy(str2, temp);
    }
    delete temp;
}

void showDir(char *path){

    DIR *dirptr;
    dirptr = opendir(path);
    struct dirent *entry;

    while(entry = readdir(dirptr)){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){

            if(!isFolder(entry->d_name))
                printf("     \t%s\n", entry->d_name);
            else
                printf("<DIR>\t%s\n", entry->d_name);
        }
        else
            printf("<DIR>\t%s\n", entry->d_name);
    }
    closedir(dirptr);
}


void dirInFile(char *path, char *des){

    if (!isAbsolute(des)){
        char *aux = new char[100]; ///auxiliary variable.
        strcpy(aux, path);
        strcat(aux, "\\");
        strcat(aux, des);
        strcpy(des, aux);
    }
    FILE *fptr;
    fptr = fopen(des, "a");
    if(fptr == NULL){
        printf("Could Not Open The File.\n");
    }
    else{
        DIR *dirptr;
        dirptr = opendir(path);
        struct dirent *entry;
        while(entry = readdir(dirptr)){
            fprintf(fptr,"%s\n", entry->d_name);
        }
        closedir(dirptr);
        fclose(fptr);
    }
}
/// sort by extension
void suffixSort(char *path){

    char **str = new char *[100];
    int i;
    for(i = 0; i<100; i++)
        str[i] = new char[100];

    char **suffix = new char *[100];
    for(i = 0; i<100; i++)
        suffix[i] = new char [100];

    DIR *dirptr;
    dirptr = opendir(path);
    struct dirent *entry;
    int countsuff = 0;

    while(entry = readdir(dirptr)){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            int j = strlen(entry->d_name);
            int n = j;

            while(entry->d_name[j] != '.' && j >= 0)
                j--;

            j++;

            if(j != 0){
                int o , m = 0;
                for (o = j; o < n; o++){
                    suffix[countsuff][m] = entry->d_name[o];
                    m++;
                }
                suffix[countsuff][m] = '\0';
                strcpy(str[countsuff],entry->d_name);
                countsuff++;
            }

            else
                printf("%s\n", entry->d_name);
        }
    }
    int number = countsuff, j;
    for (i = 0; i < number - 1 ; i++){
        for (j = i + 1; j < number; j++)
            strsort2(suffix[i],suffix[j],str[i],str[j]);
    }

    for (i =0;i < number; i++)
        puts(str[i]);

    for(i = 0;i < number; i++)
        delete str[i];

    for(i = 0;i < number;i++)
        delete suffix[i];

    delete str;
    delete suffix;
    closedir(dirptr);
}


void strsort2(char *suff1, char *suff2, char *str1, char *str2){

    char *temp = new char [100];
    char *temp1 = new char [100];

    if(strcmp(suff1,suff2) > 0){
        strcpy(temp, str1);
        strcpy(str1, str2);
        strcpy(str2, temp);
        strcpy(temp1, suff1);
        strcpy(suff1, suff2);
        strcpy(suff2, temp1);
    }
    if(strcmp(suff1,suff2) == 0)
        strsort(str1,str2);

    delete temp;
    delete temp1;
}

void recursiveDir(char *path){

    DIR *dirptr;
    char *path2 = new char[100];
    struct dirent *entry;
    dirptr= opendir(path);

    while (entry=readdir(dirptr)){
            if(strcmp(entry->d_name,".") && strcmp(entry->d_name,"..")){
                if(isFolder(entry->d_name))
                    printf("<DIR>\t%s\n", entry->d_name);
                else
                    printf("     \t%s\n",entry->d_name);
            }
            if (isFolder(entry->d_name)){
                strcpy(path2,path);
                strcat(path2,"\\");
                strcat(path2,entry->d_name);
                recursiveDir(path2);
            }
    }
    delete path2;
}

void Directories::cdRec(char *second_part, char *third_part, char *path,char **drive){

        if(!strcmp(second_part, ".."))
            cdDoubleDot(path);

        else if(!strcmp(second_part, "."))
            return;

        else if(!strcmp(second_part, ""))
            printf("%s\n", path);

        else if(!strcmp(second_part, "\\d")){
            if( isValid(third_part))
                strcpy(path,third_part);
            else
                printf("The system cannot find the path specified.\n\n");
        }

        else if(!strcmp(second_part,"\\?"))
            showCd();

        else{
            char *aux = new char [100]; ///auxiliary variable
            strcpy(aux,path);
            strcat(aux,"\\");
            strcat(aux,second_part);

            if(isValid(aux))
                strcpy(path,aux);
            else
                printf("The system cannot find the path specified.\n\n");

            delete aux;
        }
        chdirMake(path,second_part,drive);
}

void showCd(){
    printf("Displays the name of or changes the current directory.\n"
           "CD  [.] [..] [/D] [/?]\n"
           " .           Displays the current directory in the specified drive.\n"
           " ..          Specifies that you want to change to the parent directory.\n"
           " /D          Changes current drive in addition to changing current\n"
           "             directory for a drive.\n"
           " /?          Provides Help information for CD commands.\n");
}

void cdDoubleDot(char *path){

    int i = strlen(path) - 1;
    while(path[i] != '\\')
        i--;
    path[i]='\0';
}

///ba tavajoh be dastur haye vared shode badaz "chdir", tabe haye marbute ra call mikonad.
void Directories::chdirRec(char *path, char *second_part, char **drive){

    if(!strcmp(second_part,""))
        printf("%s\n",path);
    else{
        chdirPrint(chdirMake(path,second_part,drive),drive,second_part);
    }
}

int chdirMake(char *path, char *second_part, char **drive){


    static int i = 0;
    if(drive[i][0] != path[0]){
        drive[i][0] = path[0];
        drive[i][1] = ':';
    }
    i++;
    if(isAbsolute(second_part)){
        strcpy(drive[i] , second_part);
        i++;
    }

    int j;
    for(j=0; j<i; j++){
        if(drive[j][0] == path[0])
            strcpy(drive[j],path);
    }

    return i;
}
void chdirPrint(int i,char **drive,char *second_part){
    int j;
    for(j=0; j<i; j++){
        if(drive[j][0] == second_part[0]){
            printf("%s\n",drive[j]);
            break;
        }
    }
}

void Directories::treeRec(char *second_part, char *third_part, char *path){

    char *des = new char[100];
    if (!isAbsolute(third_part)){
        strcpy(des,path);
        strcat(des, "\\");
        strcat(des, third_part);
    }
    else
        strcpy(des,third_part);

    if(!strcmp(second_part,">"))
        treeInFile(path,des,0);

    if(!strcmp(second_part,""))
        tree(path,0);
}

void treeInFile(char *path, char *des, const int root){

    int i;
    FILE *fptr;
    fptr = fopen(des,"a");
    DIR *dirptr;
    char *path2 = new char[100];
    struct dirent *entry;
    dirptr = opendir(path);
    if(!dirptr)
        return;
    while(entry = readdir(dirptr)){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){

            for (i=0; i<root; i++) {
                if (i%2 == 0)
                    fprintf(fptr,"|");
                else
                    fprintf(fptr,"   ");

            }
            fprintf(fptr,"---%s\n",  entry->d_name);
            strcpy(path2, path);
            strcat(path2, "\\");
            strcat(path2, entry->d_name);
            fclose(fptr);
            treeInFile(path2,des,root + 2);
        }
    }
    closedir(dirptr);
    delete path2;
}

///show tree on console
void tree(char *path,const int root){
    int i;
    DIR *dirptr;
    char *path2 = new char[100];
    struct dirent *entry;
    dirptr = opendir(path);
    if(!dirptr)
        return;

    while(entry = readdir(dirptr)){

        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){

            for (i=0; i<root; i++) {
                if (i%2 == 0)
                    printf("%c",186);
                else
                    printf("   ");

            }
            printf("%c%c%c%c%s\n", 204,205,205,205, entry->d_name);
            strcpy(path2, path);
            strcat(path2, "\\");
            strcat(path2, entry->d_name);
            tree(path2, root + 2);

        }
    }
    delete path2;
    closedir(dirptr);
}

int isValid (char *path){
    DIR *dirptr;
    dirptr= opendir(path);
    FILE *fptr;
    fptr = fopen(path,"r");
    if (dirptr || fptr){
        fclose(fptr);
        closedir(dirptr);
        return 1;
    }
    else{
        fclose(fptr);
        closedir(dirptr);
        return 0;
    }
}

int isAbsolute(char *path){
    int i = 0;
    while(path[i]){
        if(path[i] == ':')
            return 1;
        i++;
    }
    return 0;
}

