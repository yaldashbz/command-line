#ifndef FILEMANAGING_H
#define FILEMANAGING_H


class FileManaging
{
    public:
        void copyRec(char *second_part, char *third_part, char *forth_part, char *path);
        void delRec(char *second_part, char *third_part, char *path);
        void reName(char *second_part, char *third_part, char *path);
        void findRec(char *second_part, char *third_part, char *path);

};
#endif // FILEMANAGING_H

void makeAddCopy(char *, char*, char*, char *, char*, char*);
void copy(char *, char *);
int isValid(char *);
int isAbsolute(char *);
void makeAddDel(char *, char *, char *);
void delFolder(char *);
void showDel();
int perDel(char *);
int isFolder(char *);
int starRec(char *);
void find(char *, char *);
void starFind(char *, char *);
int sameRec(char *, char *);
