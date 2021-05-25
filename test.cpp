#include "segment.h"
#include "memory_allocator.h"


void testSegment() {
    Segment seg(0,
                "Data",
                2,
                4,
                SegmentType::PROCESS);

    Segment hole(-1,
                "Don't care",
                6,
                4,
                SegmentType::HOLE);
    qDebug() << seg << "\n" << hole << "\n";
}


void testAllocator() {
    Segment hole1(-1,
                "Don't care",
                5,
                10,
                SegmentType::HOLE);
    Segment hole2(-1,
                "Don't care",
                50,
                20,
                SegmentType::HOLE);
    Segment hole3(-1,
                "Don't care",
                30,
                10,
                SegmentType::HOLE);

    MemoryAllocator allocator = MemoryAllocator::makeFromHoles({hole1, hole2, hole3}, 100);
    qDebug() << allocator;

    allocator.compact();
    qDebug() << "After Compact\n" << allocator;

    allocator.deleteProcess(0);
    qDebug() << "After Deleting 0\n" << allocator;

    allocator.deleteProcess(1);
    qDebug() << "After Deleting 1\n" << allocator;
}
