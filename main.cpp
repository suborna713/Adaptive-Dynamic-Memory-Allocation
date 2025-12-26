#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct MemoryBlock {
    int start;
    int size;
    bool free;
    string allocatedTo;

    MemoryBlock(int s, int sz, bool f, string a) {
        start = s;
        size = sz;
        free = f;
        allocatedTo = a;
    }
};

vector<MemoryBlock> memory;

// ---------- PRINT MEMORY ----------
void printMemory() {
    for (auto &b : memory) {
        cout << "[" << b.start << " - " << b.start + b.size << "] "
             << "Size: " << b.size << " | "
             << (b.free ? "Free" : "Used")
             << " | Allocated To: " << b.allocatedTo << endl;
    }
    cout << endl;
}

// ---------- MERGE FREE BLOCKS ----------
void mergeFreeBlocks() {
    for (size_t i = 0; i < memory.size() - 1; i++) {
        if (memory[i].free && memory[i + 1].free) {
            memory[i].size += memory[i + 1].size;
            memory.erase(memory.begin() + i + 1);
            i--;
        }
    }
}

// ---------- FIRST FIT ----------
void firstFit(string pid, int req) {
    for (size_t i = 0; i < memory.size(); i++) {
        if (memory[i].free && memory[i].size >= req) {
            MemoryBlock used(memory[i].start, req, false, pid);

            memory[i].start += req;
            memory[i].size -= req;

            memory.insert(memory.begin() + i, used);
            if (memory[i + 1].size == 0)
                memory.erase(memory.begin() + i + 1);
            return;
        }
    }
}

// ---------- DEALLOCATE ----------
void deallocate(string pid) {
    for (auto &b : memory) {
        if (!b.free && b.allocatedTo == pid) {
            b.free = true;
            b.allocatedTo = "None";
        }
    }
    mergeFreeBlocks();
}

// ---------- MEMORY COMPACTION ----------
void compactMemory() {
    vector<MemoryBlock> newMemory;
    int currentAddress = 0;
    int totalFree = 0;

    // Move used blocks to start
    for (auto &b : memory) {
        if (!b.free) {
            newMemory.push_back(
                MemoryBlock(currentAddress, b.size, false, b.allocatedTo)
            );
            currentAddress += b.size;
        } else {
            totalFree += b.size;
        }
    }

    // Add one large free block at the end
    if (totalFree > 0) {
        newMemory.push_back(
            MemoryBlock(currentAddress, totalFree, true, "None")
        );
    }

    memory = newMemory;
}

// ---------- MAIN ----------
int main() {
    cout << "Adaptive Dynamic Memory Allocation Tool\n";
    cout << "Phase 6: Memory Compaction\n\n";

    // Initial memory
    memory.push_back(MemoryBlock(0, 1000, true, "None"));
    printMemory();

    // Allocations
    firstFit("P1", 200);
    firstFit("P2", 300);
    firstFit("P3", 100);

    cout << "--- After Allocations ---\n";
    printMemory();

    // Deallocate to create fragmentation
    cout << "--- Deallocating P2 ---\n";
    deallocate("P2");
    printMemory();

    // Compaction
    cout << "--- Performing Memory Compaction ---\n";
    compactMemory();
    printMemory();

    cout << "Phase 6 completed successfully.\n";
    system("pause");
    return 0;
}
