#ifndef MEMORYALLOCATOR_H
#define MEMORYALLOCATOR_H

#include <QList>

#include "segment.h"

enum AllocationType {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
};

class MemoryAllocator
{
public:
    MemoryAllocator();
    static MemoryAllocator makeFromHoles(const QList<Segment>& holes);

    QList<Segment> addProcess(const QList<Segment>& process, AllocationType type);
    void deleteProcess(int processId);
    Segment addSegment(const Segment& seg, AllocationType type);

    QList<Segment> getHoles();
private:
    int m_maxSize;
    QList<Segment> m_segments;
    QList<Segment> m_holes;

    static constexpr auto comp_address_func = [](const Segment &seg1, const Segment &seg2) {
        return seg1.startingAddress() < seg2.startingAddress();
    };
    static constexpr auto comp_size_func = [](const Segment &seg1, const Segment &seg2) {
        return seg1.size() < seg2.size();
    };
};

#endif // MEMORYALLOCATOR_H
