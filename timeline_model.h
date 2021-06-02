#ifndef TIMELINE_MODEL_H
#define TIMELINE_MODEL_H

#include <QAbstractListModel>
#include <QList>

#include "segment.h"

class TimelineModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimelineModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addSegments(const QList<Segment> &segments);
    void clearSegments(void);

private:
    QList<Segment> m_data;
};

#endif // TIMELINE_MODEL_H
