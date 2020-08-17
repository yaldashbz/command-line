#ifndef DIRECTORIES_H
#define DIRECTORIES_H

///in class b command haye "dir", "cd", "tree", "chdir" marbut ast.
class Directories
{
    ///tabe haye dakhele in class har kodam be yeki az command ha taalogh darad.
    public:
        void dirRec(char *path, char *second_part,char *third_part,char *forth_part);
        void cdRec(char *second_part,char *third_part,char *path,char **drive);
        void chdirRec(char *path, char *second_part,char **drive);
        void treeRec(char *second_part, char *third_part, char *path);

};
void chdirPrint(int ,char **,char *);
void showDir(char *);
void dirInFile(char *, char *);
void nameSort(char *);
void suffixSort(char *);
void recursiveDir(char *);
int isAbsolute(char *);
void strsort(char *, char *);
int isFolder(char *);
void strsort2(char *, char *, char *, char *);
void cdDoubleDot(char *);
int isValid(char *);
void showCd();
int chdirMake(char *, char *, char **);
void treeInFile(char *,char *,const int);
void tree(char *,const int);
void chdirPrint(int);
#endif // DIRECTORIES_H



