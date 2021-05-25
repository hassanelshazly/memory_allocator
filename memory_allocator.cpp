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
    processIds.remove(processId);
    cleanupHoles();
}

Segment MemoryAllocator::addSegment(const Segment &seg, AllocationType type)
{
    switch(type) {
    case AllocationType::FIRST_FIT :
        return addSegmentIn(seg, comp_address_func);
        break;
    case AllocationType::BEST_FIT :
        return addSegmentIn(seg, comp_size_func);
        break;
    case AllocationType::WORST_FIT :
        return addSegmentIn(seg, comp_size_backward_func);
        break;
    default:
        throw QString("Unknown AllocationType");
    }
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

Segment MemoryAllocator::addSegmentIn(
        Segment seg,
        std::function<bool(const Segment&, const Segment&)> comp_func)
{
    std::sort(m_holes.begin(), m_holes.end(), comp_func);

    bool done = false;
    for(int i = 0; i < m_holes.size(); i++) {
        if(m_holes[i].size() >= seg.size()) {
            seg.setStartingAddress(m_holes[i].startingAddress());
            int endAddress = m_holes[i].endingAddress();
            m_holes[i].setStartingAddress(seg.endingAddress());
            m_holes[i].setSize(
                        endAddress -
                        m_holes[i].startingAddress());
            done = true;
            if(m_holes[i].size() == 0) {
                m_holes.erase(m_holes.begin() + i);
            }
            break;
        }
    }
    if(!done)
        throw QString("Segment Does't fit in Memory");
    m_segments.push_back(seg);
    return seg;
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

QList<Segment> MemoryAllocator::addProcess(const QList<Segment> &process, AllocationType type)
{
    if(!process.size())
        throw QString("Empty process");

    int processId = process[0].processId();

    if(processIds.contains(processId))
        throw QString("Already Included Process Id");
    else
        processIds.insert(processId);

    QList<Segment> list;
    for(const Segment& seg: process) {
        if(seg.processId() != processId) {
            deleteProcess(processId);
            throw QString("Process Id doesn't match between segments");
        }
        if(seg.type() != SegmentType::PROCESS) {
            deleteProcess(processId);
            throw QString("Expected Process not Hole");
        }
        try {
            list.push_back(addSegment(seg, type));
        }  catch (...){
            deleteProcess(processId);
            throw QString("One or more segments doesn't fit im memory");
        }
    }

    return list;
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
