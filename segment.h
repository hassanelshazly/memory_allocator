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

    Segment(int processId,
            QString name,
            int size,
            SegmentType type);

    Segment(int processId,
            QString name,
            int startingAddress,
            int size,
            SegmentType type);

    int processId() const;
    void setProcessId(int processId);

    int startingAddress() const;
    void setStartingAddress(int startingAddress);

    int size() const;
    void setSize(int size);

    QString name() const;
    void setName(const QString &name);

    SegmentType type() const;
    void setType(const SegmentType &type);

private:
    int m_processId;
    QString m_name;
    int m_startingAddress;
    int m_size;
    SegmentType m_type;
};

#endif // SEGMENT_H
