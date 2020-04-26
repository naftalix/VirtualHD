#include "gui.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QTableView>
#include <QDebug>
#include "sectordialog.h"
#include "uploadfiledialog.h"
#include "studentrecordsdialog.h"
#include "Student.h"
#include <sstream>

#include<QDebug>

Gui::Gui(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);

	initSources();
	initContext();
}

Gui::~Gui()
{

}

void Gui::initSources(){
	vhd = new QVhdListModel(d, this);
	dir = new QDirListModel(d, this);
	file = new QFileListModel(d, "", this);
	dirWithoutEmptyFiles = new QSortFilterProxyModel(this);
	dirWithoutEmptyFiles->setFilterRegExp("^(?=\\s*\\S).*$");
	dirWithoutEmptyFiles->sort(0);
	dirWithoutEmptyFiles->setSourceModel(dir);

	fullDir = new QDirTableModel(d, this);
	fullDirNoEmptyFiles = new QSortFilterProxyModel();
	fullDirNoEmptyFiles->setSourceModel(fullDir);
	fullDirNoEmptyFiles->setFilterFixedString("1");
	fullDirNoEmptyFiles->setFilterKeyColumn(13);
	singleFile = new QSortFilterProxyModel(this);
	singleFile->setFilterKeyColumn(0);
	singleFile->setSourceModel(fullDirNoEmptyFiles);
	singleFile->setFilterRegExp("$^");

	dat = new QDatTypeTableModel(d, QString(""), this);
	fat = new QDatTypeTableModel(d, QString(" "), this);

	locations = new QLocationArrayTableModel(d, QString(), this);

	//ui.fileList->setModel(fullDirNoEmptyFiles);
	//ui.fileData->setModel(singleFile);
	ui.fileList->setModel(dirWithoutEmptyFiles);
	ui.fileData->setModel(file);
	ui.vhdData->setModel(vhd);
	ui.datView->setModel(dat);
	ui.fatView->setModel(fat);
	ui.allocationTableView->setModel(locations);

	ui.tabWidget->setCurrentIndex(0);

	connect(ui.fileList->selectionModel(),
		SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
		this, SLOT(updateChosenFile(QItemSelection)));
}

void Gui::initContext()
{
	ui.fileList->setContextMenuPolicy(Qt::ActionsContextMenu);
	QList<QAction*> fileListActions;
	fileListActions << ui.actionDownload_File << ui.actionDelete_File << ui.actionDownload_Student_File << ui.actionOpen_Student_File << ui.actionPrint_students_file;
	ui.fileList->addActions(fileListActions);

	ui.menuFile->setEnabled(false);
	ui.actionUnmount_Disk->setEnabled(false);
	ui.actionFormat_Disk->setEnabled(false);
	ui.actionSector->setEnabled(false);
	ui.actionDefrag->setEnabled(false);
}

void Gui::on_actionCreate_Disk_triggered()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Create disk"), QString("."));
	if (fileName.isEmpty()) return;
	bool ok;
	QString ownerName = QInputDialog::getText(this, tr("Create disk"), tr("Owner name:"), QLineEdit::Normal, tr(""), &ok);
	if (!ok) return;
	try{
		d.createDisk(fileName.toStdString(), ownerName.toStdString());
		QMessageBox::information(this, tr("Status"), tr("The disk has been created"), QMessageBox::Ok);
	} catch (std::exception e){
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}
}

void Gui::on_actionMount_Disk_triggered()
{

	QString fileName = QFileDialog::getOpenFileName(this, tr("Mount disk"), QString("."));
	if (fileName.isEmpty()) return;

	try{
		d.mountDisk(fileName.toStdString());
		forceProxyUpdate();

		ui.actionUnmount_Disk->setEnabled(true);
		ui.actionFormat_Disk->setEnabled(true);
		ui.actionDefrag->setEnabled(true);
		if (d.getVolumeHeader().isFormated){
			ui.menuFile->setEnabled(true);
			ui.actionSector->setEnabled(true);
		}
		ui.actionCreate_Disk->setEnabled(false);
		ui.actionRecreate_Disk->setEnabled(false);
		ui.actionMount_Disk->setEnabled(false);

		QMessageBox::information(this, tr("Status"), tr("The disk has been mounted"), QMessageBox::Ok);
	} catch (std::exception e){
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}
}

void Gui::on_actionUnmount_Disk_triggered()
{
	try{
		d.unmountDisk();
		forceProxyUpdate();
		ui.actionCreate_Disk->setEnabled(true);
		ui.actionRecreate_Disk->setEnabled(true);
		ui.menuFile->setEnabled(false);
		ui.actionUnmount_Disk->setEnabled(false);
		ui.actionFormat_Disk->setEnabled(false);
		ui.actionSector->setEnabled(false);
		ui.actionMount_Disk->setEnabled(true);
		ui.actionDefrag->setEnabled(false);
		QMessageBox::information(this, tr("Status"), tr("The disk has been unmounted"), QMessageBox::Ok);
	} catch (std::exception e){
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}
}

void Gui::on_actionFormat_Disk_triggered()
{
	bool ok;
	QString ownerName = QInputDialog::getText(this, tr("Format Disk"), tr("Owner name:"), QLineEdit::Normal, tr(""), &ok);
	if (ok){
		try{
			d.format(ownerName.toStdString());
			forceProxyUpdate();
			ui.menuFile->setEnabled(true);
			ui.actionSector->setEnabled(true);
			QMessageBox::information(this, tr("Status"), tr("The disk has been formatted"), QMessageBox::Ok);
		} catch (std::exception e){
			QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
		}
	}
}

void Gui::on_actionRecreate_Disk_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Recreate Disk"), QString("."));
	if (fileName.isEmpty()) return;
	bool ok;
	QString ownerName = QInputDialog::getText(this, tr("Format Disk"), tr("Owner name:"), QLineEdit::Normal, tr(""), &ok);
	if (!ok) return;
	try{
		d.mountDisk(fileName.toStdString());
		d.unmountDisk();
		d.recreateDisk(ownerName.toStdString());
		QMessageBox::information(this, tr("Status"), tr("The disk has been recreated"), QMessageBox::Ok);
	} catch (std::exception e){
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}
}

void Gui::on_actionSector_triggered()
{
	SectorDialog secDiag(d,this);
	secDiag.exec();
}

void Gui::on_actionExit_triggered()
{
}

void Gui::updateChosenFile(const QItemSelection& selection)
{
	if(selection.indexes().isEmpty()) {
		file->changeSource(std::string());
		fat->changeSource(QString(" "));
		//singleFile->setFilterRegExp("$^");
	} else {
		QModelIndex index = selection.indexes().first();
		//QMessageBox::information(this, tr("Hello"), dir->data(index, Qt::DisplayRole).toString(), QMessageBox::Ok);
		file->changeSource(dirWithoutEmptyFiles->data(index, Qt::DisplayRole).toString().toStdString());
		fat->changeSource(dirWithoutEmptyFiles->data(index, Qt::DisplayRole).toString());
		locations->changeSource(dirWithoutEmptyFiles->data(index, Qt::DisplayRole).toString());
		//file->changeSource(fullDirNoEmptyFiles->data(index, Qt::DisplayRole).toString().toStdString());
		//singleFile->setFilterFixedString(fullDirNoEmptyFiles->data(index).toString());
	}
}

void Gui::forceProxyUpdate(){
	dirWithoutEmptyFiles->invalidate();
	fullDirNoEmptyFiles->invalidate();
	singleFile->invalidate();
	dat->refresh();
	fat->refresh();
	locations->refresh();
	try{
		std::stringstream s;
		Fms::Dat dat(d.getDat());
		s << dat;
		ui.labelDATsum->setText(QString(s.str().c_str()));
		dat.dat.flip();
		qint32 precentge = float(dat.dat.count()) / dat.dat.size() * 100;
		ui.progressBar->setValue(precentge);
	} catch (...){
		ui.labelDATsum->setText(tr("No usable disk have been found..."));
		ui.progressBar->setValue(0);
	}
}

void Gui::on_actionDownload_File_triggered()
{
	QModelIndex index = ui.fileList->currentIndex();
	if (index.isValid() == false){
		QMessageBox::warning(this, tr("Error!"), tr("No file selected."), QMessageBox::Ok);
		return;
	}
	QString fileName = QFileDialog::getSaveFileName(this, tr("Download file"), QString("."));
	if (fileName.isEmpty()) return;
	bool ok;
	QString ownerName = QInputDialog::getText(this, tr("Download file"), tr("Owner name:"), QLineEdit::Normal, tr(""), &ok);
	if (!ok) return;
	std::string fileToDownload = dirWithoutEmptyFiles->data(index).toString().toStdString();
	try{
		d.downloadFile(fileName.toStdString(), fileToDownload, ownerName.toStdString());
		QMessageBox::information(this, tr("Status"), tr("The file has been downloaded"), QMessageBox::Ok);
	} catch (std::exception e){
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}
}

void Gui::on_actionDownload_Student_File_triggered()
{
	QModelIndex index = ui.fileList->currentIndex();
	if (index.isValid() == false){
		QMessageBox::warning(this, tr("Error!"), tr("No file selected."), QMessageBox::Ok);
		return;
	}
	QString fileName = QFileDialog::getSaveFileName(this, tr("Download students file"), QString("."), QString("Text file (*.txt)"));
	if (fileName.isEmpty()) return;

	std::string fileToDownload = dirWithoutEmptyFiles->data(index).toString().toStdString();
	try{
		FmsUtils::StudentRecord::downloadStudentsFile(d, fileToDownload, fileName.toStdString());
		QMessageBox::information(this, tr("Status"), tr("The file has been downloaded"), QMessageBox::Ok);
	} catch (std::exception e){
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}
}

void Gui::on_actionUpload_Studen_File_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Upload students file"), QString("."), QString("Text file (*.txt)"));
	if (fileName.isEmpty()) return;
	bool ok;
	QString fileToUpload = QInputDialog::getText(this, tr("Upload students file"), tr("File name:"), QLineEdit::Normal, tr(""), &ok);
	if (!ok) return;
	try{
		FmsUtils::StudentRecord::uploadStudentsFile(d, fileToUpload.toStdString(), fileName.toStdString());
		forceProxyUpdate();
		QMessageBox::information(this, tr("Status"), tr("The file has been uploaded"), QMessageBox::Ok);
	} catch (std::exception e){
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}
}

void Gui::on_actionDelete_File_triggered()
{
	QModelIndex index = ui.fileList->currentIndex();
	if (index.isValid() == false){
		QMessageBox::warning(this, tr("Error!"), tr("No file selected."), QMessageBox::Ok);
		return;
	}
	bool ok;
	QString ownerName = QInputDialog::getText(this, tr("Delete file"), tr("Owner name:"), QLineEdit::Normal, tr(""), &ok);
	if (!ok) return;
	std::string fileToDelete = dirWithoutEmptyFiles->data(index).toString().toStdString();
	try{
		d.delFile(fileToDelete, ownerName.toStdString());
		forceProxyUpdate();
		QMessageBox::information(this, tr("Status"), tr("The file has been deleted"), QMessageBox::Ok);
	} catch (std::exception e){
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}
}

void Gui::on_actionUpload_File_triggered()
{
	uploadFileDialog upDial(this);
	upDial.exec();
	if (upDial.result() == QDialog::Accepted){
		std::string src = upDial.getFilePath().toStdString();
		std::string fileName = upDial.getFileName().toStdString();
		std::string ownerName = upDial.getFileOwner().toStdString();
		uint8_t recordSize = upDial.getRecordSizeOption();
		uint32_t fit = upDial.getFit();
		try{
			d.uploadFile(src, fileName, ownerName, fit, recordSize);
			forceProxyUpdate();
			QMessageBox::information(this, tr("Status"), tr("The file has been uploaded"), QMessageBox::Ok);
		}
		catch (std::exception e){
			QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
		}
	}
}

void Gui::on_actionOpen_Student_File_triggered()
{ 
	QModelIndex index = ui.fileList->currentIndex();
	if (index.isValid() == false){
		QMessageBox::warning(this, tr("Error!"), tr("No file selected."), QMessageBox::Ok);
		return;
	}
	std::string fileToOpen = dirWithoutEmptyFiles->data(index).toString().toStdString();

	std::unique_ptr<Fms::Fcb> fcb;
	try{
		fcb = d.openFile(fileToOpen, std::string("Students"), "IO");
	} catch (std::exception e) {
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
		return;
	}
	if (fcb->fileDesc.fileSize != 0){
		QMessageBox::critical(this, tr("Exception!"), tr("Can't open file as student file"), QMessageBox::Ok);
		return;
	}
	StudentRecordsDialog srd(*fcb.get(), 1, this);
	srd.exec();
	fat->refresh();
}

void Gui::on_actionCreate_Student_File_triggered()
{
	bool ok;
	QString fileName = QInputDialog::getText(this, tr("Create students file"), tr("File name:"), QLineEdit::Normal, tr(""), &ok);
	try{
		d.createFile(fileName.toStdString(), std::string("Students"), std::string("F"), 204, 1, std::string("I"), 0, 1, 4);
		std::unique_ptr<Fms::Fcb> fcb = d.openFile(fileName.toStdString(), std::string("Students"), "IO");
		if (fcb->fileDesc.fileSize != 0){
			QMessageBox::critical(this, tr("Exception!"), tr("Can't open file as student file"), QMessageBox::Ok);
			return;
		}
		StudentRecordsDialog srd(*fcb.get(), 1, this);

		srd.exec();
		QMessageBox::information(this, tr("Status"), tr("The file has been created"), QMessageBox::Ok);
		forceProxyUpdate();
	}
	catch(std::exception e){
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}

}

void Gui::on_actionDefrag_triggered(){
	try{
		d.defrag(10000);
		forceProxyUpdate();
		QMessageBox::information(this, tr("Status"), tr("The disk has been defragmentted!"), QMessageBox::Ok);
	} catch(std::exception e){
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}
}

void Gui::on_actionPrint_students_file_triggered()
{
	try{
		std::string textStd = FmsUtils::StudentRecord::studentFileAsString(d, file->data(file->index(0), Qt::DisplayRole).toString().toStdString());
		QString text = QString(textStd.c_str());
		QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon, tr("List of students"), tr("To see the students, press show details:") + QString("\t\t\t\t\t\t\t\t\t"), QMessageBox::Ok, this);
		msg->setDetailedText(text);
		msg->exec();
	} catch(std::exception e){
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}
}

void Gui::on_actionAbout_triggered()
{
	QMessageBox *msg = new QMessageBox(QMessageBox::Information, tr("Copyright"), tr("'File Managment System' 'C' 2014\nThis program made by some people\nAll rights reserved.") , QMessageBox::Ok, this);
	msg->exec();
}

void Gui::on_commandLinkButtonShowDir_clicked()
{
	try{
		std::stringstream s;
		s << d.getDir();
		std::string textStd = s.str();
		QString text = QString(textStd.c_str());
		QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon, tr("Directory contents"), tr("To see the dir, press show details:") + QString("\t\t\t\t\t\t\t\t\t"), QMessageBox::Ok, this);
		msg->setDetailedText(text);
		msg->exec();
	} catch(std::exception e){
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}
}