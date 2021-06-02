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

void Controller::visualize()
{
    // TODO call m_allocator.memoryLayout()
}

quint32 Controller::stageNumber()
{
    return m_stage_number;
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

    // TODO Use segments here then call visualize(QList<Segment>)
    // Need the AllocationType;
    m_allocator.addProcess(segments, AllocationType::BEST_FIT);
    visualize();

}

void Controller::setup()
{
    m_stage_number = 1;
    emit stageNumberChanged();

    QList<Segment> holes = m_hole_model.getSegmentsList();

    // TODO Use holes here then call visualize(QList<Segment>)
    // Need memory size
    m_allocator = MemoryAllocator::makeFromHoles(holes, 200);
    visualize();
}

void Controller::compact()
{
    // Done
    m_allocator.compact();
    visualize();
}

void Controller::processDeleted(int id)
{
    // Done Use id here then call visualize(QList<Segment>)
    m_allocator.deleteProcess(id);
    visualize();
}
