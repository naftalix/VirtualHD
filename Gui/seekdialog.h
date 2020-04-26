#ifndef SEEKDIALOG_H
#define SEEKDIALOG_H

#include <QWidget>
#include <stdint.h>
namespace Ui {class SeekDialog;};


enum class placeMode : uint32_t {BEGIN,CURRENT,END};
class SeekDialog : public QWidget
{
	Q_OBJECT

public:
	SeekDialog(QWidget *parent = 0);
	~SeekDialog();

	placeMode getPlaceMode();
	int32_t getSeekNum();

public slots:
	void on_buttonBox_accepted();

private:
	Ui::SeekDialog *ui;
	placeMode place;
	int32_t recSeekNum;
};

#endif // SEEKDIALOG_H
