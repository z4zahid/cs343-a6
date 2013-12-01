#ifndef _PRINTER_GUARD
#define _PRINTER_GUARD

#include <uC++.h>
#include <vector>
#include <string>

_Monitor Printer {
  public:
  	~Printer();
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
  private:
    unsigned int numStudents;
    unsigned int numVendingMachines;
    unsigned int numCouriers;
    bool havePrintedColumnLabels;
    std::vector<std::string>* stateBuffer;
    int totalTasks;
    int getStateBufferIndex(Kind kind, unsigned int id);
    void printFinishedRow(unsigned int index);
    void flushBuffers();
    void clearBuffer();
    void printColumnLabels();
    void updateStateBufferForIndex(unsigned int stateBufferIndex, char state, std::string data);
};

#endif