#include "Files.h"
#include <string.h>


Files::copyRec(char *second_part, char *third_part, char *forth_part, char *path){
    char *src = new char [100];
    char *des = new char [100];
    char *des2 = new char [100];
    if(!strcmp(second_part,"\\x") || !strcmp(second_part,"-x")){

        makeAddCopy(third_part,forth_part,path,src,des,des2);
        if(validate(src) && validate(des2)){
            copy(src,des);
            remove(src);

        }
        else
            printf("Not Validate.");
    }
    else{

        makeAddCopy(second_part,third_part,path,src,des,des2);
        if(validate(src) && validate(des2))
            copy(src,des);
        else
            printf("Not Validate.");


    }
    delete src;
    delete des;
    delete des2;
}

void makeAddCopy(char second_part[], char third_part[],char *path,char *src,char *des,char *des2){

            char *filename = new char [100];
            int i = length(second_part) - 1 ;
            while(second_part[i] != '\\' && i>=0){
                i--;
            }
            i++;
            int j = 0,m;
            for( m=i; m<length(second_part) ;m++){
                filename[j] = second_part[m];
                j++;
            }
            filename[j] = '\0';
            ///
        if(motlagh(second_part)) {
            strcpy(src,second_part);
            if(motlagh(third_part)){
                strcpy(des,third_part);
                strcpy(des2,des); ///for pass to check validate
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
            if(motlagh(third_part)){
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

        if(desptr == NULL ){
            fclose(srcptr);
        }

        for(i = 0; i < leng; i++){
            fputc(fgetc(srcptr), desptr);
        }
    }
    fclose(srcptr);
    fclose(desptr);
}




Files::delRec(char *second_part, char *third_part, char *path){

    char *src = new char [100];
    if(!strcmp(second_part,"\\f")){
        makeAddDel(third_part,src,path);
        if (validate(src))
            delFolder(src);
        else
            printf("Not Validate.\n");
    }
    else if(!strcmp(second_part,"\\?") || !strcmp(second_part,"-?")){
        showDel();
    }
    else if(!strcmp(second_part,"\\p") || !strcmp(second_part,"-p")){
        makeAddDel(third_part,src,path);
        if (validate(src))
            perDel(src);
        else{
            printf("Not Validate.\n");
        }
    }
    else{
        makeAddDel(second_part,src,path);
        if (validate(src))
            remove(src);
        else
            printf("Not Validate.\n");
    }
}

void showDel(){
    printf("Deletes one or more files.\n"
           "DEL [/P] [/F] [/?]\n"
           " /P          Gets permission from user.\n"
           " /F          Deletes a folder.\n"
           " /?          Provides Help information for DEL commands.\n");
}

void perDel(char src[]){
    char per;

        printf("%s,Delete(Y/N)?",src);
        scanf(" %c",&per);
        if( per == 'y'|| per == 'Y'){
            remove(src);
        }
        else if( per == 'n'|| per=='N')
            return 0;

        else{
            perDel(src);
        }

}

void delFolder(char *path){
    char *path2=new char[100];
    DIR *dirptr;
    struct dirent *entry;
    dirptr= opendir(path);
    while (entry=readdir(dirptr)){
            strcpy(path2,path);
            strcat(path2,"\\");
            strcat(path2,entry->d_name);
            if (recFolder(entry->d_name))
                delFolder(path2);
            else
                remove(path2);
    }
    rmdir(path);
    delete path2;
}
void makeAddDel(char *third_part, char *src, char *path){
    if(motlagh(third_part))
            strcpy(src,third_part);
        else{
            strcpy(src,path);
            strcat(src,"\\");
            strcat(src,third_part);
        }
}

Files::reName(char *second_part, char *third_part, char *path){

    int i = length(second_part) - 1;
    while(second_part[i] != '\\')
        i--;
    int j;
    for(j = 0; j < i ; j++){
        beforeName[j] = second_part[j];
    }
    beforeName[j] = '\0';

    char *destination = new char [100];
    char *src = new char [100];

    if(motlagh(second_part)){
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

    if(validate(src)){
        rename(src,destination);
    }
    else
        printf("Not Validate.\n");
}

Files::findRec(char *second_part, char *third_part, char *path){

    if(!starRec(second_part)){
        if(!strcmp(third_part,"")){
            char *path2 = new char [100];
            strcpy(path2,path);
            find(path2,second_part);
            delete path2;
        }
        else{
            find(third_part,second_part);
        }
    }
    else{
        if(!strcmp(third_part,"")){
            char *path2 = new char [100];
            strcpy(path2,path);
            starFind(path2,second_part);
            delete path2;
        }
        else{
            starFind(third_part,second_part);
        }
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

void find(char *path,char *file){ ///bi setare
    char *path2 = new char [100];
    DIR *dirptr;
    dirptr = opendir(path);
    struct dirent *entry;
    while (entry=readdir(dirptr)){
            if(!strcmp(entry->d_name,file)){
                strcpy(path2,path);
                strcat(path2,"\\");
                strcat(path2,entry->d_name);
                printf("%s\n",path2);
            }
            if (isFolder(entry->d_name)){
                strcat(path,"\\");
                strcat(path,entry->d_name);
                find(path,file);
            }
    }
    delete path2;
    closedir(dirptr);
}

void starFind(char *path,char *file){
    char *path2 = new char [100];
    DIR *dirptr;
    dirptr = opendir(path);
    struct dirent *entry;
    while(entry=readdir(dirptr)){
            if(sameRec(entry->d_name,file)){

                strcpy(path2,path);
                strcat(path2,"\\");
                strcat(path2,entry->d_name);
                printf("%s\n",path2);
            }
            if (isFolder(entry->d_name)){

                strcat(path,"\\");
                strcat(path,entry->d_name);
                starFind(path,file);
            }
    }
    delete path2;
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
    for (int i=0; i<strlen(name)); i++){
        if (name[i]!='.'){
            j++;
        }
    }
    if (j==length){
        return 1;
    }
    else
        return 0;
}

int motlagh(char *path){
    int i = 0;
    while(path[i]){
        if(path[i] == ':')
            return 1;
        i++;
    }

    return 0;
}

int validate (char *path){
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
