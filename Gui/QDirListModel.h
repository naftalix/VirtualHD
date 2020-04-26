#ifndef QDIRLISTMODEL_H
#define QDIRLISTMODEL_H

#include <QAbstractListModel>
#include "Disk.h"

class QDirListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    QDirListModel(Fms::Disk &disk, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

signals:

public slots:

private:
    Fms::Disk &disk;
};

#endif // QDIRLISTMODEL_H
