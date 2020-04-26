#include "QDirTableModel.h"

int QDirTableModel::rowCount(const QModelIndex &parent) const{
    if (parent != parent){}
    Fms::Dir dir;
    try{
        dir = disk.getDir();
    } catch (...){
        dir = Fms::Dir();
    }
    return dir.size();
}
int QDirTableModel::columnCount(const QModelIndex &parent) const{
    if (parent != parent){}
    return 15;
}
QVariant QDirTableModel::data(const QModelIndex &index, int role) const{
    Fms::Dir dir;

    if (!index.isValid())
        return QVariant();
    if (index.row() >= int(dir.size()))
        return QVariant();
    if (index.column() >= 15)
        return QVariant();

    // Get folder
    try{
        dir = disk.getDir();
    } catch (...){
        dir = Fms::Dir();
    }

    if (role == Qt::DisplayRole){
        switch (index.column()){
        case 0:
            return QString(dir[index.row()].fileName);
            break;
        case 1:
            return QString(dir[index.row()].fileOwner);
            break;
        case 2:
            return QString::number(dir[index.row()].fileAddr);
            break;
        case 3:
            return QString(Fms::convertDate(dir[index.row()].crDate).c_str());
            break;
        case 4:
        {
            // FAT is used here, so we need the file. We only grab it here to save read/write access
            size_t loc;
            Fms::FileHeader fileHeader;
            try{
                fileHeader = disk.findFile(std::string(dir[index.row()].fileName), loc);
            } catch (...){
                fileHeader = Fms::FileHeader();
            }
            return QString::number(fileHeader.FAT.count() * Fms::CLUSTERSIZE * Fms::SIZEOFSECTOR);
        }

            break;
        case 5:
            return QString::number(dir[index.row()].fileSize>0 ? dir[index.row()].fileSize : dir[index.row()].eofRecNr*dir[index.row()].maxRecSize);
        case 6:
            return QString::number(dir[index.row()].eofRecNr);
            break;
        case 7:
            return QString::number(dir[index.row()].maxRecSize);
            break;
        case 8:
            return QString::number(dir[index.row()].actualRecSize);
            break;
        case 9:
            return QString(dir[index.row()].recFormat);
            break;
        case 10:
            return QString::number(dir[index.row()].keyOffset);
            break;
        case 11:
            return QString::number(dir[index.row()].keySize);
            break;
        case 12:
            return QString(dir[index.row()].keyType);
            break;
        case 13:
            return QString::number(dir[index.row()].entryStatus);
            break;
        case 14:
            return QString::number(dir[index.row()].fileSize==0);
            break;
        }
    }
    return QVariant();
}

QVariant QDirTableModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
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
    else
        return tr("File %1").arg(section);
    return QVariant();
}
