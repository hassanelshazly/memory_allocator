#include "process_model.h"

#include <algorithm>

#include "segment.h"

ProcessModel::ProcessModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int ProcessModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

int ProcessModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant ProcessModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation)
    if (role != Qt::DisplayRole)
        return QVariant();

    switch (section) {
    case 0:
        return "Name";
    case 1:
        return "Size";
    case 2:
        return "Action";
    }

    return QVariant();
}

QVariant ProcessModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const Segment &segment = m_data[index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0:
            return QStringLiteral("P%1 %2").arg(segment.processId()).arg(segment.name());
        case 1:
            return segment.size();
        case 2:
            return "Delete Process";
        }
    }

    switch (role) {
    case NameRole:
        return QStringLiteral("P%1 %2").arg(segment.processId()).arg(segment.name());
    case SizeRole:
        return segment.size();
    }

    return QVariant();
}

Qt::ItemFlags ProcessModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    if (index.column() != 2)
        return QAbstractItemModel::flags(index);

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool ProcessModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(value)

    if (role != Qt::EditRole || !index.isValid())
        return false;

    const Segment &segment = m_data[index.row()];

    switch (index.column()) {
    case 2:
        bool status = true;
        for (int i = m_data.size() - 1; i >= 0; i--)
            if (m_data[i].processId() == segment.processId())
                status &= removeRow(i, index);
        if (status)
            emit processDeleted(segment.processId());
        return status;
    }

    return false;
}

bool ProcessModel::insertRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent)

    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; row++)
        m_data.insert(position, Segment(ProcessModel::currentId++, "Enter Name", 0, PROCESS));
    endInsertRows();

    return true;
}

bool ProcessModel::removeRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent)

    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; row++)
        m_data.removeAt(position);
    endRemoveRows();

    return true;
}

int ProcessModel::addNewProcess(QList<Segment> segments) {
    int position = m_data.count();
    int id = currentId++;

    for (auto &segment: segments)
        segment.setProcessId(id);

    beginInsertRows(QModelIndex(), position, position + segments.size() - 1);
    m_data.append(segments);
    endInsertRows();

    return id;
}

int ProcessModel::id() const
{
    return currentId;
}

void ProcessModel::setId(int id)
{
    currentId = id;
}

QHash<int, QByteArray> ProcessModel::roleNames() const {
    return { {Qt::DisplayRole, "display"},
             {Qt::EditRole, "edit"},
             {NameRole, "name"},
             {SizeRole, "size"}};
}
