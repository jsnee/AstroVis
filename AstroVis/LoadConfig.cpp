
#include <iostream>
#include "globaldefs.h"
#include <string.h>

using namespace std;

static char* getRoot(string fpath) {
    char * result;
    string root = (char*)getenv("HOME");
    string resultPath = (root).append(fpath);
    result = new char [resultPath.size()+1];
    return strcpy(result,resultPath.c_str());
}



