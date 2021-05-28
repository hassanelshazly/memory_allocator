#include "hole_model.h"

HoleModel::HoleModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    for (int i = 0; i < 6; i++) {
        m_data.append(Segment(i, "Hole", i * 20, 10, HOLE));
    }
}

int HoleModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

int HoleModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant HoleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation)
    if (role != Qt::DisplayRole)
        return QVariant();

    switch (section) {
    case 0:
        return "Id";
    case 1:
        return "Starting Address";
    case 2:
        return "Size";
    }

    return QVariant();
}

QVariant HoleModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid())
        return QVariant();

    const Segment &segment = m_data[index.row()];

    switch (index.column()) {
    case 0:
        return segment.processId();
    case 1:
        return segment.startingAddress();
    case 2:
        return segment.size();
    }

    return QVariant();
}

bool HoleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || !index.isValid())
        return false;

    switch (index.column()) {
    case 0:
        m_data[index.row()].setProcessId(value.toInt());
        emit dataChanged(index, index);
        return true;
    case 1:
        m_data[index.row()].setStartingAddress(value.toInt());
        emit dataChanged(index, index);
        return true;
    case 2:
        m_data[index.row()].setSize(value.toInt());
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

Qt::ItemFlags HoleModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> HoleModel::roleNames() const {
    return { {Qt::DisplayRole, "display"}, {Qt::EditRole, "edit"} };
}
