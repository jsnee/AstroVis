//
//  LoadConfig.cpp
//  AstroVis
//
//  Created by  on 10/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "globaldefs.h"
#include <string.h>

using namespace std;

static char* getRoot(string fpath) {
    char * result;
    string root = (char*)getenv("HOME");
    string resultPath = (root).append(fpath);
    //strcat(resultPath, fpath);
    result = new char [resultPath.size()+1];
    return strcpy(result,resultPath.c_str());
}



