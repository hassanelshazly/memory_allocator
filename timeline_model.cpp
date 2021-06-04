#include "timeline_model.h"

#define EPSILON 0.01

TimelineModel::TimelineModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int TimelineModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

QVariant TimelineModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Vertical)
        return QVariant();

    const Segment &segment = m_data[section];

    if (segment.type() == HOLE)
        return "Hole";
    else
        return QStringLiteral("P%1 %2").arg(segment.processId()).arg(segment.name());
}

QVariant TimelineModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const Segment &segment = m_data[index.row()];

    if (role == Qt::DisplayRole) {
        return segment.size();
//        return QVariant::fromValue(segment.name());
    }

    return QVariant();
}

void TimelineModel::addSegments(const QList<Segment> &segments)
{
    if (segments.isEmpty())
        return;

    beginInsertRows(QModelIndex(), rowCount(), rowCount() + segments.size() - 1);
    for (const Segment &segment: segments) {
        m_data.append(segment);
    }
    endInsertRows();
}

void TimelineModel::clearSegments()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}
