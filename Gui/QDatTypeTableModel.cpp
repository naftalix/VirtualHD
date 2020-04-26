#include "QDatTypeTableModel.h"
#include "QBrush"
#include <cmath>

QDatTypeTableModel::QDatTypeTableModel(Fms::Disk &disk, QString fileName, QObject *parent)
    : QAbstractTableModel(parent), d(disk), fileName(fileName) {
    if (fileName.isEmpty()){
        bits.set();
    } else {
        bits.reset();
    }
}

int QDatTypeTableModel::rowCount(const QModelIndex &parent) const{
    if (parent != parent){} 
    return Fms::CLUSTERSINDISK / columnCount();
}

int QDatTypeTableModel::columnCount(const QModelIndex &parent) const{
    if (parent != parent){}
    //return 80;
    return Fms::ClusterId(std::sqrt(Fms::CLUSTERSINDISK));
}

QVariant QDatTypeTableModel::data(const QModelIndex &index, int role) const{

    if (!index.isValid())
        return QVariant();
    if (index.row() >= rowCount())
        return QVariant();
    if (index.column() >= columnCount())
        return QVariant();

    if (role == Qt::DisplayRole){
        return QString();
    }
    if (role == Qt::BackgroundRole){
		bool bit = bits[Fms::CLUSTERSINDISK - 1 - (index.row()*columnCount()+index.column())];
        if (bit && fileName.isEmpty() || !bit && !fileName.isEmpty()){ // Free
            return QBrush(Qt::green);
        } else {
            return QBrush(Qt::red);
        }
    }
    if (role == Qt::ToolTipRole){
        return QString::number(Fms::CLUSTERSINDISK - 1 - (index.row()*columnCount()+index.column()));
    }

    return QVariant();
}

QVariant QDatTypeTableModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (section == 0) { }
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return QVariant();
    else
        return QVariant();
    return QVariant();
}

void QDatTypeTableModel::changeSource(QString fileName){
    this->fileName = fileName;
    refresh();
}

void QDatTypeTableModel::refresh(){
    if (fileName.isEmpty()){ // DAT
        try{
            bits = d.getDat().dat;
        } catch (...){
            bits = Fms::DatType();
            bits.set();
        }
    } else { // FAT
        try{
            size_t tmp;
            bits = d.findFile(fileName.toStdString(), tmp).FAT;
        } catch (...){
            bits = Fms::DatType();
        }
    }
    emit dataChanged(this->index(0,0), this->index(this->rowCount(), this->columnCount()));
}
