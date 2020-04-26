#ifndef UPLOADFILEDIALOG_H
#define UPLOADFILEDIALOG_H

#include <QDialog>
#include "Disk.h"
#include "gui.h"

namespace Ui {
class uploadFileDialog;
}

class uploadFileDialog : public QDialog
{
    Q_OBJECT

public:
    uploadFileDialog(QWidget *parent = 0);
    ~uploadFileDialog();
	QString getFileName();
	QString getFileOwner();
	QString getFilePath();
	uint8_t getRecordSizeOption();
	uint32_t getFit();


private slots:
	void on_pushButtonBrowseFile_clicked();

private:
    Ui::uploadFileDialog *ui;
};

#endif // UPLOADFILEDIALOG_H
