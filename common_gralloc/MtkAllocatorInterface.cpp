#include "MtkAllocatorInterface.h"
#include "MtkIonAllocator.h"
#include <cutils/properties.h>

#define USE_DMA_BUF_HEAPS_PROP "ro.vendor.dma_buf_heaps.enabled"

namespace gralloc {

AllocatorInterface *AllocatorInterface::GetInstance() {
    static AllocatorInterface *instance = nullptr;
    if (instance) return instance;

    char property[PROPERTY_VALUE_MAX] = {0};
    instance = MtkIonAllocator::GetInstance();

    return instance;
}

}  // namespace gralloc