#ifndef QSTUDENTRECORDLISTMODEL_H
#define QSTUDENTRECORDLISTMODEL_H

#include <QAbstractListModel>
#include "Fcb.h"
#include "Student.h"

class QStudentRecordListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    QStudentRecordListModel(Fms::Fcb &fcb, Fms::Fcb::OpenMode mode, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const ;

signals:

public slots:
    void moveNext();
    void movePrev();
    void write();
    void seek(uint32_t, uint32_t);
    void deleteRecord();

private:
    Fms::Fcb &fcb;
    FmsUtils::StudentRecord record;
    Fms::Fcb::OpenMode mode;

    void read();
};

#endif // QSTUDENTRECORDLISTMODEL_H
