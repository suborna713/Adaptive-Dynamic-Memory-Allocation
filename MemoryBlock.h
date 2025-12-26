#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H

#include <string>

class MemoryBlock {
public:
    int start;          // starting address
    int size;           // size of the block
    bool isFree;         // free or allocated
    std::string allocatedTo;  // process name

    MemoryBlock(int s, int sz);

    void print() const;
};

#endif
