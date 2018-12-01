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
  cerr << "Beginning of the FAT simulation" << endl << endl;



  Entry FAT[240];
  FAT[0] = Entry("..", 0, 0);
  FAT[1] = Entry(".", 0);
  int fileCount = 2;

  for (int i = 2; i < 240; i++) {
    FAT[i] = Entry();
  }

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
    Entry newEntry;

    switch (transactionType) {
      case 'N':
        cerr << "Transaction: Add a new file" << endl;

        infile >> mainFile;
        infile >> fileSize;

        newEntry = Entry(mainFile, fileSize);

        fileCount++;
        FAT[fileCount] = newEntry;

        cerr << "Successfully added a new file, " << newEntry.getName()
              << ", of size " << newEntry.getSize() << endl;
        break;
      case 'M':
        cerr << "Transaction: Modify a file" << endl;
        infile >> mainFile;
        infile >> fileSize;
        break;
      case 'C':
        cerr << "Transaction: Copy a file" << endl;
        infile >> mainFile;
        infile >> targetFile;
        break;
      case 'R':
        cerr << "Transaction: Rename a file" << endl;
        infile >> mainFile;
        infile >> targetFile;
        break;
      case 'D':
        cerr << "Transaction: Delete a file" << endl;
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
