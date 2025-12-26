#include "AllocationRequest.h"

AllocationRequest::AllocationRequest(std::string name, int size) {
    processName = name;
    requestedSize = size;
}
