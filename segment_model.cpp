#include "segment_model.h"

SegmentModel::SegmentModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_data.append(Segment(0, "Text", 5, PROCESS));
    m_data.append(Segment(0, "Heap", 15, PROCESS));
    m_data.append(Segment(0, "Stack", 10, PROCESS));
}

int SegmentModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

int SegmentModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant SegmentModel::headerData(int section, Qt::Orientation orientation, int role) const
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
        return "Delete";
    }

    return QVariant();
}

QVariant SegmentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const Segment &segment = m_data[index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0:
            return segment.name();
        case 1:
            return segment.size();
        case 2:
            return "Delete";
        }
    }

    switch (role) {
    case NameRole:
        return segment.name();
    case SizeRole:
        return segment.size();
    }

    return QVariant();
}

Qt::ItemFlags SegmentModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool SegmentModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || !index.isValid() || index.row() >= m_data.size())
        return false;

    switch (index.column()) {
    case 0:
        m_data[index.row()].setName(value.toString());
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

bool SegmentModel::insertRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent)

    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; row++)
        m_data.insert(position, Segment(0, "Enter Name", 0, PROCESS));
    endInsertRows();

    return true;
}

bool SegmentModel::removeRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent)

    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; row++)
        m_data.removeAt(position);
    endRemoveRows();

    return true;
}

void SegmentModel::addNewSegment() {
    int position = m_data.count();

    beginInsertRows(QModelIndex(), position, position);
    m_data.append(Segment(position, "Enter Name", 0, PROCESS));
    endInsertRows();
}

QList<Segment> SegmentModel::getSegmentsList() {
    return m_data;
}

QHash<int, QByteArray> SegmentModel::roleNames() const {
    return { {Qt::DisplayRole, "display"},
             {Qt::EditRole, "edit"},
             {NameRole, "name"},
             {SizeRole, "size"} };
}
