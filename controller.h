#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "hole_model.h"
#include "segment_model.h"
#include "process_model.h"
#include "timeline_model.h"
#include "memory_allocator.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(HoleModel *holeModel READ holeModel)
    Q_PROPERTY(SegmentModel *segmentModel READ segmentModel)
    Q_PROPERTY(ProcessModel *processModel READ processModel)
    Q_PROPERTY(TimelineModel *timelineModel READ timelineModel)
    Q_PROPERTY(quint32 stageNumber READ stageNumber WRITE setStageNumber NOTIFY stageNumberChanged)
    Q_PROPERTY(quint32 memorySize READ memorySize WRITE setMemorySize NOTIFY memorySizeChanged)
    Q_PROPERTY(quint32 allocationType READ allocationType WRITE setAllocationType NOTIFY allocationTypeChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
public:
    explicit Controller(QObject *parent = nullptr);

    HoleModel *holeModel();
    SegmentModel *segmentModel();
    ProcessModel *processModel();
    TimelineModel *timelineModel();

    quint32 stageNumber();
    void setStageNumber(quint32 new_stage_number);

    quint32 memorySize();
    void setMemorySize(quint32 new_size);

    AllocationType allocationType();
    void setAllocationType(quint32 new_allocation_type);

    QString status();
    void setStatus(QString new_status);

    void visualize();

public slots:
    void addNewHole();
    void addNewSegment();
    void addNewProcess();

    void setup();
    void compact();

    void processDeleted(int id);

signals:
    void stageNumberChanged(quint32);
    void memorySizeChanged(quint32);
    void allocationTypeChanged(AllocationType);
    void statusChanged(QString);

private:
    HoleModel m_hole_model;
    SegmentModel m_segment_model;
    ProcessModel m_process_model;
    TimelineModel m_timeline_model;

    quint32 m_stage_number = 0;
    quint32 m_memory_size = 200;
    AllocationType m_allocation_type = WORST_FIT;
    QString m_status = "Status: OK";

    MemoryAllocator m_allocator;
};

#endif // CONTROLLER_H
