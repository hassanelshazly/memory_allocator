#include "controller.h"

#include <algorithm>
#include <iterator>

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

void Controller::setStageNumber(quint32 new_stage_number)
{
    m_stage_number = new_stage_number;
    emit stageNumberChanged(new_stage_number);
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

QString Controller::status()
{
    return m_status;
}

void Controller::setStatus(QString new_status)
{
    m_status = new_status;
    emit statusChanged(new_status);
}

void Controller::visualize()
{
    QList<Segment> segments = m_allocator.memoryLayout();
    QList<Segment> processes_segments;

    std::copy_if(segments.begin(), segments.end(), std::back_inserter(processes_segments), [](Segment segment) {
        return segment.type() == PROCESS;
    });

    m_timeline_model.clearSegments();
    m_timeline_model.addSegments(segments);

    m_process_model.clearSegments();
    m_process_model.updateSegments(processes_segments);

    setStatus("Status: OK");
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
    QList<Segment> segments = m_segment_model.getSegmentsList();

    try {
        m_allocator.addProcess(segments, m_allocation_type);
        visualize();

        m_segment_model.removeRows(0, m_segment_model.rowCount());
    } catch (const QString &e) {
        setStatus(e);
    }
}

void Controller::setup()
{
    QList<Segment> holes = m_hole_model.getSegmentsList();

    try {
        m_allocator = MemoryAllocator::makeFromHoles(holes, m_memory_size);
        visualize();

        setStageNumber(1);
    }  catch (const QString &e) {
        setStatus(e);
    }
}

void Controller::compact()
{
    try {
        m_allocator.compact();
        visualize();
    }  catch (const QString &e) {
        setStatus(e);
    }
}

void Controller::processDeleted(int id)
{
    try {
        m_allocator.deleteProcess(id);
        visualize();
    }  catch (const QString &e) {
        setStatus(e);
    }
}
