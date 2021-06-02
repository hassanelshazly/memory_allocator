#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject(parent)
{
    QObject::connect(&m_process_model, SIGNAL(processDeleted(int)),
                     this, SLOT(processDeleted(int)));
}

HoleModel *Controller::holeModel()
{
    return &m_hole_model;
}

SegmentModel *Controller::segmentModel()
{
    return &m_segment_model;
}

ProcessModel *Controller::processModel()
{
    return &m_process_model;
}

TimelineModel *Controller::timelineModel()
{
    return &m_timeline_model;
}

quint32 Controller::stageNumber()
{
    return m_stage_number;
}

quint32 Controller::memorySize()
{
    return m_memory_size;
}

void Controller::setMemorySize(quint32 new_size)
{
    m_memory_size = new_size;
    emit memorySizeChanged(new_size);
}

AllocationType Controller::allocationType()
{
    return m_allocation_type;
}

void Controller::setAllocationType(quint32 new_allocation_type)
{
    AllocationType allocation_type = static_cast<AllocationType>(new_allocation_type);
    m_allocation_type = allocation_type;
    emit allocationTypeChanged(allocation_type);
}

void Controller::visualize()
{
    QList<Segment> segments = m_allocator.memoryLayout();

    m_timeline_model.clearSegments();
    m_timeline_model.addSegments(segments);
}

void Controller::addNewHole()
{
    m_hole_model.addNewHole();
}

void Controller::addNewSegment()
{
    m_segment_model.addNewSegment();
}

void Controller::addNewProcess()
{
    int id = m_process_model.addNewProcess();

    QList<Segment> segments = m_segment_model.getSegmentsList();
    for (auto &segment: segments)
        segment.setProcessId(id);
    m_segment_model.removeRows(0, m_segment_model.rowCount());

    try {
        m_allocator.addProcess(segments, m_allocation_type);
    } catch (...) {
        qDebug() << "No space.";
    }

    visualize();
}

void Controller::setup()
{
    m_stage_number = 1;
    emit stageNumberChanged();

    QList<Segment> holes = m_hole_model.getSegmentsList();

    m_allocator = MemoryAllocator::makeFromHoles(holes, m_memory_size);
    visualize();
}

void Controller::compact()
{
    m_allocator.compact();
    visualize();
}

void Controller::processDeleted(int id)
{
    m_allocator.deleteProcess(id);
    visualize();
}
