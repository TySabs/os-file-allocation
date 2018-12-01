#ifndef ENTRY_H
  #define ENTRY_H

  /*********************************************************************
   * Name: Tyler Saballus
   * Date: 11/30/2018
   * Operating Systems 480 - Hutchins - Boley/Crumpton
   * Assignment 7 - File Allocation
   ***********************************************************************/
   #include <string>
   using std::string;

  class Entry {
    private:
      string name;
      int size;
      int startingBlock;
    public:
      Entry();
      Entry(string, int);
      Entry(string, int, int);
      void printInfo();
      string getName();
      int getSize();
  };

#endif
