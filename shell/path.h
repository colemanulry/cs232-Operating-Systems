//
//  path.h
//  CS232 Command Shell
//
//  Author: Coleman Ulry
//  Date: 2/28/21
//  h class to represent directories
//

#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
using namespace std;

class Path
{
public:
  Path();
  int find(const string &program);
  string getDirectory(int i) const;

private:
  // vector or strings to store each directory
  vector<string> pathItems;
};
