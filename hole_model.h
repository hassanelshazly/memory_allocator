#ifndef HOLE_MODEL_H
#define HOLE_MODEL_H

#include <QtQml/qqml.h>
#include <QtCore/QAbstractTableModel>

#include "segment.h"

class HoleModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)
public:
    explicit HoleModel(QObject *parent = 0);

    enum Role {
        IdRole = Qt::UserRole + 1,
        StartAddressRole,
        SizeRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Segment> m_data;
};

#endif // HOLE_MODEL_H
