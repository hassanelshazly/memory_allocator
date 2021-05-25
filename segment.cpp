#include "segment.h"

Segment::Segment()
{

}

Segment::Segment(int processId, QString name, int size, SegmentType type)
    : m_processId(processId), m_name(name), m_size(size), m_type(type)
{

}

Segment::Segment(int processId, QString name, int startingAddress, int size, SegmentType type)
    : m_processId(processId), m_name(name),  m_startingAddress(startingAddress),
      m_size(size), m_type(type)
{

}

int Segment::processId() const
{
    return m_processId;
}

void Segment::setProcessId(int processId)
{
    m_processId = processId;
}

int Segment::startingAddress() const
{
    return m_startingAddress;
}

void Segment::setStartingAddress(int startingAddress)
{
    m_startingAddress = startingAddress;
}

int Segment::endingAddress() const
{
    return m_startingAddress + m_size;
}

int Segment::size() const
{
    return m_size;
}

QString Segment::name() const
{
    return m_name;
}

void Segment::setName(const QString &name)
{
    m_name = name;
}

SegmentType Segment::type() const
{
    return m_type;
}

void Segment::setType(const SegmentType &type)
{
    m_type = type;
}

void Segment::setSize(int size)
{
    m_size = size;
}
