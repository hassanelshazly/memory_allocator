#ifndef PROCESS_MODEL_H
#define PROCESS_MODEL_H

#include <QtQml/qqml.h>
#include <QtCore/QAbstractTableModel>

#include "segment.h"

class ProcessModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ProcessModel(QObject *parent = 0);

    enum Role {
        NameRole = Qt::UserRole + 1,
        SizeRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    int addNewProcess(QList<Segment> segments);

    int id() const;
    void setId(int id);

signals:
    void processDeleted(int id);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Segment> m_data;

    int currentId;
};

#endif // PROCESS_MODEL_H
