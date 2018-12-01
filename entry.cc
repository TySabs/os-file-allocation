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
  name = "cool-stuff";
}

Entry::Entry(string newName, int newSize) {
  name = newName;
  size = newSize;
  startingBlock = 0;
}

Entry::Entry(string newName, int newSize, int newStart) {
  name = newName;
  size = newSize;
  startingBlock = newStart;
}

void Entry::printInfo() {
  cerr << "File name: " << setw(18) << std::left << name << "\tFile Size: " << size << endl;
}

string Entry::getName() {
  return name;
}

int Entry::getSize() {
  return size;
}
