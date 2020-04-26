#include "QDirListModel.h"
#include "QIcon"

QDirListModel::QDirListModel(Fms::Disk &disk, QObject *parent)
    : QAbstractListModel(parent), disk(disk) {

}

int QDirListModel::rowCount(const QModelIndex &parent) const{
    if (parent != parent){}
    Fms::Dir d;
    return int(d.size());
}

QVariant QDirListModel::data(const QModelIndex &index, int role) const{
    Fms::Dir dir;
    try{
        dir = disk.getDir();
    } catch (...){
        dir = Fms::Dir();
    }

    if (!index.isValid())
        return QVariant();
    if (index.row() >= int(dir.size()))
        return QVariant();
    if (role == Qt::DisplayRole){
        if (dir[index.row()].entryStatus != 1) return QString("");
        return QString(dir[index.row()].fileName);
    }
    if (role == Qt::DecorationRole){

		QPixmap imagedisplay(":/images/binary2.png");
		return imagedisplay;
    }
    return QVariant();
}
QVariant QDirListModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return tr("File name");
    else
        return tr("File %1").arg(section);
}
