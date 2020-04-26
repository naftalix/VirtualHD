#include "QStudentRecordListModel.h"
#include <QDebug>
#include <sstream>

QStudentRecordListModel::QStudentRecordListModel(Fms::Fcb &fcb, Fms::Fcb::OpenMode mode, QObject *parent)
    : QAbstractListModel(parent), fcb(fcb), mode(mode) {
    read();
    emit dataChanged(this->index(0), this->index(this->rowCount()));
}

int QStudentRecordListModel::rowCount(const QModelIndex &parent) const{
    if (parent != parent){}
    return 5;
}

QVariant QStudentRecordListModel::data(const QModelIndex &index, int role) const{
    Fms::Dir dir;
    try{
        dir = fcb.d->getDir();
    } catch (...){
        dir = Fms::Dir();
    }

    if (!index.isValid())
        return QVariant();
    if (index.row() >= 4)
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        switch (index.row()){
        case 0:
            return QString::number(record.student.id);
            break;
        case 1:
            return QString(record.student.name);
            break;
        case 2:
            return QString(record.student.address);
            break;
        case 3:
            return QString::number(record.student.average);
            break;
        case 4:
            return QString::number(static_cast<int>(mode));
        }
        return QVariant();
    }
    else
        return QVariant();
}

QVariant QStudentRecordListModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return tr("Property");
    else
        switch (section){
        case 0:
            return tr("Id");
            break;
        case 1:
            return tr("Name");
            break;
        case 2:
            return tr("Address");
            break;
        case 3:
            return tr("Average");
            break;
        case 4:
            return tr("Open mode");
        }
    return QVariant();
}

bool QStudentRecordListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        std::string str = value.toString().toStdString();
        switch (index.row()){
        case 0:
            record.student.id = value.toString().toInt();
            break;
        case 1:
            strncpy(record.student.name,str.c_str(),sizeof(record.student.name));
            record.student.name[sizeof(record.student.name)-1] = '\0';
            break;
        case 2:
            strncpy(record.student.address,str.c_str(),sizeof(record.student.address));
            record.student.address[sizeof(record.student.address)-1] = '\0';
            break;
        case 3:
            record.student.average = value.toString().toInt();
            break;
        case 4:
            // Not avilable
            break;
        }
    }
    return true;
}

Qt::ItemFlags QStudentRecordListModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

void QStudentRecordListModel::moveNext()
{
    if (mode == Fms::Fcb::OpenMode::IO){
        try{
            fcb.updateCancel();
        } catch (...) { }
        fcb.seek(1,1);
    }
    read();
    emit dataChanged(this->index(0), this->index(this->rowCount()));
}

void QStudentRecordListModel::movePrev()
{
    if (mode == Fms::Fcb::OpenMode::IO){
        try{
            fcb.updateCancel();
        } catch (...) { }
        try{
            fcb.seek(1,-1);
        } catch (std::exception e){
            fcb.seek(0,0);
            read();
            throw e;
        }
        memcpy(reinterpret_cast<char*>(&record),fcb.read(1).get(),sizeof(FmsUtils::StudentRecord));
        if (record.key == -1) movePrev();

    } else if (mode == Fms::Fcb::OpenMode::I){
        fcb.seek(1,-2);
        memcpy(reinterpret_cast<char*>(&record),fcb.read(0).get(),sizeof(FmsUtils::StudentRecord));
        if (record.key == -1) movePrev();
    } else if (mode == Fms::Fcb::OpenMode::O){
        fcb.seek(1,-1);
        record = FmsUtils::StudentRecord();
    }
    emit dataChanged(this->index(0), this->index(this->rowCount()));
}

void QStudentRecordListModel::write()
{
    if (fcb.eof()){
        fcb.write(reinterpret_cast<char*>(&record));
    } else {
        fcb.update(reinterpret_cast<char*>(&record));
    }
    read();
    emit dataChanged(this->index(0), this->index(this->rowCount()));
}

void QStudentRecordListModel::seek(uint32_t mode, uint32_t amount)
{
    try{
        fcb.updateCancel();
    } catch (...) { }
    fcb.seek(mode, amount);
    read();
    emit dataChanged(this->index(0), this->index(this->rowCount()));
}

void QStudentRecordListModel::deleteRecord()
{
    fcb.delRecord();
    read();
    emit dataChanged(this->index(0), this->index(this->rowCount()));
}

void QStudentRecordListModel::read()
{
    if(fcb.eof()){
        record = FmsUtils::StudentRecord();
    } else {
        try{
            if (mode == Fms::Fcb::OpenMode::IO){
                try{
                    fcb.updateCancel();
                } catch (...) { }
                memcpy(reinterpret_cast<char*>(&record),fcb.read(1).get(),sizeof(FmsUtils::StudentRecord));
                if (record.key == -1) moveNext();
            } else if (mode == Fms::Fcb::OpenMode::I){
                memcpy(reinterpret_cast<char*>(&record),fcb.read(0).get(),sizeof(FmsUtils::StudentRecord));
                if (record.key == -1) moveNext();
            } else if (mode == Fms::Fcb::OpenMode::O){
                record = FmsUtils::StudentRecord();
            }
        } catch (...) {
            record = FmsUtils::StudentRecord();
            // Hopefully this isn't needed and logic work correctly
        }
    }
}
