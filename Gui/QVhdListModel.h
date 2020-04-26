#ifndef QVHDLISTMODEL_H
#define QVHDLISTMODEL_H

#include <QAbstractListModel>
#include "Disk.h"

class QVhdListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    QVhdListModel(Fms::Disk &disk, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

signals:

public slots:

private:
    Fms::Disk &d;
};

#endif // QVHDLISTMODEL_H
