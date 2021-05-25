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

    // initialize the holes
    allocator.cleanupHoles();

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

    for(int i = 1, n = allocator.m_holes.size(); i < n + 1; i++) {
        int startingAddress = allocator.m_holes[i-1].endingAddress();
        int segmentSize = i == n ?
                    size - startingAddress :
                    allocator.m_holes[i].startingAddress() - startingAddress;

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
    auto first = m_segments.begin();
    auto result = m_segments.begin();

    while (first != m_segments.end()) {
        if (first->processId() != processId) {
            if (result != first)
                *result = std::move(*first);
            ++result;
        } else {
            Segment seg(-1,
                        "Hole",
                        first->startingAddress(),
                        first->size(),
                        SegmentType::HOLE);
            m_holes.push_back(seg);
        }
        ++first;
    }
    m_segments.erase(result, m_segments.end());
    cleanupHoles();
}

void MemoryAllocator::compact()
{
    std::sort(m_segments.begin(), m_segments.end(), comp_address_func);
    m_segments[0].setStartingAddress(0);
    for(int i = 1; i < m_segments.size(); i++) {
        m_segments[i].setStartingAddress(m_segments[i-1].endingAddress());
    }

    Segment hole(-1,
                 "Hole",
                 m_segments.back().endingAddress(),
                 m_size - m_segments.back().endingAddress(),
                 SegmentType::HOLE);
    m_holes.clear();
    m_holes.push_back(hole);
}

QList<Segment> MemoryAllocator::segments() const
{
    return m_segments;
}

QList<Segment> MemoryAllocator::holes() const
{
    return m_holes;
}

void MemoryAllocator::cleanupHoles()
{
    std::sort(m_holes.begin(), m_holes.end(), comp_address_func);
    auto first = m_holes.begin();
    first++;
    auto result = m_holes.begin();

    while (first != m_holes.end()) {
        if (first->startingAddress() != result->endingAddress()) {
            ++result;
        } else {
             result->setSize(result->size() + first->size());
        }
        ++first;
    }
    m_holes.erase(result + 1, m_holes.end());
}

int MemoryAllocator::size() const
{
    return m_size;
}

void MemoryAllocator::setSize(int size)
{
    m_size = size;
}

QDebug operator<<(QDebug dbg, const MemoryAllocator &allocator) {
    dbg.nospace() << "Memory Allocator with size: " << allocator.size() << "\n\n"
                  << "Memory segments: " << allocator.m_segments.size() << "\n\n";
    for(const auto& seg : allocator.m_segments) {
        dbg.nospace() << seg << "\n";
    }

    dbg.nospace() << "Hole segments: " << allocator.m_holes.size() << "\n\n";
    for(const auto& seg : allocator.m_holes) {
        dbg.nospace() << seg << "\n";
    }
    return dbg.nospace();
}
