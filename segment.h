#ifndef SEGMENT_H
#define SEGMENT_H

#include <QString>

enum SegmentType {
    PROCESS,
    HOLE
};

class Segment
{
public:
    Segment();

    int processId() const;
    void setProcessId(int processId);

    int startingAddress() const;
    void setStartingAddress(int startingAddress);

    int size() const;

    QString name() const;
    void setName(const QString &name);

    SegmentType type() const;
    void setType(const SegmentType &type);

private:
    int m_processId;
    int m_startingAddress;
    int m_size;
    QString m_name;
    SegmentType m_type;
};

#endif // SEGMENT_H
