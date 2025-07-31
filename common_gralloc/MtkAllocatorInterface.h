#pragma once

namespace gralloc {

class AllocatorInterface {
public:
    virtual ~AllocatorInterface() {}

    static AllocatorInterface *GetInstance();

    virtual int AllocateBuffer(int size, int usage, int *out_fd) = 0;
};

}  // namespace gralloc