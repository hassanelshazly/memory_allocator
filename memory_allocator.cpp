#include "memory_allocator.h"

MemoryAllocator::MemoryAllocator()
{

}

void MemoryAllocator::deleteProcess(int processId)
{
    std::remove_if(m_segments.begin(), m_segments.end(), [processId](const Segment& seg) {
        return seg.processId() == processId;
    });
}
