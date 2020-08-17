#ifndef MANAGING_H
#define MANAGING_H


class Managing
{
    public:
        //Managing();
        //virtual ~Managing();
        void copyRec(char *second_part, char *third_part, char *forth_part, char *path);
        void delRec(char *second_part, char *third_part, char *path);
        void reName(char *second_part, char *third_part, char *path);
        void findRec(char *second_part, char *third_part, char *path);



};
#endif // MANAGING_H

void makeAddCopy(char *, char*, char*, char *, char*, char*);
void copy(char *, char *);
int validate(char *);
int motlagh(char *);
void makeAddDel(char *, char *, char *);
void delFolder(char *);
void showDel();
int perDel(char *);
int isFolder(char *);
int starRec(char *);
void find(char *, char *);
void starFind(char *, char *);
int sameRec(char *, char *);
