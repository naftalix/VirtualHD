#include "seekdialog.h"
#include "ui_seekdialog.h"

SeekDialog::SeekDialog(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::SeekDialog();
	ui->setupUi(this);
}

SeekDialog::~SeekDialog()
{
	delete ui;
}


void SeekDialog::on_buttonBox_accepted()
{
	place = placeMode::BEGIN;
	if(ui->radioButtonCur->isChecked()) place = placeMode::CURRENT;
	if(ui->radioButtonEnd->isChecked()) place = placeMode::END;

	recSeekNum = ui->spinBox->value();
}

placeMode SeekDialog::getPlaceMode() { return place; }
int32_t SeekDialog::getSeekNum() { return recSeekNum; }