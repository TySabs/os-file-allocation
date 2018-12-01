/*********************************************************************
 * Name: Tyler Saballus
 * Date: 11/30/2018
 * Operating Systems 480 - Hutchins - Boley/Crumpton
 * Assignment 7 - File Allocation
 ***********************************************************************/

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "entry.h"

using std::cerr;
using std::endl;
using std::vector;
using std::ifstream;

const int BLOCK_SIZE = 512;
const int MAX_ENTRIES = 12;
const int HOW_OFTEN = 5;

void printFAT(vector<Entry> *fileTable) {
  cerr << "Contents of the File Allocation Table" << endl;

  for (int i = 0; i < 240; i++) {
    if (i % 12 == 0) {
      cerr << endl;
      cerr << "#xxx-xxx\t";
    }

    Entry thisEntry = fileTable->at(i);
    string thisCppName = thisEntry.getName();
    const char *thisName = thisCppName.c_str();

    int compareFlag = strcmp(thisName, "*** Null Block ***");
    if (compareFlag == 0) {
      cerr << "0\t";
    } else {
      cerr << thisEntry.getStartingBlock() << "\t";
    }

  }

  cerr << endl;
}


int main() {
  cerr << "Beginning of the FAT simulation" << endl << endl;

  vector<Entry> FAT = vector<Entry>(240);
  FAT[0] = Entry("..", 0, -1);
  FAT[1] = Entry(".", 512, -1);
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

  int transactionCount = 1;

  while (isReadingFile && infile && transactionCount < 21) {
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

    if (transactionCount % HOW_OFTEN == 0) {
      printFAT(&FAT);
    }

    if (isReadingFile) {
      infile >> transactionType;
    }

    transactionCount++;
  } // end while isReadingFile

  return 0;
};
