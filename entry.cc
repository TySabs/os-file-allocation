/*********************************************************************
 * Name: Tyler Saballus
 * Date: 11/30/2018
 * Operating Systems 480 - Hutchins - Boley/Crumpton
 * Assignment 7 - File Allocation
 ***********************************************************************/

#include <iostream>
#include <iomanip>
#include "entry.h"

using std::cerr;
using std::endl;
using std::setw;

/***********************************************************************
 * Entry constructor
 *
 * Arguments(0):
 *
 * Use: Creates a null entry
 ***********************************************************************/
Entry::Entry() {
  startingBlock = 0;
  size = 0;
  name = "*** Null Block ***";
}

/***********************************************************************
 * Entry constructor
 *
 * Arguments(2):
 *   1. newName - name of entry
 *   2. newSize - size of entry
 *
 * Use: Creates an entry without a starting block
 ***********************************************************************/
Entry::Entry(string newName, int newSize) {
  name = newName;
  size = newSize;
  startingBlock = -1;
}

/***********************************************************************
 * Entry constructor
 *
 * Arguments(3):
 *   1. newName - name of entry
 *   2. newSize - size of entry
 *   2. newStart - starting block of entry
 *
 * Use: Creates an entry with a starting block
 ***********************************************************************/
Entry::Entry(string newName, int newSize, int newStart) {
  name = newName;
  size = newSize;
  startingBlock = newStart;
}

/***********************************************************************
 * Entry.printInfo method
 *
 * Arguments(0):
 *
 * Returns: void
 *
 * Use: Prints out the contents of the Entry
 ***********************************************************************/
void Entry::printInfo() {
  cerr << "File name: " << setw(18) << std::left << name << "File Size: " << size << endl;
}

/***********************************************************************
 * Entry.getName method
 *
 * Arguments(0):
 *
 * Returns: string - the name
 *
 * Use: Gets name of the entry
 ***********************************************************************/
string Entry::getName() {
  return name;
}

/***********************************************************************
 * Entry.setName method
 *
 * Arguments(1):
 *   1. newName - the new name
 *
 * Returns: void
 *
 * Use: Sets name of the entry
 ***********************************************************************/
void Entry::setName(string newName) {
  name = newName;
}


/***********************************************************************
 * Entry.getSize method
 *
 * Arguments(0):
 *
 * Returns: int - the size
 *
 * Use: Gets size of the entry
 ***********************************************************************/
int Entry::getSize() {
  return size;
}

/***********************************************************************
 * Entry.setName method
 *
 * Arguments(1):
 *   1. newSize - the new size
 *
 * Returns: void
 *
 * Use: Sets size of the entry
 ***********************************************************************/
void Entry::setSize(int newSize) {
  size = newSize;
}


/***********************************************************************
 * Entry.getStartingBlock method
 *
 * Arguments(0):
 *
 * Returns: int - the staerting block
 *
 * Use: Gets starting block of the entry
 ***********************************************************************/
int Entry::getStartingBlock() {
  return startingBlock;
}
