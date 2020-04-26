#ifndef SEEKRECDIALOG_H
#define SEEKRECDIALOG_H

#include <QDialog>
#include <stdint.h>

namespace Ui {
class SeekRecDialog;
}

enum class placeMode : uint32_t {BEGIN,CURRENT,END};
class SeekRecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SeekRecDialog(QWidget *parent = 0);
    ~SeekRecDialog();

	placeMode getPlaceMode();
	int32_t getSeekNum();

public slots:
	void on_buttonBox_accepted();

private:
    Ui::SeekRecDialog *ui;
	placeMode place;
	int32_t recSeekNum;
};

#endif // SEEKRECDIALOG_H
