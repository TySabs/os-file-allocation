/*********************************************************************
 * Name: Tyler Saballus
 * Date: 11/30/2018
 * Operating Systems 480 - Hutchins - Boley/Crumpton
 * Assignment 7 - File Allocation
 ***********************************************************************/

#include <iostream>
#include <fstream>
#include "entry.h"

using std::cerr;
using std::endl;
using std::ifstream;

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

  ifstream infile;
  infile.open("./data7.txt");

  if (!infile) {
    cerr << "Unable to open file data7.txt" << endl;
  }

  char transactionType;
  string mainFile, targetFile;
  int fileSize;
  bool isReadingFile = true;

  infile >> transactionType;

  while (isReadingFile && infile) {
    switch (transactionType) {
      case 'N':
        cerr << "N Called" << endl;
        infile >> mainFile;
        infile >> fileSize;
        break;
      case 'M':
        cerr << "M Called" << endl;
        infile >> mainFile;
        infile >> fileSize;
        break;
      case 'C':
        cerr << "C Called" << endl;
        infile >> mainFile;
        infile >> targetFile;
        break;
      case 'R':
        cerr << "R Called" << endl;
        infile >> mainFile;
        infile >> targetFile;
        break;
      case 'D':
        cerr << "D Called" << endl;
        infile >> mainFile;
        break;
      case '?':
        cerr << "Ending Program" << endl;
        isReadingFile = false;
        break;
    } // end switch transactionType

    if (isReadingFile) {
      infile >> transactionType;
    }
  } // end while isReadingFile

  return 0;
};
