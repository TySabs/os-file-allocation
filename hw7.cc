/*********************************************************************
 * Name: Tyler Saballus
 * Date: 11/30/2018
 * Operating Systems 480 - Hutchins - Boley/Crumpton
 * Assignment 7 - File Allocation
 ***********************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <math.h>
#include <vector>
#include "entry.h"

using std::cerr;
using std::endl;
using std::setw;
using std::setfill;
using std::vector;
using std::ifstream;

const int BLOCK_SIZE = 512;
const int MAX_ENTRIES = 12;
const int HOW_OFTEN = 5;

bool searchForFile(vector<Entry> *entries, string targetString) {
  vector<Entry>::iterator it;
  Entry *thisEntry;

  for (unsigned int i = 0; i < entries->size(); i++) {
    thisEntry = &entries->at(i);
    if (thisEntry->getName() == targetString) {
      return true;
    }
  }
  return false;
}

void printFAT(short *fileTable) {
  cerr << "Contents of the File Allocation Table" << endl;

  int rangeStart = 0, rangeEnd = 11;
  for (int i = 0; i < 240; ++i) {
    if (i % MAX_ENTRIES == 0) {
      if (i > 0) {
        cerr << endl;
        rangeStart += 12;
        rangeEnd += 12;
      }

      cerr << "#" << setfill('0') << std::right <<  setw(3) << rangeStart << "-"
            << std::right << setw(3) << rangeEnd;
    }

    cerr << setfill(' ') << setw(6) << fileTable[i];
  }

  cerr << endl << endl;
}

void printEntryList(vector<Entry> *entries) {
  for (int i = 0; i < 240; i++) {
    Entry thisEntry = entries->at(i);
    string thisCppName = thisEntry.getName();
    const char *thisName = thisCppName.c_str();

    int compareFlag = strcmp(thisName, "*** Null Block ***");
    if (compareFlag != 0) {
      thisEntry.printInfo();
      cerr << "Cluster(s) in use: ";
      if (thisEntry.getSize() > 0) {
        cerr << "(none)";
      }

      cerr << endl;
    }

  } // end for loop

  cerr << endl;
}

/******************************************************************
 *
 *                Main Function
 *
 ******************************************************************/
int main() {
  cerr << "Beginning of the EntryList simulation" << endl << endl;

  vector<Entry> entryList = vector<Entry>(240);
  short FAT[240];
  entryList[0] = Entry(".", 512, -1);
  entryList[1] = Entry("..", 0);

  FAT[0] = -1;
  FAT[1] = 0;
  int fileCount = 2;

  for (int i = 2; i < 240; i++) {
    entryList[i] = Entry();
    FAT[i] = 0;
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
    int clustersNeeded = 0, clustersAllocated = 0;
    double clusterSize;

    switch (transactionType) {
      case 'N':
        cerr << "Transaction: Add a new file" << endl;

        infile >> mainFile;
        infile >> fileSize;

        clusterSize = (double) fileSize / BLOCK_SIZE;
        clusterSize = ceil(clusterSize);
        clustersNeeded = (int) clusterSize;

        newEntry = Entry(mainFile, fileSize);
        for (int i = 0; i < 240; i++) {
          if (clustersNeeded == clustersAllocated) {
            break;
          }
        }

        fileCount++;
        entryList[fileCount] = newEntry;

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
      cerr << endl;
      printEntryList(&entryList);
      printFAT(FAT);
    }

    if (isReadingFile) {
      infile >> transactionType;
    }

    transactionCount++;
  } // end while isReadingFile

  return 0;
};
