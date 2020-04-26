#include "uploadfiledialog.h"
#include "ui_uploadfiledialog.h"
#include <QFileDialog>
#include <QMessageBox>

uploadFileDialog::uploadFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uploadFileDialog)
{
    ui->setupUi(this);
}

uploadFileDialog::~uploadFileDialog()
{
    delete ui;
}

void uploadFileDialog::on_pushButtonBrowseFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Upload File"), QString("."));
    if (fileName.isEmpty()) return;
	ui->lineEditPath->setText(fileName);
	QFileInfo f(fileName);
	ui->lineEditFileName->setText(f.fileName());
}

QString uploadFileDialog::getFilePath(){
	return ui->lineEditPath->text();
}

QString uploadFileDialog::getFileName(){
	return ui->lineEditFileName->text();
}

QString uploadFileDialog::getFileOwner(){
	return ui->lineEditOwnerName->text();
}

uint8_t uploadFileDialog::getRecordSizeOption(){
	uint8_t recSize = 30;
	if(ui->radioButton64->isChecked()) recSize = 64;
	if(ui->radioButton98->isChecked()) recSize = 98;
	if(ui->radioButton200->isChecked()) recSize = 200;
	return recSize;
}

uint32_t uploadFileDialog::getFit(){ 
		uint32_t fit = 0;
		if(ui->radioButtonBestFit->isChecked()) fit = 1;
		if(ui->radioButtonWorseFit->isChecked()) fit = 2;
		return fit;
	}