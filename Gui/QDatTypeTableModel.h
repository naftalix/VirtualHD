#ifndef QDATTYPETABLEMODEL_H
#define QDATTYPETABLEMODEL_H

#include <QAbstractTableModel>
#include "Disk.h"

class QDatTypeTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    QDatTypeTableModel(Fms::Disk &disk, QString fileName = QString(""), QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const;
    void changeSource(QString fileName);
    void refresh();

private:
    Fms::Disk &d;
    QString fileName;
    Fms::DatType bits;
signals:

public slots:

};

#endif // QDATTYPETABLEMODEL_H
