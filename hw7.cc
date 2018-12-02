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

int findFreeBlock(short *fileTable) {
  for (int i = 0; i < 240; i++) {
    if (fileTable[i] == 0) {
      return i;
    }
  }

  return -1;
}

int calculateClusterSize(int newSize) {
  double clusterSize;
  clusterSize = (double) newSize / BLOCK_SIZE;
  clusterSize = ceil(clusterSize);
  return (int) clusterSize;
}

int searchForFile(vector<Entry> *entries, string targetString) {
  vector<Entry>::iterator it;
  Entry *thisEntry;

  for (unsigned int i = 0; i < entries->size(); i++) {
    thisEntry = &entries->at(i);
    if (thisEntry->getName() == targetString) {
      return (int) i;
    }
  }
  return -1;
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

void printEntryList(vector<Entry> *entries, int count, int totalSize) {
  for (int i = 0; i < 240; i++) {
    Entry thisEntry = entries->at(i);
    string thisCppName = thisEntry.getName();
    const char *thisName = thisCppName.c_str();

    int compareFlag = strcmp(thisName, "*** Null Block ***");
    if (compareFlag != 0) {
      thisEntry.printInfo();
      cerr << "Cluster(s) in use: ";
      if (thisEntry.getStartingBlock() == -1) {
        cerr << "(none)";
      }

      list<int>::iterator it;
      for (it = thisEntry.clusters.begin(); it != thisEntry.clusters.end(); ++it) {
        cerr << setw(4) << *it;
      }

      cerr << endl;
    }

  } // end for loop

  cerr << "Files: " << count << "\tTotalSize: " << totalSize << endl << endl;
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
  entryList[0] = Entry(".", 512, 0);
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

  int fileSize,
      totalFileSize = 512,
      transactionCount = 1,
      matchedFile = -1,
      nextBlock = -1,
      oldBlock = -1,
      clusterTotal = 1;

  bool isReadingFile = true;

  infile >> transactionType;


  while (isReadingFile && infile && transactionCount < 11) {
    Entry newEntry;
    int clustersNeeded = 0, clustersAllocated = 0;
    bool isFirstInsert = true;

    switch (transactionType) {
      case 'N':
        cerr << "Transaction: Add a new file" << endl;

        infile >> mainFile;
        infile >> fileSize;

        if (searchForFile(&entryList, mainFile) != -1) {
          cerr << "Error! File already exists" << endl;
          continue;
        }

        clustersNeeded = calculateClusterSize(fileSize);

        for (short i = 0; i < 240; i++) {
          if (FAT[i] == 0) {
            if (isFirstInsert) {
              newEntry = Entry(mainFile, fileSize, i);
              isFirstInsert = false;
            }

            newEntry.clusters.push_back(i);
            FAT[i] = clusterTotal + 1;
            clustersAllocated++;
            clusterTotal++;

            if (clustersNeeded == clustersAllocated) {
              FAT[i] = -1;
              break;
            }
          } // end if FAT entry is blank (zero)
        } // end for loop

        fileCount++;
        totalFileSize += fileSize;
        entryList[fileCount] = newEntry;

        cerr << "Successfully added a new file, " << newEntry.getName()
              << ", of size " << newEntry.getSize() << endl;
        break;
      case 'M':
        cerr << "Transaction: Modify a file" << endl;
        infile >> mainFile;
        infile >> fileSize;

        matchedFile = searchForFile(&entryList, mainFile);

        if (matchedFile == -1) {
          cerr << "Error! Unable to match file: " << mainFile << endl;
          break;
        }

        totalFileSize -= entryList[matchedFile].getSize();
        totalFileSize += fileSize;

        nextBlock = findFreeBlock(FAT);
        newEntry = Entry(mainFile, fileSize, nextBlock);

        if (nextBlock == 0) {
          cerr << "Error! Unable to find free block" << endl;
          break;
        }

        clustersNeeded = calculateClusterSize(fileSize);

        while (clustersAllocated != clustersNeeded) {
          if (FAT[nextBlock] == 0) {
            newEntry.clusters.push_back(nextBlock);
            FAT[nextBlock] = clusterTotal;
            clustersAllocated++;
            clusterTotal++;
          }

          if (clustersAllocated == clustersNeeded) {
            FAT[nextBlock] = -1;
          }

          nextBlock++;
        } // end while loop

        while (entryList[matchedFile].clusters.size() > 0) {
          oldBlock = entryList[matchedFile].clusters.back();
          FAT[oldBlock] = 0;
          entryList[matchedFile].clusters.pop_back();
        }

        entryList[matchedFile] = newEntry;

        cerr << "Successfully modified a file, " << mainFile << endl;
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
      printEntryList(&entryList, fileCount, totalFileSize);
      printFAT(FAT);
    }

    if (isReadingFile) {
      infile >> transactionType;
    }

    transactionCount++;
  } // end while isReadingFile

  return 0;
};
