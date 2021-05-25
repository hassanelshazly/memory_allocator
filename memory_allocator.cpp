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

    if(allocator.m_holes.back().endingAddress() > size)
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

void MemoryAllocator::compact()
{
    std::sort(m_segments.begin(), m_segments.end(), comp_address_func);
    m_segments[0].setStartingAddress(0);
    for(int i = 1; i < m_segments.size(); i++) {
        m_segments[i].setStartingAddress(m_segments[i-1].endingAddress());
    }

    Segment hole(-1,
                 "Hole 0",
                 m_segments.back().endingAddress(),
                 m_size - m_segments.back().endingAddress(),
                 SegmentType::HOLE);
    m_holes.push_back(hole);
}

QList<Segment> MemoryAllocator::getSegments() const
{
    return m_segments;
}

QList<Segment> MemoryAllocator::getHoles() const
{
    return m_holes;
}

int MemoryAllocator::getSize() const
{
    return m_size;
}

void MemoryAllocator::setSize(int size)
{
    m_size = size;
}
