#include "MemoryBlock.h"
#include <iostream>

MemoryBlock::MemoryBlock(int s, int sz) {
    start = s;
    size = sz;
    isFree = true;
    allocatedTo = "None";
}

void MemoryBlock::print() const {
    std::cout << "["
              << start << " - "
              << (start + size)
              << "] Size: " << size
              << " | " << (isFree ? "Free" : "Used")
              << " | Allocated To: " << allocatedTo
              << std::endl;
}
