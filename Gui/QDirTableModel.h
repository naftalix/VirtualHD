#ifndef QDIRTABLEMODEL_H
#define QDIRTABLEMODEL_H

#include <QAbstractTableModel>
#include "Disk.h"

class QDirTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    QDirTableModel(Fms::Disk &disk, QObject *parent = 0)
        : QAbstractTableModel(parent), disk(disk) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const;

private:
    Fms::Disk &disk;

signals:

public slots:

};

#endif // QDIRTABLEMODEL_H
