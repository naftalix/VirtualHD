#include "sectordialog.h"
#include "ui_sectordialog.h"
#include <QMessageBox>


SectorDialog::SectorDialog(Fms::Disk &d, QWidget *parent) :
    QDialog(parent), d(d), ui(new Ui::SectorDialog())
{
    ui->setupUi(this);
	ui->spinBox->setMaximum(Fms::CLUSTERSINDISK*Fms::CLUSTERSIZE-1);
	selected = false;
}

SectorDialog::~SectorDialog()
{
    delete ui;
}


void SectorDialog::on_selectSectorButton_clicked()
{
	secNum = ui->spinBox->value();
	ui->textEdit->clear();
	selected = true;
	QMessageBox::information(this, tr("Status"), tr("The Sector number: %1 has been selected").arg(secNum), QMessageBox::Ok);
}

void SectorDialog::on_readSectorButton_clicked()
{
	try
	{
		if(!selected && secNum != ui->spinBox->value()) throw std::exception("No Sector selected!");
		Fms::Sector sec;
		d.readSector(secNum, &sec);
		QString data(sec.rawData);
		ui->textEdit->setText(data);
		selected = false;
	}
	catch(std::exception e)
	{
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}
}

void SectorDialog::on_writeSectorButton_clicked()
{
	try
	{
		if(!selected && secNum != ui->spinBox->value()) throw std::exception("No Sector selected!");
		QString data = ui->textEdit->toPlainText();
		Fms::Sector sec;
		sec.sectorNr = secNum;
		std::memcpy(sec.rawData,data.toStdString().c_str(),sizeof(sec.rawData));
		d.writeFreeSector(secNum,&sec);
		selected = false;
		QMessageBox::information(this, tr("Status"), tr("The data has been written in Sector %1").arg(secNum), QMessageBox::Ok);
	}
	catch(std::exception e)
	{
		QMessageBox::critical(this, tr("Exception!"), tr(e.what()), QMessageBox::Ok);
	}
}
