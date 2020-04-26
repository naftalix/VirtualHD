#ifndef QFILELISTMODEL_H
#define QFILELISTMODEL_H

#include <QAbstractListModel>
#include "Disk.h"

class QFileListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    QFileListModel(Fms::Disk &disk, std::string fileName, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void changeSource(std::string fileName);
signals:

public slots:

private:
    Fms::Disk &disk;
    std::string fileName;
};

#endif // QFILELISTMODEL_H
