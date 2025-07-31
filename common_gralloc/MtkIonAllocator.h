#pragma once
#include "MtkAllocatorInterface.h"

namespace gralloc {

class MtkIonAllocator : public AllocatorInterface {
public:
    static MtkIonAllocator *GetInstance();
    int AllocateBuffer(int size, int usage, int *out_fd) override;

private:
    MtkIonAllocator() = default;
};

}  // namespace gralloc