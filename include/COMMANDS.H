#ifndef COMMANDS_H
#define COMMANDS_H

#include "Directories.h"
#include "FileManaging.h"
#include "Information.h"


class Commands
{
    public:
        void identifier(char *order, char *path, char **drive);
        Directories directory; ///object az classe Directories
        Information info; ///object az classe Information
        FileManaging file; ///object az classe FileManaging
};

#endif // COMMANDS_H
