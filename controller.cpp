#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject(parent)
{
}

HoleModel *Controller::holeModel()
{
    return &m_hole_model;
}

ProcessModel *Controller::processModel()
{
    return &m_process_model;
}

void Controller::addNewHole()
{
    m_hole_model.addNewHole();
}

void Controller::addNewProcess()
{
    m_process_model.addNewProcess();
}

void Controller::compact()
{

}

void Controller::visualize()
{

}
