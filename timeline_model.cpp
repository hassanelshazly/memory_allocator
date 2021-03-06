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
    }

    switch (role) {
    case IdRole:
        return segment.processId();
    case NameRole:
        return segment.name();
    case StartAddressRole:
        return segment.startingAddress();
    case SizeRole:
        return segment.size();
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

Q_INVOKABLE QVariant TimelineModel::ids() const
{
    QList<qint32> ids;
    for (const auto &segment: m_data)
        ids.append(segment.processId());
    return QVariant::fromValue(ids);
}

QHash<int, QByteArray> TimelineModel::roleNames() const {
    return { {Qt::DisplayRole, "display"},
             {Qt::EditRole, "edit"},
             {IdRole, "id"},
             {NameRole, "name"},
             {StartAddressRole, "start_address"},
             {SizeRole, "size"} };
}
