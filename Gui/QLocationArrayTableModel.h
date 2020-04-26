#ifndef QLOCATIONARRAYTABLEMODEL_H
#define QLOCATIONARRAYTABLEMODEL_H

#include <QAbstractTableModel>
#include "Disk.h"

class QLocationArrayTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	QLocationArrayTableModel(Fms::Disk &disk, QString fileName = QString("") , QObject *parent = 0);
	~QLocationArrayTableModel();

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
	std::vector<std::pair<Fms::ClusterId, Fms::SectorId> > cache;
	
};

#endif // QLOCATIONARRAYTABLEMODEL_H
