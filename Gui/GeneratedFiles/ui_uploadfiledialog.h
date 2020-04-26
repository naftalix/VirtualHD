/********************************************************************************
** Form generated from reading UI file 'uploadfiledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOADFILEDIALOG_H
#define UI_UPLOADFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_uploadFileDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelPath;
    QLineEdit *lineEditPath;
    QPushButton *pushButtonBrowseFile;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelRecordSize;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton30;
    QRadioButton *radioButton64;
    QRadioButton *radioButton98;
    QRadioButton *radioButton200;
    QWidget *layoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelFitOption;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *radioButtonFirstFit;
    QRadioButton *radioButtonBestFit;
    QRadioButton *radioButtonWorseFit;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonOK;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonCancel;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_6;
    QLabel *labelSetFileName;
    QLineEdit *lineEditFileName;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_7;
    QLabel *labelSetOwnerName;
    QLineEdit *lineEditOwnerName;

    void setupUi(QDialog *uploadFileDialog)
    {
        if (uploadFileDialog->objectName().isEmpty())
            uploadFileDialog->setObjectName(QStringLiteral("uploadFileDialog"));
        uploadFileDialog->resize(518, 295);
        uploadFileDialog->setBaseSize(QSize(90, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/upload.png"), QSize(), QIcon::Normal, QIcon::Off);
        uploadFileDialog->setWindowIcon(icon);
        layoutWidget = new QWidget(uploadFileDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(170, 14, 321, 51));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(30);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, -1, -1, 0);
        labelPath = new QLabel(layoutWidget);
        labelPath->setObjectName(QStringLiteral("labelPath"));
        QFont font;
        font.setPointSize(10);
        labelPath->setFont(font);

        verticalLayout_2->addWidget(labelPath);

        lineEditPath = new QLineEdit(layoutWidget);
        lineEditPath->setObjectName(QStringLiteral("lineEditPath"));
        lineEditPath->setReadOnly(true);

        verticalLayout_2->addWidget(lineEditPath);


        horizontalLayout_2->addLayout(verticalLayout_2);

        pushButtonBrowseFile = new QPushButton(layoutWidget);
        pushButtonBrowseFile->setObjectName(QStringLiteral("pushButtonBrowseFile"));
        pushButtonBrowseFile->setMinimumSize(QSize(90, 31));

        horizontalLayout_2->addWidget(pushButtonBrowseFile);

        layoutWidget_2 = new QWidget(uploadFileDialog);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(20, 10, 116, 121));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        labelRecordSize = new QLabel(layoutWidget_2);
        labelRecordSize->setObjectName(QStringLiteral("labelRecordSize"));
        labelRecordSize->setFont(font);

        verticalLayout_3->addWidget(labelRecordSize);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        radioButton30 = new QRadioButton(layoutWidget_2);
        radioButton30->setObjectName(QStringLiteral("radioButton30"));

        verticalLayout->addWidget(radioButton30);

        radioButton64 = new QRadioButton(layoutWidget_2);
        radioButton64->setObjectName(QStringLiteral("radioButton64"));

        verticalLayout->addWidget(radioButton64);

        radioButton98 = new QRadioButton(layoutWidget_2);
        radioButton98->setObjectName(QStringLiteral("radioButton98"));

        verticalLayout->addWidget(radioButton98);

        radioButton200 = new QRadioButton(layoutWidget_2);
        radioButton200->setObjectName(QStringLiteral("radioButton200"));

        verticalLayout->addWidget(radioButton200);


        verticalLayout_3->addLayout(verticalLayout);

        layoutWidget_4 = new QWidget(uploadFileDialog);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(20, 160, 116, 101));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_4);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        labelFitOption = new QLabel(layoutWidget_4);
        labelFitOption->setObjectName(QStringLiteral("labelFitOption"));
        labelFitOption->setFont(font);

        verticalLayout_4->addWidget(labelFitOption);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        radioButtonFirstFit = new QRadioButton(layoutWidget_4);
        radioButtonFirstFit->setObjectName(QStringLiteral("radioButtonFirstFit"));

        verticalLayout_5->addWidget(radioButtonFirstFit);

        radioButtonBestFit = new QRadioButton(layoutWidget_4);
        radioButtonBestFit->setObjectName(QStringLiteral("radioButtonBestFit"));

        verticalLayout_5->addWidget(radioButtonBestFit);

        radioButtonWorseFit = new QRadioButton(layoutWidget_4);
        radioButtonWorseFit->setObjectName(QStringLiteral("radioButtonWorseFit"));

        verticalLayout_5->addWidget(radioButtonWorseFit);


        verticalLayout_4->addLayout(verticalLayout_5);

        layoutWidget_3 = new QWidget(uploadFileDialog);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(190, 200, 271, 61));
        horizontalLayout = new QHBoxLayout(layoutWidget_3);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Fixed);

        horizontalLayout->addItem(verticalSpacer);

        pushButtonOK = new QPushButton(layoutWidget_3);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setMinimumSize(QSize(110, 35));

        horizontalLayout->addWidget(pushButtonOK);

        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonCancel = new QPushButton(layoutWidget_3);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setMinimumSize(QSize(110, 35));

        horizontalLayout->addWidget(pushButtonCancel);

        layoutWidget1 = new QWidget(uploadFileDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(170, 110, 141, 44));
        verticalLayout_6 = new QVBoxLayout(layoutWidget1);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        labelSetFileName = new QLabel(layoutWidget1);
        labelSetFileName->setObjectName(QStringLiteral("labelSetFileName"));
        labelSetFileName->setFont(font);

        verticalLayout_6->addWidget(labelSetFileName);

        lineEditFileName = new QLineEdit(layoutWidget1);
        lineEditFileName->setObjectName(QStringLiteral("lineEditFileName"));

        verticalLayout_6->addWidget(lineEditFileName);

        layoutWidget2 = new QWidget(uploadFileDialog);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(350, 110, 141, 44));
        verticalLayout_7 = new QVBoxLayout(layoutWidget2);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        labelSetOwnerName = new QLabel(layoutWidget2);
        labelSetOwnerName->setObjectName(QStringLiteral("labelSetOwnerName"));
        labelSetOwnerName->setFont(font);

        verticalLayout_7->addWidget(labelSetOwnerName);

        lineEditOwnerName = new QLineEdit(layoutWidget2);
        lineEditOwnerName->setObjectName(QStringLiteral("lineEditOwnerName"));

        verticalLayout_7->addWidget(lineEditOwnerName);

#ifndef QT_NO_SHORTCUT
        labelPath->setBuddy(lineEditPath);
        labelSetFileName->setBuddy(lineEditPath);
        labelSetOwnerName->setBuddy(lineEditPath);
#endif // QT_NO_SHORTCUT

        retranslateUi(uploadFileDialog);
        QObject::connect(pushButtonOK, SIGNAL(clicked()), uploadFileDialog, SLOT(accept()));
        QObject::connect(pushButtonCancel, SIGNAL(clicked()), uploadFileDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(uploadFileDialog);
    } // setupUi

    void retranslateUi(QDialog *uploadFileDialog)
    {
        uploadFileDialog->setWindowTitle(QApplication::translate("uploadFileDialog", "Upload file", 0));
        labelPath->setText(QApplication::translate("uploadFileDialog", "Path:", 0));
        pushButtonBrowseFile->setText(QApplication::translate("uploadFileDialog", "Browse", 0));
        labelRecordSize->setText(QApplication::translate("uploadFileDialog", "Choose record size:", 0));
        radioButton30->setText(QApplication::translate("uploadFileDialog", "30", 0));
        radioButton64->setText(QApplication::translate("uploadFileDialog", "64", 0));
        radioButton98->setText(QApplication::translate("uploadFileDialog", "98", 0));
        radioButton200->setText(QApplication::translate("uploadFileDialog", "200", 0));
        labelFitOption->setText(QApplication::translate("uploadFileDialog", "Choose Fit option:", 0));
        radioButtonFirstFit->setText(QApplication::translate("uploadFileDialog", "First Fit", 0));
        radioButtonBestFit->setText(QApplication::translate("uploadFileDialog", "Best Fit", 0));
        radioButtonWorseFit->setText(QApplication::translate("uploadFileDialog", "Worse Fit", 0));
        pushButtonOK->setText(QApplication::translate("uploadFileDialog", "OK", 0));
        pushButtonCancel->setText(QApplication::translate("uploadFileDialog", "Cancel", 0));
        labelSetFileName->setText(QApplication::translate("uploadFileDialog", "Set file name:", 0));
        labelSetOwnerName->setText(QApplication::translate("uploadFileDialog", "Set owner name:", 0));
    } // retranslateUi

};

namespace Ui {
    class uploadFileDialog: public Ui_uploadFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOADFILEDIALOG_H
