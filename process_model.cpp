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
    return 5;
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
    case 3:
        return "Add";
    case 4:
        return "Delete";
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
            return segment.processId();
        case 1:
            return segment.name();
        case 2:
            return segment.size();
        case 3:
            return "Add";
        case 4:
            return "Delete";
        }
    }

    switch (role) {
    case IdRole:
        return segment.processId();
    case NameRole:
        return segment.name();
    case SizeRole:
        return segment.size();
    }

    return QVariant();
}

Qt::ItemFlags ProcessModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool ProcessModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || !index.isValid())
        return false;

    Segment &segment = m_data[index.row()];

    switch (index.column()) {
    case 0:
        segment.setProcessId(value.toInt());
        emit dataChanged(index, index);
        return true;
    case 1:
        segment.setName(value.toString());
        emit dataChanged(index, index);
        return true;
    case 2:
        segment.setSize(value.toInt());
        emit dataChanged(index, index);
        return true;
    case 3:
        beginInsertRows(QModelIndex(), index.row() + 1, index.row() + 1);
        m_data.insert(index.row() + 1, Segment(segment.processId(), "Enter Name", 0, PROCESS));
        endInsertRows();
        return true;
    case 4:
        return removeRow(index.row(), index);
    }

    return false;
}

bool ProcessModel::insertRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent)

    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; row++)
        m_data.insert(position, Segment(0, "Text", 5, PROCESS));
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

void ProcessModel::addNewProcess() {
    int position = m_data.count();

    beginInsertRows(QModelIndex(), position, position);
    m_data.append(Segment(position, "Enter Name", 0, PROCESS));
    endInsertRows();
}

QHash<int, QByteArray> ProcessModel::roleNames() const {
    return { {Qt::DisplayRole, "display"},
             {Qt::EditRole, "edit"},
             {IdRole, "id"},
             {NameRole, "name"},
             {SizeRole, "size"} };
}
