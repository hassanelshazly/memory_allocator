#include "process_model.h"

ProcessModel::ProcessModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_data.append(Segment(0, "Text", 5, PROCESS));
    m_data.append(Segment(0, "Heap", 15, PROCESS));
    m_data.append(Segment(0, "Stack", 10, PROCESS));
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
        return "Id";
    case 1:
        return "Name";
    case 2:
        return "Size";
    }

    return QVariant();
}

QVariant ProcessModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid())
        return QVariant();

    const Segment &segment = m_data[index.row()];

    switch (index.column()) {
    case 0:
        return segment.processId();
    case 1:
        return segment.name();
    case 2:
        return segment.size();
    }

    return QVariant();
}

bool ProcessModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || !index.isValid())
        return false;

    switch (index.column()) {
    case 0:
        m_data[index.row()].setProcessId(value.toInt());
        emit dataChanged(index, index);
        return true;
    case 1:
        m_data[index.row()].setName(value.toString());
        emit dataChanged(index, index);
        return true;
    case 2:
        m_data[index.row()].setSize(value.toInt());
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

Qt::ItemFlags ProcessModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> ProcessModel::roleNames() const {
    return { {Qt::DisplayRole, "display"}, {Qt::EditRole, "edit"} };
}
