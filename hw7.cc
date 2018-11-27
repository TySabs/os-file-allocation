/*********************************************************************
 * Name: Tyler Saballus
 * Date: 11/30/2018
 * Operating Systems 480 - Hutchins - Boley/Crumpton
 * Assignment 7 - File Allocation
 ***********************************************************************/

#include <iostream>
#include "entry.h"

using std::cerr;
using std::endl;

const int BLOCK_SIZE = 512;
const int MAX_ENTRIES = 12;
const int HOW_OFTEN = 6;


int main() {
  Entry FAT[240];
  FAT[0] = Entry("..", 0, 0);
  FAT[1] = Entry(".", 0);

  for (int i = 2; i < 240; i++) {
    FAT[i] = Entry();
  }

  string foo = FAT[0].getName();
  cerr << "Hello FAT0: " << foo << endl;

  string bar = FAT[1].getName();
  cerr << "Hello FAT1: " << bar << endl;

  string baz = FAT[2].getName();
  cerr << "Hello FAT2: " << baz << endl;

  return 0;
};
