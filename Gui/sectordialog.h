#ifndef SECTORDIALOG_H
#define SECTORDIALOG_H

#include <QDialog>
#include "Disk.h"

namespace Ui {
class SectorDialog;
}

class SectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SectorDialog(Fms::Disk &d, QWidget *parent = 0);
    ~SectorDialog();

	


private slots:
	void on_selectSectorButton_clicked();
	void on_readSectorButton_clicked();
	void on_writeSectorButton_clicked();

private:
    Ui::SectorDialog *ui;
	Fms::Disk &d;
	Fms::SectorId secNum;
	bool selected;
};

#endif // SECTORDIALOG_H
