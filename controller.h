#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "hole_model.h"
#include "process_model.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    HoleModel *holeModel();
    ProcessModel *processModel();
public slots:
    void addNewHole();
    void addNewProcess();
    void compact();
    void visualize();
private:
    HoleModel m_hole_model;
    ProcessModel m_process_model;
};

#endif // CONTROLLER_H
