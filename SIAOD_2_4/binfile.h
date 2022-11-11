#ifndef _BINFILE_H
#define _BINFILE_H
#include "Node.h"

struct binfile {
    static void textToBin(string text, string bin);
    static int searchBin(string bin, string name);
    static Node directAccessBin(string bin, int index);
    static void addBin(string bin, Node node);
};

#endif 
