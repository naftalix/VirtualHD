#include "seekrecdialog.h"
#include "ui_seekrecdialog.h"

SeekRecDialog::SeekRecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeekRecDialog)
{
    ui->setupUi(this);
}

SeekRecDialog::~SeekRecDialog()
{
    delete ui;
}


void SeekRecDialog::on_buttonBox_accepted()
{
	place = placeMode::BEGIN;
	if(ui->radioButtonCur->isChecked()) place = placeMode::CURRENT;
	if(ui->radioButtonEnd->isChecked()) place = placeMode::END;

	recSeekNum = ui->spinBox->value();
}

placeMode SeekRecDialog::getPlaceMode() { return place; }
int32_t SeekRecDialog::getSeekNum() { return recSeekNum; }
