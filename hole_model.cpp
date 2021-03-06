#include "hole_model.h"

HoleModel::HoleModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_data.append(Segment(-1, "Hole", 20, 180, HOLE));
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
        return "Start Address";
    case 1:
        return "Size";
    case 2:
        return "Delete";
    }

    return QVariant();
}

QVariant HoleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const Segment &segment = m_data[index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0:
            return segment.startingAddress();
        case 1:
            return segment.size();
        case 2:
            return "Delete";
        }
    }

    switch (role) {
    case StartAddressRole:
        return segment.startingAddress();
    case SizeRole:
        return segment.size();
    }

    return QVariant();
}

Qt::ItemFlags HoleModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool HoleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || !index.isValid() || index.row() >= m_data.size())
        return false;

    switch (index.column()) {
    case 0:
        m_data[index.row()].setStartingAddress(value.toInt());
        emit dataChanged(index, index);
        return true;
    case 1:
        m_data[index.row()].setSize(value.toInt());
        emit dataChanged(index, index);
        return true;
    case 2:
        return removeRow(index.row(), index);
    }

    return false;
}

bool HoleModel::insertRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent)

    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; row++)
        m_data.insert(position, Segment(-1, "Hole", 0, 0, HOLE));
    endInsertRows();

    return true;
}

bool HoleModel::removeRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent)

    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; row++)
        m_data.removeAt(position);
    endRemoveRows();

    return true;
}

void HoleModel::addNewHole() {
    int position = m_data.count();

    beginInsertRows(QModelIndex(), position, position);
    m_data.append(Segment(-1, "Hole", 0, 0, HOLE));
    endInsertRows();
}

QList<Segment> HoleModel::getSegmentsList() {
    return m_data;
}

QHash<int, QByteArray> HoleModel::roleNames() const {
    return { {Qt::DisplayRole, "display"},
             {Qt::EditRole, "edit"},
             {StartAddressRole, "start_address"},
             {SizeRole, "size"} };
}
