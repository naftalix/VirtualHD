#include "QFileListModel.h"
#include "Sector.h"

QFileListModel::QFileListModel(Fms::Disk &disk, std::string fileName, QObject *parent)
    : QAbstractListModel(parent), disk(disk), fileName(fileName) { }

int QFileListModel::rowCount(const QModelIndex &parent) const{
    if (parent != parent){}
    return 15;
}

QVariant QFileListModel::data(const QModelIndex &index, int role) const{
    size_t loc;
    Fms::FileHeader fileHeader;
    try{
        fileHeader = disk.findFile(fileName, loc);
    } catch (...){
        fileHeader = Fms::FileHeader();
    }

    if (!index.isValid())
        return QVariant();
    if (index.row() >= 15)
        return QVariant();
    if (role == Qt::DisplayRole){
        if (fileHeader.fileDesc.entryStatus != 1) return QString("");
        switch (index.row()){
        case 0:
            return QString(fileHeader.fileDesc.fileName);
            break;
        case 1:
            return QString(fileHeader.fileDesc.fileOwner);
            break;
        case 2:
            return QString::number(fileHeader.fileDesc.fileAddr);
            break;
        case 3:
            return QString(Fms::convertDate(fileHeader.fileDesc.crDate).c_str());
            break;
        case 4:
            return QString::number(fileHeader.FAT.count() * Fms::CLUSTERSIZE * Fms::SIZEOFSECTOR);
            break;
        case 5:
            return QString::number(fileHeader.fileDesc.fileSize>0 ? fileHeader.fileDesc.fileSize : fileHeader.fileDesc.eofRecNr*fileHeader.fileDesc.maxRecSize);
        case 6:
            return QString::number(fileHeader.fileDesc.eofRecNr);
            break;
        case 7:
            return QString::number(fileHeader.fileDesc.maxRecSize);
            break;
        case 8:
            return QString::number(fileHeader.fileDesc.actualRecSize);
            break;
        case 9:
            return QString(fileHeader.fileDesc.recFormat);
            break;
        case 10:
            return QString::number(fileHeader.fileDesc.keyOffset);
            break;
        case 11:
            return QString::number(fileHeader.fileDesc.keySize);
            break;
        case 12:
            return QString(fileHeader.fileDesc.keyType);
            break;
        case 13:
            return QString::number(fileHeader.fileDesc.entryStatus);
            break;
        case 14:
            return QString::number(fileHeader.fileDesc.fileSize==0);
            break;
        }
        return QVariant();
    }
    else
        return QVariant();
}

QVariant QFileListModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return tr("Property");
    else
        switch (section){
        case 0:
            return tr("File name");
            break;
        case 1:
            return tr("Owner name");
            break;
        case 2:
            return tr("File address");
            break;
        case 3:
            return tr("Creation Date");
            break;
        case 4:
            return tr("File size (Bytes)");
            break;
        case 5:
            return tr("Real size (Bytes)");
            break;
        case 6:
            return tr("Amount of records");
            break;
        case 7:
            return tr("Max record size");
            break;
        case 8:
            return tr("Acctual record size");
            break;
        case 9:
            return tr("Record Format");
            break;
        case 10:
            return tr("Key offset");
            break;
        case 11:
            return tr("Key size");
            break;
        case 12:
            return tr("Key Type");
            break;
        case 13:
            return tr("Entry status");
            break;
        case 14:
            return tr("Student?");
            break;
        }
    return QVariant();
}

void QFileListModel::changeSource(std::string fileName){
    this->fileName = fileName;
    emit dataChanged(this->index(0), this->index(this->rowCount()));
}
