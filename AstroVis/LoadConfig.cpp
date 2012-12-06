
#include <iostream>
#include "globaldefs.h"
#include <string.h>
#include <unistd.h>
#include <fstream>

using namespace std;

static char* getRoot(string fpath) {
    char * result;
    string root = (char*)getenv("HOME");
    string resultPath = (root).append(fpath);
    result = new char [resultPath.size()+1];
    return strcpy(result,resultPath.c_str());
}

//TEST create function to output to console the current working directory
static void dispCWD() {
    ifstream workDir;
    workDir.open(".");
    fchdir(2);
    printf("CWD=%s\n", getcwd(NULL, 100) );
    char* result = (char*)getenv("SRCROOT");
    cout << result << endl;
    //testing commits
}


