#include "memory_allocator.h"

MemoryAllocator::MemoryAllocator()
{

}

MemoryAllocator::MemoryAllocator(int size)
    :  m_size(size)
{

}

MemoryAllocator MemoryAllocator::makeFromHoles(const QList<Segment> &holes, int size)
{
    // initialize new allocator with c
    MemoryAllocator allocator(size);
    allocator.m_holes = holes;

    // sort by starting address
    std::sort(allocator.m_holes.begin(), allocator.m_holes.end(), comp_address_func);

    if(allocator.m_holes.back().startingAddress() +
            allocator.m_holes.back().size() > size)
        throw QString("A hole exceded the allocated size");

    // make the reminder segments processes
    int id = 0;
    if (allocator.m_holes[0].startingAddress() != 0) {
        Segment seg(id++,
                    "Old Process",
                    0,
                    allocator.m_holes[0].startingAddress(),
                    SegmentType::PROCESS);
        allocator.m_segments.push_back(seg);
    }

    for(int i = 1, n = allocator.m_holes.size(); i < n; i++) {
        int startingAddress = allocator.m_holes[i-1].startingAddress() +
                allocator.m_holes[i-1].size();
        int segmentSize = i == n - 1 ?
                    size - startingAddress :
                    allocator.m_holes[i+1].startingAddress() - startingAddress;

        Segment seg(id++,
                    "Old Process",
                    startingAddress,
                    segmentSize,
                    SegmentType::PROCESS);

        if(segmentSize < 0)
            throw QString("Overlaping holes");
        else if (segmentSize > 0)
            allocator.m_segments.push_back(seg);
    }

    return allocator;
}

void MemoryAllocator::deleteProcess(int processId)
{
    std::remove_if(m_segments.begin(), m_segments.end(), [processId](const Segment& seg) {
        return seg.processId() == processId;
    });
}

int MemoryAllocator::getSize() const
{
    return m_size;
}

void MemoryAllocator::setSize(int size)
{
    m_size = size;
}
