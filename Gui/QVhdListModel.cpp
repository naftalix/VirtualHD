#include "QVhdListModel.h"

QVhdListModel::QVhdListModel(Fms::Disk &disk, QObject *parent)
    : QAbstractListModel(parent), d(disk){ }

int QVhdListModel::rowCount(const QModelIndex &parent) const{
    if (parent != parent){}
    return 12;
}

QVariant QVhdListModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= 12)
        return QVariant();
    if (role == Qt::DisplayRole){
        Fms::VolumeHeader vhd;
        try{
            vhd = d.getVolumeHeader();
        } catch (...) {
            vhd = Fms::VolumeHeader();
        }
        switch (index.row()){
        case 0:
            return QString(vhd.diskName);
            break;
        case 1:
            return QString(vhd.diskOwner);
            break;
        case 2:
            return QString(Fms::convertDate(vhd.prodDate).c_str());
            break;
        case 3:
            return QString::number(vhd.clusQty);
            break;
        case 4:
            return QString::number(vhd.dataClusQty);
            break;
        case 5:
            return QString::number(vhd.addrDat);
        case 6:
            return QString::number(vhd.addrRootDir);
            break;
        case 7:
            return QString::number(vhd.addrDatCpy);
            break;
        case 8:
            return QString::number(vhd.addrRootDirCpy);
            break;
        case 9:
            return QString::number(vhd.addrDataStart);
            break;
        case 10:
            return QString(Fms::convertDate(vhd.formatDate).c_str());
            break;
        case 11:
            return QString::number(vhd.isFormated);
            break;
        }
        return QVariant();
    }
    else
        return QVariant();
}
QVariant QVhdListModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return tr("Property");
    else
        switch (section){
        case 0:
            return tr("Disk name");
            break;
        case 1:
            return tr("Owner name");
            break;
        case 2:
            return tr("Production Date");
            break;
        case 3:
            return tr("Cluster in disk");
            break;
        case 4:
            return tr("Clusters for data");
            break;
        case 5:
            return tr("Sector of Dat");
            break;
        case 6:
            return tr("Cluster of Root dir");
            break;
        case 7:
            return tr("Sector of Dat copy");
            break;
        case 8:
            return tr("Cluster of Root dir copy");
            break;
        case 9:
            return tr("First cluster for data");
            break;
        case 10:
            return tr("Format date");
            break;
        case 11:
            return tr("Is formatted:");
            break;
        }
    return QVariant();
}
