#ifndef GUI_H
#define GUI_H

#include <QtWidgets/QMainWindow>
#include <QSortFilterProxyModel>
#include "ui_gui.h"
#include "Disk.h"
#include "QDirListModel.h"
#include "QFileListModel.h"
#include "QDirTableModel.h"
#include "QVhdListModel.h"
#include "QDatTypeTableModel.h"
#include "QLocationArrayTableModel.h"

class Gui : public QMainWindow
{
	Q_OBJECT

public:
	Gui(QWidget *parent = 0);
	~Gui();

private slots:

	//Disk menu bar
	void on_actionCreate_Disk_triggered();
    void on_actionMount_Disk_triggered();
    void on_actionUnmount_Disk_triggered();
    void on_actionFormat_Disk_triggered();
    void on_actionRecreate_Disk_triggered();
	void on_actionSector_triggered();
	void on_actionExit_triggered();

	//File menu bar
	void on_actionDownload_File_triggered();
    void on_actionDownload_Student_File_triggered();
    void on_actionUpload_Studen_File_triggered();
    void on_actionDelete_File_triggered();
	void on_actionUpload_File_triggered();
	void on_actionOpen_Student_File_triggered();
	void on_actionCreate_Student_File_triggered();
	void on_actionDefrag_triggered();
	void on_actionPrint_students_file_triggered();
	void on_actionAbout_triggered();

	// Buttons
	void on_commandLinkButtonShowDir_clicked();

	// Other
	void updateChosenFile(const QItemSelection& selection);
    void forceProxyUpdate();

private:
    //! Helper function to intialize the sources for the models.
    void initSources();

    //! Helper function to intialize the context for the viewers.
    void initContext();

    Ui::GuiClass ui;
	Fms::Disk d;
    QVhdListModel *vhd;
    QDirListModel *dir;
    QFileListModel *file;
    QSortFilterProxyModel *dirWithoutEmptyFiles;

    QDatTypeTableModel *dat;
    QDatTypeTableModel *fat;

    QDirTableModel *fullDir;
    QSortFilterProxyModel *fullDirNoEmptyFiles;
    QSortFilterProxyModel *singleFile;
	
	QLocationArrayTableModel *locations;
};

#endif // GUI_H
