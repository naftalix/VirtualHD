#include "QLocationArrayTableModel.h"

QLocationArrayTableModel::QLocationArrayTableModel(Fms::Disk &disk, QString fileName, QObject *parent)
	: QAbstractTableModel(parent), d(disk), fileName(fileName) 
{
	refresh();
}

QLocationArrayTableModel::~QLocationArrayTableModel()
{

}

void QLocationArrayTableModel::refresh(){
	beginResetModel();
	if (fileName.isEmpty()){
		cache = std::vector<std::pair<Fms::ClusterId, Fms::SectorId> >();
	} else {
		try{
			cache = d.locationsVectorOfFile(fileName.toStdString());
		} catch (...) {
			cache = std::vector<std::pair<Fms::ClusterId, Fms::SectorId> >();
		}
	}
	endResetModel();
	emit dataChanged(this->index(0,0), this->index(this->rowCount(), this->columnCount()));
}


int QLocationArrayTableModel::rowCount(const QModelIndex &parent) const{
	if (parent != parent){} 
	return cache.size();
}

int QLocationArrayTableModel::columnCount(const QModelIndex &parent) const{
	if (parent != parent){}
	return 2;
}


QVariant QLocationArrayTableModel::data(const QModelIndex &index, int role) const{

	if (!index.isValid())
		return QVariant();
	if (index.row() >= rowCount())
		return QVariant();
	if (index.column() >= columnCount())
		return QVariant();

	if (role == Qt::DisplayRole){
		try{
			switch (index.column())
			{
			case 0:
				return QString::number(cache[index.row()].first);
			case 1:
				return QString::number(cache[index.row()].second);
			default:
				break;
			}
		} catch (...){
			return QVariant();
		}
	}
	return QVariant();
}


QVariant QLocationArrayTableModel::headerData(int section, Qt::Orientation orientation, int role) const{
	if (role != Qt::DisplayRole)
		return QVariant();
	if (orientation == Qt::Horizontal){
		switch (section)
		{
		case 0:
			return tr("Cluster Number");
		case 1:
			return tr("Amount");
		default:
			break;
		}
	} else if (orientation == Qt::Vertical){
		return QString::number(section+1);
	}
	return QVariant();
}


void QLocationArrayTableModel::changeSource(QString fileName){
	this->fileName = fileName;
	refresh();
}


