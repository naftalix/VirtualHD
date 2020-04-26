#include "studentrecordsdialog.h"
#include "ui_studentrecordsdialog.h"
#include <QInputDialog>
#include <QMessageBox>
#include "seekrecdialog.h"


StudentRecordsDialog::StudentRecordsDialog(Fms::Fcb &fcb, int modeInt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentRecordsDialog), fcb(fcb)
{
	Fms::Fcb::OpenMode mode;
	switch (modeInt){
	case 0:
		mode = Fms::Fcb::OpenMode::I;
		break;
	case 1:
		mode = Fms::Fcb::OpenMode::IO;
		break;
		case 2:
		mode = Fms::Fcb::OpenMode::O;
		break;
	}

    ui->setupUi(this);
    student = new QStudentRecordListModel(fcb, mode, this);
    mapper = new QDataWidgetMapper(this);
    mapper->setOrientation(Qt::Vertical);
    mapper->setModel(student);
    mapper->setSubmitPolicy(QDataWidgetMapper::SubmitPolicy::ManualSubmit);
    mapper->addMapping(ui->lineEditId, 0);
    mapper->addMapping(ui->lineEditName, 1);
    mapper->addMapping(ui->plainTextAddress, 2);
    mapper->addMapping(ui->lineEditAverage, 3);
    mapper->toFirst();
}

StudentRecordsDialog::~StudentRecordsDialog()
{
    delete ui;
}

void StudentRecordsDialog::on_buttonPrev_clicked()
{
    try{
        student->movePrev();
    } catch (std::exception e){
        QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
    }
    mapper->revert();
}

void StudentRecordsDialog::on_buttonNext_clicked()
{
    try{
        student->moveNext();
    } catch (std::exception e){
        QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
    }
    mapper->revert();
}

void StudentRecordsDialog::on_buttonWrite_clicked()
{
    mapper->submit();
    try{
        student->write();
    } catch (std::exception e){
        QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
    }
    mapper->revert();
}

void StudentRecordsDialog::on_buttonDelete_clicked()
{
    try{
        student->deleteRecord();
    } catch (std::exception e){
        QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
    }
    mapper->revert();
}

void StudentRecordsDialog::on_buttonSeek_clicked()
{
	SeekRecDialog seeDial(this);
	seeDial.exec();
	if (seeDial.result() == QDialog::Accepted){
		try{
			student->seek((uint32_t)seeDial.getPlaceMode(), seeDial.getSeekNum());
		}
		catch(std::exception e)
		{
			QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
		}
	}
	mapper->revert();
	
}

void StudentRecordsDialog::on_pushButtonAddRecord_clicked()
{
		try{
			student->seek(2,0);
		}
		catch(std::exception e)
		{
			QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
		}
		mapper->revert();
}
