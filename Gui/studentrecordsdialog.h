#ifndef STUDENTRECORDSDIALOG_H
#define STUDENTRECORDSDIALOG_H

#include <QDialog>
#include <QStudentRecordListModel.h>
#include <QDataWidgetMapper>
#include <QMessageBox>

namespace Ui {
class StudentRecordsDialog;
}

class StudentRecordsDialog : public QDialog
{
    Q_OBJECT

public:
    StudentRecordsDialog(Fms::Fcb&, int, QWidget *parent = 0);
    ~StudentRecordsDialog();

private slots:
    void on_buttonPrev_clicked();
    void on_buttonNext_clicked();
    void on_buttonWrite_clicked();
	void on_buttonSeek_clicked();
    void on_buttonDelete_clicked();
	void on_pushButtonAddRecord_clicked();

private:
    Ui::StudentRecordsDialog *ui;
    Fms::Fcb &fcb;
    QStudentRecordListModel *student;
    QDataWidgetMapper *mapper;
};

#endif // STUDENTRECORDSDIALOG_H
