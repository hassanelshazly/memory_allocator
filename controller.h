#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "hole_model.h"
#include "segment_model.h"
#include "process_model.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(HoleModel *holeModel READ holeModel)
    Q_PROPERTY(SegmentModel *segmentModel READ segmentModel)
    Q_PROPERTY(ProcessModel *processModel READ processModel)
    Q_PROPERTY(quint32 stageNumber READ stageNumber NOTIFY stageNumberChanged)
public:
    explicit Controller(QObject *parent = nullptr);

    HoleModel *holeModel();
    SegmentModel *segmentModel();
    ProcessModel *processModel();

    quint32 stageNumber();

public slots:
    void addNewHole();
    void addNewSegment();
    void addNewProcess();

    void setup();
    void compact();

    void processDeleted(int id);

signals:
    void stageNumberChanged();

private:
    HoleModel m_hole_model;
    SegmentModel m_segment_model;
    ProcessModel m_process_model;

    quint32 m_stage_number = 0;
};

#endif // CONTROLLER_H
