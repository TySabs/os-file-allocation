#ifndef ENTRY_H
  #define ENTRY_H

  /*********************************************************************
   * Name: Tyler Saballus
   * Date: 11/30/2018
   * Operating Systems 480 - Hutchins - Boley/Crumpton
   * Assignment 7 - File Allocation
   ***********************************************************************/
   #include <string>
   #include <list>

   using std::list;
   using std::string;

  class Entry {
    private:
      string name;
      int size;
      int startingBlock;
    public:
      list<int> clusters;

      Entry();
      Entry(string, int);
      Entry(string, int, int);
      int getStartingBlock();
      void printInfo();
      string getName();
      int getSize();
      void setSize(int);
  };

#endif
