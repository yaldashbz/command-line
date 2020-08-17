#include "FileManaging.h"
#include <string.h>
#include <stdio.h>
#include <dirent.h>


void FileManaging::copyRec(char *second_part, char *third_part, char *forth_part, char *path){

    char *src = new char [100];  ///baraye pas dadan be tabe makeAddCopy
    char *des = new char [100];  ///baraye pas dadan be tabe makeAddCopy
    char *des2 = new char [100]; ///baraye check validate destination
    if(!strcmp(second_part,"\\x") || !strcmp(second_part,"-x")){

        makeAddCopy(third_part, forth_part, path, src, des, des2);
        if(isValid(src) && isValid(des2)){
            copy(src,des);
            remove(src);
        }
        else
            printf("The system cannot find the file specified.\n");
    }
    else{
        makeAddCopy(second_part,third_part,path,src,des,des2);
        if(isValid(src) && isValid(des2))
            copy(src,des);
        else
            printf("The system cannot find the file specified.\n");
    }
    delete src;
    delete des;
    delete des2;
}

void makeAddCopy(char second_part[], char third_part[],char *path,char *src, char *des, char *des2){

            char *filename = new char [100];
            int i = strlen(second_part) - 1 ;

            while(second_part[i] != '\\' && i>=0)
                i--;

            i++;
            int j = 0, m;
            for( m=i; m<strlen(second_part); m++){
                filename[j] = second_part[m];
                j++;
            }
            filename[j] = '\0';

        if(isAbsolute(second_part)) {
            strcpy(src,second_part);
            if(isAbsolute(third_part)){
                strcpy(des,third_part);
                strcpy(des2,des);
                strcat(des,"\\");
                strcat(des,filename);

            }
            else{
                strcpy(des,path);
                strcat(des,"\\");
                strcat(des,third_part);
                strcpy(des2,des);      ///check validate
                strcat(des,"\\");
                strcat(des,filename);   ///make destination
            }

        }
        else{
            if(isAbsolute(third_part)){ ///des is absolute
                strcpy(src,path);
                strcat(src,"\\");
                strcat(src,second_part);
                strcpy(des2,third_part);
                strcpy(des,third_part);
                strcat(des,"\\");
                strcat(des,filename);
            }
            else{
                strcpy(src,path);
                strcat(src,"\\");
                strcat(src,second_part);

                strcpy(des2,path);
                strcat(des2,"\\");
                strcat(des2,third_part);

                strcpy(des,path);
                strcat(des,"\\");
                strcat(des,third_part);
                strcat(des,"\\");
                strcat(des,filename);
            }
        }

        delete filename;
}

void copy(char *src, char *des){

    FILE *srcptr, *desptr;
    int i;
    srcptr = fopen(src, "rb");

    if( srcptr == NULL ){
        printf("The system cannot find the file.\n");
    }
    else{
        fseek(srcptr, 0, SEEK_END);
        int leng = ftell(srcptr);

        fseek(srcptr, 0, SEEK_SET);
        desptr = fopen(des, "wb");

        if(desptr == NULL )
            fclose(srcptr);

        for(i = 0; i < leng; i++)
            fputc(fgetc(srcptr), desptr);
    }
    fclose(srcptr);
    fclose(desptr);
}

void FileManaging::delRec(char *second_part, char *third_part, char *path){

    char *src = new char[100];

    if(!strcmp(second_part,"\\f")){
        makeAddDel(third_part,src,path);
        if (isValid(src))
            delFolder(src);
        else
            printf("could Not find %s\n", src);
    }

    else if(!strcmp(second_part,"\\?") || !strcmp(second_part,"-?"))
        showDel();

    else if(!strcmp(second_part,"\\p") || !strcmp(second_part,"-p")){
        makeAddDel(third_part,src,path);
        if (isValid(src))
            perDel(src);
        else
            printf("could Not find %s\n", src);
    }

    else{
        makeAddDel(second_part,src,path);
        if (isValid(src))
            remove(src);
        else
            printf("could Not find %s\n", src);
    }
}

void showDel(){
    printf("Deletes one or more files.\n"
           "DEL [/P] [/F] [/?]\n"
           " /P          Gets permission from user.\n"
           " /F          Deletes a folder.\n"
           " /?          Provides Help information for DEL commands.\n");
}

///gets permission from user
int perDel(char src[]){

    char per;
    printf("%s,Delete(Y/N)?",src);
    scanf(" %c",&per);
    if( per == 'y'|| per == 'Y'){
        remove(src);
    }
    else if( per == 'n'|| per=='N')
        return 0;
    else
        perDel(src);
}

void delFolder(char *path){

    char *aux = new char[100];
    DIR *dirptr;
    struct dirent *entry;
    dirptr= opendir(path);
    while (entry=readdir(dirptr)){
            strcpy(aux, path);
            strcat(aux, "\\");
            strcat(aux, entry->d_name);
            if (isFolder(entry->d_name))
                delFolder(aux);
            else
                remove(aux); ///file haye dakhele folder ra pak mikonad
    }
    rmdir(path); ///foldere khali ra pak mikonad
    delete aux;
}

void makeAddDel(char *third_part, char *src, char *path){

    if(isAbsolute(third_part))
            strcpy(src,third_part);
        else{
            strcpy(src,path);
            strcat(src,"\\");
            strcat(src,third_part);
        }
}


void FileManaging::reName(char *second_part, char *third_part, char *path){

    char *beforeName= new char[100];
    int i = strlen(second_part) - 1;
    while(second_part[i] != '\\')
        i--;
    int j;
    for(j = 0; j < i ; j++){
        beforeName[j] = second_part[j];
    }
    beforeName[j] = '\0';
    ///

    char *destination = new char [100];
    char *src = new char [100];

    if(isAbsolute(second_part)){
        strcpy(src,second_part);
        strcpy(destination,beforeName);
        strcat(destination,"\\");
        strcat(destination,third_part);

    }
    else{
        strcpy(src,path);
        strcat(src,"\\");
        strcat(src,second_part);
        strcpy(destination,path);
        strcat(destination,"\\");
        strcat(destination,third_part);
    }
    ///

    if(isValid(src))
        rename(src,destination);
    else
        printf("The system cannot find the file specified.\n");
}

void FileManaging::findRec(char *second_part, char *third_part, char *path){

    if(!starRec(second_part)){
        if(!strcmp(third_part, "")){
            char *aux = new char [100];
            strcpy(aux,path);
            find(aux,second_part);
            delete aux;
        }
        else
            find(third_part,second_part);
    }
    else{
        if(!strcmp(third_part, "")){
            char *aux = new char [100];
            strcpy(aux,path);
            starFind(aux,second_part);
            delete aux;
        }
        else
            starFind(third_part,second_part);
    }
}

int starRec(char *name){

    int i = 0;
    while(name[i]){
        if(name[i] == '*')
            return 1;
        i++;
    }
    return 0;
}


void find(char *path, char *file){
    char *aux = new char[100];
    DIR *dirptr;
    dirptr = opendir(path);
    struct dirent *entry;
    while (entry=readdir(dirptr)){
            if(!strcmp(entry->d_name,file)){
                strcpy(aux,path);
                strcat(aux,"\\");
                strcat(aux,entry->d_name);
                printf("%s\n",aux);
            }
            if (isFolder(entry->d_name)){
                strcat(path,"\\");
                strcat(path,entry->d_name);
                find(path,file);
            }
    }
    delete aux;
    closedir(dirptr);
}

void starFind(char *path,char *file){

    char *aux = new char [100];
    DIR *dirptr;
    dirptr = opendir(path);
    struct dirent *entry;
    while(entry=readdir(dirptr)){
            if(sameRec(entry->d_name,file)){

                strcpy(aux,path);
                strcat(aux,"\\");
                strcat(aux,entry->d_name);
                printf("%s\n",aux);
            }
            if (isFolder(entry->d_name)){

                strcat(path,"\\");
                strcat(path,entry->d_name);
                starFind(path,file);
            }
    }
    delete aux;
    closedir(dirptr);
}

int sameRec(char *str1, char *str2){

    int i=0,j=0,o=0;
    while(str2[j] !='\0' && str1[i] != '\0' && str2[j]!='*') {
        if(str1[i] == str2[j])
            o++;
        i++,j++;
    }
    int l2 = strlen(str2) -1 ,l1 = strlen(str1) -1,m=0,n=0;

    while(l2 >= 0 && l1>=0 && str1[l1] != '.' && str2[l2]!='.' ){
        if(str1[l1] == str2[l2])
            m++;
        l1--,l2--;
        n++;
    }
    if(o == j && m == n)
        return 1;
    else
        return 0;
}

int isFolder(char *name){

    int j=0;
    for (int i=0; i<strlen(name); i++){
        if (name[i]!='.'){
            j++;
        }
    }
    if (j==strlen(name)){
        return 1;
    }
    else
        return 0;
}
