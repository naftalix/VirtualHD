/********************************************************************************
** Form generated from reading UI file 'seekrecdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEEKRECDIALOG_H
#define UI_SEEKRECDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SeekRecDialog
{
public:
    QSpinBox *spinBox;
    QLabel *label_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButtonBegin;
    QRadioButton *radioButtonCur;
    QRadioButton *radioButtonEnd;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SeekRecDialog)
    {
        if (SeekRecDialog->objectName().isEmpty())
            SeekRecDialog->setObjectName(QStringLiteral("SeekRecDialog"));
        SeekRecDialog->resize(286, 185);
        SeekRecDialog->setMaximumSize(QSize(287, 185));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        SeekRecDialog->setWindowIcon(icon);
        spinBox = new QSpinBox(SeekRecDialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(190, 20, 51, 22));
        spinBox->setMinimum(-99);
        label_2 = new QLabel(SeekRecDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 60, 101, 21));
        layoutWidget = new QWidget(SeekRecDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 80, 251, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        radioButtonBegin = new QRadioButton(layoutWidget);
        radioButtonBegin->setObjectName(QStringLiteral("radioButtonBegin"));

        horizontalLayout->addWidget(radioButtonBegin);

        radioButtonCur = new QRadioButton(layoutWidget);
        radioButtonCur->setObjectName(QStringLiteral("radioButtonCur"));

        horizontalLayout->addWidget(radioButtonCur);

        radioButtonEnd = new QRadioButton(layoutWidget);
        radioButtonEnd->setObjectName(QStringLiteral("radioButtonEnd"));

        horizontalLayout->addWidget(radioButtonEnd);

        label = new QLabel(SeekRecDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 141, 16));
        buttonBox = new QDialogButtonBox(SeekRecDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(70, 130, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(SeekRecDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), SeekRecDialog, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), SeekRecDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(SeekRecDialog);
    } // setupUi

    void retranslateUi(QDialog *SeekRecDialog)
    {
        SeekRecDialog->setWindowTitle(QApplication::translate("SeekRecDialog", "Seek Dialog", 0));
        label_2->setText(QApplication::translate("SeekRecDialog", "Choose seek place:", 0));
        radioButtonBegin->setText(QApplication::translate("SeekRecDialog", "Begin", 0));
        radioButtonCur->setText(QApplication::translate("SeekRecDialog", "Current", 0));
        radioButtonEnd->setText(QApplication::translate("SeekRecDialog", "End", 0));
        label->setText(QApplication::translate("SeekRecDialog", "Enter seek records number:", 0));
    } // retranslateUi

};

namespace Ui {
    class SeekRecDialog: public Ui_SeekRecDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEEKRECDIALOG_H
