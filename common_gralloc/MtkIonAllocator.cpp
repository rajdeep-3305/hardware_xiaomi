#include "MtkIonAllocator.h"
#include <fcntl.h>
#include <unistd.h>
#include <linux/ion.h>
#include <sys/ioctl.h>
#include <log/log.h>

#define ION_HEAP_SYSTEM_MASK (1 << 0)  // Use system heap; you may adjust this for secure/camera

namespace gralloc {

int MtkIonAllocator::AllocateBuffer(int size, int usage, int *out_fd) {
    int ion_fd = open("/dev/ion", O_RDONLY | O_CLOEXEC);
    if (ion_fd < 0) {
        ALOGE("Failed to open /dev/ion");
        return -errno;
    }

    struct ion_allocation_data alloc = {};
    alloc.len = size;
    alloc.heap_id_mask = ION_HEAP_SYSTEM_MASK;
    alloc.flags = 0;

    if (ioctl(ion_fd, ION_IOC_ALLOC, &alloc) < 0) {
        ALOGE("ION_IOC_ALLOC failed");
        close(ion_fd);
        return -errno;
    }

    struct ion_fd_data fd_data = {};
    fd_data.handle = alloc.handle;

    if (ioctl(ion_fd, ION_IOC_SHARE, &fd_data) < 0) {
        ALOGE("ION_IOC_SHARE failed");
        ioctl(ion_fd, ION_IOC_FREE, &alloc.handle);
        close(ion_fd);
        return -errno;
    }

    ioctl(ion_fd, ION_IOC_FREE, &alloc.handle);
    close(ion_fd);

    *out_fd = fd_data.fd;
    return 0;
}

}  // namespace gralloc
