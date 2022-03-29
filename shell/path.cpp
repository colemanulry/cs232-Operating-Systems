//
//  path.cpp
//  CS232 Command Shell
//
//  Author: Coleman Ulry
//  Date: 2/28/21
//  cpp class to represent directories
//

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include "path.h"
using namespace std;

// vector of strings created for each directory
Path::Path()
{

  // reference: http://www.cplusplus.com/reference/cstdlib/getenv/
  char *myPath = getenv("PATH");

  // reference: https://www.programiz.com/cpp-programming/library-function/cstring/strtok#:~:text=The%20strtok()%20function%20returns,no%20more%20tokens%20are%20found.
  // delimiter is :
  char *singlePath = strtok(myPath, ":");

  // while it hasn't reached the end of PATH
  while (singlePath != NULL)
  {
    // append to vector
    pathItems.push_back(singlePath);
    // get next path item
    singlePath = strtok(NULL, ":");
  }
}

// returns index of the program found within PATH, returns -1 otherwise
int Path::find(const string &program)
{

  int index = 0;

  DIR *directory;
  struct dirent *pDirent;
  const char *thisDir;

  // loop through for each item in pathItems
  // reference: https://stackoverflow.com/questions/3554120/open-directory-using-c
  for (unsigned i = 0; i < pathItems.size(); i++)
  {
    thisDir = pathItems[i].c_str();
    directory = opendir(thisDir);

    // make sure it opened successfully
    if (directory == NULL)
    {
      return -1;
    }
    else
    {
      // reference: https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
      if ((pDirent = readdir(directory)) == NULL)
      {
        closedir(directory);
        return -1;
      }
      else
      {
        // if program name matches program argument
        // reference: https://www.cplusplus.com/forum/general/4648/
        if (pDirent->d_name == program)
        {
          // close directory
          closedir(directory);

          // return that program's index
          return i;
        }
      }
    }
  }
}

// returns directory at index i
string Path::getDirectory(int i) const
{
  // make sure index isn't out of range
  if (i < 0)
  {
    cerr << "Index out of range... " << endl;
  }
  else
  {
    return pathItems[i];
  }
}
