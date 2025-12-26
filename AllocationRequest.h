#ifndef ALLOCATIONREQUEST_H
#define ALLOCATIONREQUEST_H

#include <string>

class AllocationRequest {
public:
    std::string processName;
    int requestedSize;

    AllocationRequest(std::string name, int size);
};

#endif
