#include "process_model.h"

#include "segment.h"

int ProcessModel::currentId = 0;

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
    return 2;
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
        return "Delete";
    }

    return QVariant();
}

QVariant ProcessModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const int &process = m_data[index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0:
            return QStringLiteral("P%1").arg(process);
        case 1:
            return "Delete";
        }
    }

    switch (role) {
    case NameRole:
        return QStringLiteral("P%1").arg(process);
    }

    return QVariant();
}

Qt::ItemFlags ProcessModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    if (index.column() != 1)
        return QAbstractItemModel::flags(index);

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool ProcessModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(value)

    if (role != Qt::EditRole || !index.isValid())
        return false;

    const int &process = m_data[index.row()];

    switch (index.column()) {
    case 1:
        bool status = removeRow(index.row(), index);
        if (status)
            emit processDeleted(process);
        return status;
    }

    return false;
}

bool ProcessModel::insertRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent)

    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; row++)
        m_data.insert(position, ProcessModel::currentId++);
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

int ProcessModel::addNewProcess() {
    int position = m_data.count();
    int id = ProcessModel::currentId++;

    beginInsertRows(QModelIndex(), position, position);
    m_data.append(id);
    endInsertRows();

    return id;
}

QHash<int, QByteArray> ProcessModel::roleNames() const {
    return { {Qt::DisplayRole, "display"},
             {Qt::EditRole, "edit"},
             {NameRole, "name"} };
}
