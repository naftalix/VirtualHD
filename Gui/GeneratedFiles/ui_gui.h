/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuiClass
{
public:
    QAction *actionCreate_Disk;
    QAction *actionRecreate_Disk;
    QAction *actionMount_Disk;
    QAction *actionUnmount_Disk;
    QAction *actionFormat_Disk;
    QAction *actionSector;
    QAction *actionExit;
    QAction *actionInfo;
    QAction *actionAbout;
    QAction *actionUpload_File;
    QAction *actionDownload_File;
    QAction *actionDelete_File;
    QAction *actionCreate_Student_File;
    QAction *actionDownload_Student_File;
    QAction *actionOpen_Student_File;
    QAction *actionUpload_Studen_File;
    QAction *actionDefrag;
    QAction *actionPrint_students_file;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QLabel *labelDAT;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelVHD;
    QTableView *vhdData;
    QTableView *datView;
    QLabel *labelDATsum;
    QLabel *label;
    QProgressBar *progressBar;
    QLabel *labelDAT_2;
    QWidget *tab_2;
    QLabel *labelFileList_2;
    QTableView *fileData;
    QLabel *labelFileList;
    QListView *fileList;
    QLabel *labelFileList_3;
    QTableView *fatView;
    QTableView *allocationTableView;
    QLabel *labelFileList_4;
    QCommandLinkButton *commandLinkButtonShowDir;
    QMenuBar *menuBar;
    QMenu *menuDisk;
    QMenu *menuFile;
    QMenu *menuStudent_File;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GuiClass)
    {
        if (GuiClass->objectName().isEmpty())
            GuiClass->setObjectName(QStringLiteral("GuiClass"));
        GuiClass->resize(801, 648);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GuiClass->sizePolicy().hasHeightForWidth());
        GuiClass->setSizePolicy(sizePolicy);
        GuiClass->setMaximumSize(QSize(16777215, 16777215));
        GuiClass->setContextMenuPolicy(Qt::DefaultContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/main.png"), QSize(), QIcon::Normal, QIcon::Off);
        GuiClass->setWindowIcon(icon);
        actionCreate_Disk = new QAction(GuiClass);
        actionCreate_Disk->setObjectName(QStringLiteral("actionCreate_Disk"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/createdisk.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_Disk->setIcon(icon1);
        actionRecreate_Disk = new QAction(GuiClass);
        actionRecreate_Disk->setObjectName(QStringLiteral("actionRecreate_Disk"));
        actionRecreate_Disk->setIcon(icon1);
        actionMount_Disk = new QAction(GuiClass);
        actionMount_Disk->setObjectName(QStringLiteral("actionMount_Disk"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/mount.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMount_Disk->setIcon(icon2);
        actionUnmount_Disk = new QAction(GuiClass);
        actionUnmount_Disk->setObjectName(QStringLiteral("actionUnmount_Disk"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/unmount.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUnmount_Disk->setIcon(icon3);
        actionFormat_Disk = new QAction(GuiClass);
        actionFormat_Disk->setObjectName(QStringLiteral("actionFormat_Disk"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/format.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFormat_Disk->setIcon(icon4);
        actionSector = new QAction(GuiClass);
        actionSector->setObjectName(QStringLiteral("actionSector"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/sector.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSector->setIcon(icon5);
        actionExit = new QAction(GuiClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/exit.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon6);
        actionInfo = new QAction(GuiClass);
        actionInfo->setObjectName(QStringLiteral("actionInfo"));
        actionAbout = new QAction(GuiClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionUpload_File = new QAction(GuiClass);
        actionUpload_File->setObjectName(QStringLiteral("actionUpload_File"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/upload.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUpload_File->setIcon(icon7);
        actionDownload_File = new QAction(GuiClass);
        actionDownload_File->setObjectName(QStringLiteral("actionDownload_File"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDownload_File->setIcon(icon8);
        actionDelete_File = new QAction(GuiClass);
        actionDelete_File->setObjectName(QStringLiteral("actionDelete_File"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete_File->setIcon(icon9);
        actionCreate_Student_File = new QAction(GuiClass);
        actionCreate_Student_File->setObjectName(QStringLiteral("actionCreate_Student_File"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images/createfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_Student_File->setIcon(icon10);
        actionDownload_Student_File = new QAction(GuiClass);
        actionDownload_Student_File->setObjectName(QStringLiteral("actionDownload_Student_File"));
        actionDownload_Student_File->setIcon(icon8);
        actionOpen_Student_File = new QAction(GuiClass);
        actionOpen_Student_File->setObjectName(QStringLiteral("actionOpen_Student_File"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Student_File->setIcon(icon11);
        actionUpload_Studen_File = new QAction(GuiClass);
        actionUpload_Studen_File->setObjectName(QStringLiteral("actionUpload_Studen_File"));
        actionUpload_Studen_File->setIcon(icon7);
        actionDefrag = new QAction(GuiClass);
        actionDefrag->setObjectName(QStringLiteral("actionDefrag"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/images/defrag.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDefrag->setIcon(icon12);
        actionPrint_students_file = new QAction(GuiClass);
        actionPrint_students_file->setObjectName(QStringLiteral("actionPrint_students_file"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/images/Print.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint_students_file->setIcon(icon13);
        centralWidget = new QWidget(GuiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tabWidget->setIconSize(QSize(16, 16));
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        labelDAT = new QLabel(tab_1);
        labelDAT->setObjectName(QStringLiteral("labelDAT"));
        labelDAT->setGeometry(QRect(360, 21, 121, 19));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        font.setKerning(true);
        labelDAT->setFont(font);
        layoutWidget = new QWidget(tab_1);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 20, 261, 411));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        labelVHD = new QLabel(layoutWidget);
        labelVHD->setObjectName(QStringLiteral("labelVHD"));
        labelVHD->setFont(font);

        verticalLayout->addWidget(labelVHD);

        vhdData = new QTableView(layoutWidget);
        vhdData->setObjectName(QStringLiteral("vhdData"));
        vhdData->setAutoFillBackground(false);
        vhdData->setAutoScroll(true);
        vhdData->setAlternatingRowColors(true);
        vhdData->setSelectionMode(QAbstractItemView::NoSelection);
        vhdData->setIconSize(QSize(4, 4));

        verticalLayout->addWidget(vhdData);

        datView = new QTableView(tab_1);
        datView->setObjectName(QStringLiteral("datView"));
        datView->setGeometry(QRect(360, 46, 371, 371));
        datView->setAutoFillBackground(true);
        datView->setFrameShape(QFrame::NoFrame);
        datView->setFrameShadow(QFrame::Plain);
        datView->setLineWidth(0);
        datView->setAutoScroll(true);
        datView->setSelectionMode(QAbstractItemView::NoSelection);
        datView->horizontalHeader()->setVisible(false);
        datView->horizontalHeader()->setDefaultSectionSize(9);
        datView->horizontalHeader()->setMinimumSectionSize(0);
        datView->verticalHeader()->setVisible(false);
        datView->verticalHeader()->setDefaultSectionSize(9);
        datView->verticalHeader()->setMinimumSectionSize(0);
        labelDATsum = new QLabel(tab_1);
        labelDATsum->setObjectName(QStringLiteral("labelDATsum"));
        labelDATsum->setGeometry(QRect(360, 450, 371, 41));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        labelDATsum->setFont(font1);
        label = new QLabel(tab_1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(360, 430, 81, 16));
        QFont font2;
        font2.setPointSize(10);
        font2.setItalic(true);
        font2.setUnderline(false);
        font2.setStrikeOut(false);
        label->setFont(font2);
        progressBar = new QProgressBar(tab_1);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(30, 490, 261, 23));
        progressBar->setValue(0);
        labelDAT_2 = new QLabel(tab_1);
        labelDAT_2->setObjectName(QStringLiteral("labelDAT_2"));
        labelDAT_2->setGeometry(QRect(30, 470, 121, 19));
        labelDAT_2->setFont(font);
        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        labelFileList_2 = new QLabel(tab_2);
        labelFileList_2->setObjectName(QStringLiteral("labelFileList_2"));
        labelFileList_2->setGeometry(QRect(172, 9, 93, 19));
        labelFileList_2->setFont(font);
        fileData = new QTableView(tab_2);
        fileData->setObjectName(QStringLiteral("fileData"));
        fileData->setGeometry(QRect(186, 32, 211, 481));
        fileData->setAlternatingRowColors(true);
        fileData->setSelectionMode(QAbstractItemView::NoSelection);
        labelFileList = new QLabel(tab_2);
        labelFileList->setObjectName(QStringLiteral("labelFileList"));
        labelFileList->setGeometry(QRect(3, 9, 63, 19));
        labelFileList->setFont(font);
        fileList = new QListView(tab_2);
        fileList->setObjectName(QStringLiteral("fileList"));
        fileList->setGeometry(QRect(7, 32, 172, 481));
        fileList->setTabKeyNavigation(true);
        fileList->setDragEnabled(true);
        fileList->setIconSize(QSize(4, 4));
        fileList->setSpacing(8);
        fileList->setViewMode(QListView::ListMode);
        labelFileList_3 = new QLabel(tab_2);
        labelFileList_3->setObjectName(QStringLiteral("labelFileList_3"));
        labelFileList_3->setGeometry(QRect(390, 10, 101, 19));
        labelFileList_3->setFont(font);
        fatView = new QTableView(tab_2);
        fatView->setObjectName(QStringLiteral("fatView"));
        fatView->setGeometry(QRect(404, 32, 371, 371));
        fatView->setAutoFillBackground(true);
        fatView->setFrameShape(QFrame::NoFrame);
        fatView->setFrameShadow(QFrame::Plain);
        fatView->setLineWidth(0);
        fatView->setSelectionMode(QAbstractItemView::NoSelection);
        fatView->horizontalHeader()->setVisible(false);
        fatView->horizontalHeader()->setDefaultSectionSize(9);
        fatView->horizontalHeader()->setMinimumSectionSize(0);
        fatView->verticalHeader()->setVisible(false);
        fatView->verticalHeader()->setDefaultSectionSize(9);
        fatView->verticalHeader()->setMinimumSectionSize(0);
        allocationTableView = new QTableView(tab_2);
        allocationTableView->setObjectName(QStringLiteral("allocationTableView"));
        allocationTableView->setGeometry(QRect(480, 428, 221, 131));
        allocationTableView->setSelectionMode(QAbstractItemView::NoSelection);
        labelFileList_4 = new QLabel(tab_2);
        labelFileList_4->setObjectName(QStringLiteral("labelFileList_4"));
        labelFileList_4->setGeometry(QRect(520, 406, 131, 19));
        labelFileList_4->setFont(font);
        commandLinkButtonShowDir = new QCommandLinkButton(tab_2);
        commandLinkButtonShowDir->setObjectName(QStringLiteral("commandLinkButtonShowDir"));
        commandLinkButtonShowDir->setGeometry(QRect(30, 520, 111, 41));
        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        GuiClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GuiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 801, 20));
        menuDisk = new QMenu(menuBar);
        menuDisk->setObjectName(QStringLiteral("menuDisk"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuStudent_File = new QMenu(menuFile);
        menuStudent_File->setObjectName(QStringLiteral("menuStudent_File"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/images/student.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuStudent_File->setIcon(icon14);
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        GuiClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(GuiClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GuiClass->setStatusBar(statusBar);
        QWidget::setTabOrder(tabWidget, vhdData);
        QWidget::setTabOrder(vhdData, datView);
        QWidget::setTabOrder(datView, fileList);
        QWidget::setTabOrder(fileList, fileData);
        QWidget::setTabOrder(fileData, fatView);
        QWidget::setTabOrder(fatView, allocationTableView);

        menuBar->addAction(menuDisk->menuAction());
        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuDisk->addAction(actionCreate_Disk);
        menuDisk->addAction(actionRecreate_Disk);
        menuDisk->addSeparator();
        menuDisk->addAction(actionMount_Disk);
        menuDisk->addAction(actionUnmount_Disk);
        menuDisk->addSeparator();
        menuDisk->addAction(actionFormat_Disk);
        menuDisk->addSeparator();
        menuDisk->addAction(actionSector);
        menuDisk->addAction(actionDefrag);
        menuDisk->addSeparator();
        menuDisk->addAction(actionExit);
        menuFile->addAction(actionUpload_File);
        menuFile->addAction(actionDownload_File);
        menuFile->addAction(actionDelete_File);
        menuFile->addSeparator();
        menuFile->addAction(menuStudent_File->menuAction());
        menuFile->addSeparator();
        menuStudent_File->addAction(actionCreate_Student_File);
        menuStudent_File->addAction(actionUpload_Studen_File);
        menuStudent_File->addAction(actionDownload_Student_File);
        menuStudent_File->addAction(actionOpen_Student_File);
        menuStudent_File->addAction(actionPrint_students_file);
        menuHelp->addAction(actionInfo);
        menuHelp->addAction(actionAbout);

        retranslateUi(GuiClass);
        QObject::connect(actionExit, SIGNAL(triggered()), GuiClass, SLOT(close()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(GuiClass);
    } // setupUi

    void retranslateUi(QMainWindow *GuiClass)
    {
        GuiClass->setWindowTitle(QApplication::translate("GuiClass", "File Management System", 0));
        actionCreate_Disk->setText(QApplication::translate("GuiClass", "Create Disk", 0));
        actionRecreate_Disk->setText(QApplication::translate("GuiClass", "Recreate Disk", 0));
        actionMount_Disk->setText(QApplication::translate("GuiClass", "Mount Disk", 0));
        actionUnmount_Disk->setText(QApplication::translate("GuiClass", "Unmount Disk", 0));
        actionFormat_Disk->setText(QApplication::translate("GuiClass", "Format Disk", 0));
        actionSector->setText(QApplication::translate("GuiClass", "Sector", 0));
        actionExit->setText(QApplication::translate("GuiClass", "Exit", 0));
        actionInfo->setText(QApplication::translate("GuiClass", "Info", 0));
        actionAbout->setText(QApplication::translate("GuiClass", "About", 0));
        actionUpload_File->setText(QApplication::translate("GuiClass", "Upload File..", 0));
        actionDownload_File->setText(QApplication::translate("GuiClass", "Download File..", 0));
        actionDelete_File->setText(QApplication::translate("GuiClass", "Delete File", 0));
        actionCreate_Student_File->setText(QApplication::translate("GuiClass", "Create students file", 0));
#ifndef QT_NO_TOOLTIP
        actionCreate_Student_File->setToolTip(QApplication::translate("GuiClass", "Create students file", 0));
#endif // QT_NO_TOOLTIP
        actionDownload_Student_File->setText(QApplication::translate("GuiClass", "Download students file", 0));
#ifndef QT_NO_TOOLTIP
        actionDownload_Student_File->setToolTip(QApplication::translate("GuiClass", "Download students file", 0));
#endif // QT_NO_TOOLTIP
        actionOpen_Student_File->setText(QApplication::translate("GuiClass", "Open students file", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen_Student_File->setToolTip(QApplication::translate("GuiClass", "Open students file", 0));
#endif // QT_NO_TOOLTIP
        actionUpload_Studen_File->setText(QApplication::translate("GuiClass", "Upload students file", 0));
#ifndef QT_NO_TOOLTIP
        actionUpload_Studen_File->setToolTip(QApplication::translate("GuiClass", "Upload students file", 0));
#endif // QT_NO_TOOLTIP
        actionDefrag->setText(QApplication::translate("GuiClass", "Defrag", 0));
        actionPrint_students_file->setText(QApplication::translate("GuiClass", "Print students file", 0));
        labelDAT->setText(QApplication::translate("GuiClass", "Disk DAT map", 0));
        labelVHD->setText(QApplication::translate("GuiClass", "Volume Header", 0));
        labelDATsum->setText(QApplication::translate("GuiClass", "No usable disk have been found...", 0));
        label->setText(QApplication::translate("GuiClass", "DAT details:", 0));
        labelDAT_2->setText(QApplication::translate("GuiClass", "In use:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("GuiClass", "Menu Disk", 0));
        labelFileList_2->setText(QApplication::translate("GuiClass", "File Header", 0));
        labelFileList->setText(QApplication::translate("GuiClass", "File List", 0));
        labelFileList_3->setText(QApplication::translate("GuiClass", "File FAT map", 0));
        labelFileList_4->setText(QApplication::translate("GuiClass", "Allocation Table", 0));
        commandLinkButtonShowDir->setText(QApplication::translate("GuiClass", "Show Dir", 0));
        commandLinkButtonShowDir->setDescription(QApplication::translate("GuiClass", "Shows the root directory", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("GuiClass", "File Menu", 0));
        menuDisk->setTitle(QApplication::translate("GuiClass", "Disk", 0));
        menuFile->setTitle(QApplication::translate("GuiClass", "File", 0));
        menuStudent_File->setTitle(QApplication::translate("GuiClass", "Student File", 0));
        menuHelp->setTitle(QApplication::translate("GuiClass", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class GuiClass: public Ui_GuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
