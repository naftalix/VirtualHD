/********************************************************************************
** Form generated from reading UI file 'studentrecordsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENTRECORDSDIALOG_H
#define UI_STUDENTRECORDSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StudentRecordsDialog
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *labelId;
    QLineEdit *lineEditId;
    QLabel *labelName;
    QLineEdit *lineEditName;
    QLabel *labelAddress;
    QPlainTextEdit *plainTextAddress;
    QLabel *labelAverage;
    QLineEdit *lineEditAverage;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *buttonSeek;
    QPushButton *buttonWrite;
    QPushButton *buttonPrev;
    QPushButton *pushButtonAddRecord;
    QPushButton *buttonDelete;
    QPushButton *buttonNext;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *StudentRecordsDialog)
    {
        if (StudentRecordsDialog->objectName().isEmpty())
            StudentRecordsDialog->setObjectName(QStringLiteral("StudentRecordsDialog"));
        StudentRecordsDialog->resize(447, 396);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        StudentRecordsDialog->setWindowIcon(icon);
        formLayoutWidget = new QWidget(StudentRecordsDialog);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(20, 20, 381, 233));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        labelId = new QLabel(formLayoutWidget);
        labelId->setObjectName(QStringLiteral("labelId"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelId);

        lineEditId = new QLineEdit(formLayoutWidget);
        lineEditId->setObjectName(QStringLiteral("lineEditId"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditId);

        labelName = new QLabel(formLayoutWidget);
        labelName->setObjectName(QStringLiteral("labelName"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelName);

        lineEditName = new QLineEdit(formLayoutWidget);
        lineEditName->setObjectName(QStringLiteral("lineEditName"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditName);

        labelAddress = new QLabel(formLayoutWidget);
        labelAddress->setObjectName(QStringLiteral("labelAddress"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelAddress);

        plainTextAddress = new QPlainTextEdit(formLayoutWidget);
        plainTextAddress->setObjectName(QStringLiteral("plainTextAddress"));

        formLayout->setWidget(2, QFormLayout::FieldRole, plainTextAddress);

        labelAverage = new QLabel(formLayoutWidget);
        labelAverage->setObjectName(QStringLiteral("labelAverage"));

        formLayout->setWidget(3, QFormLayout::LabelRole, labelAverage);

        lineEditAverage = new QLineEdit(formLayoutWidget);
        lineEditAverage->setObjectName(QStringLiteral("lineEditAverage"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditAverage);

        layoutWidget = new QWidget(StudentRecordsDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(100, 280, 241, 112));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        buttonSeek = new QPushButton(layoutWidget);
        buttonSeek->setObjectName(QStringLiteral("buttonSeek"));

        gridLayout->addWidget(buttonSeek, 1, 0, 1, 1);

        buttonWrite = new QPushButton(layoutWidget);
        buttonWrite->setObjectName(QStringLiteral("buttonWrite"));

        gridLayout->addWidget(buttonWrite, 0, 1, 1, 1);

        buttonPrev = new QPushButton(layoutWidget);
        buttonPrev->setObjectName(QStringLiteral("buttonPrev"));

        gridLayout->addWidget(buttonPrev, 0, 0, 1, 1);

        pushButtonAddRecord = new QPushButton(layoutWidget);
        pushButtonAddRecord->setObjectName(QStringLiteral("pushButtonAddRecord"));

        gridLayout->addWidget(pushButtonAddRecord, 1, 2, 1, 1);

        buttonDelete = new QPushButton(layoutWidget);
        buttonDelete->setObjectName(QStringLiteral("buttonDelete"));

        gridLayout->addWidget(buttonDelete, 1, 1, 1, 1);

        buttonNext = new QPushButton(layoutWidget);
        buttonNext->setObjectName(QStringLiteral("buttonNext"));

        gridLayout->addWidget(buttonNext, 0, 2, 1, 1);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);

#ifndef QT_NO_SHORTCUT
        labelId->setBuddy(lineEditId);
        labelName->setBuddy(lineEditName);
        labelAddress->setBuddy(plainTextAddress);
        labelAverage->setBuddy(lineEditAverage);
#endif // QT_NO_SHORTCUT

        retranslateUi(StudentRecordsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), StudentRecordsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), StudentRecordsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(StudentRecordsDialog);
    } // setupUi

    void retranslateUi(QDialog *StudentRecordsDialog)
    {
        StudentRecordsDialog->setWindowTitle(QApplication::translate("StudentRecordsDialog", "Open File", 0));
        labelId->setText(QApplication::translate("StudentRecordsDialog", "ID", 0));
        labelName->setText(QApplication::translate("StudentRecordsDialog", "Name", 0));
        labelAddress->setText(QApplication::translate("StudentRecordsDialog", "Address", 0));
        labelAverage->setText(QApplication::translate("StudentRecordsDialog", "Average", 0));
        buttonSeek->setText(QApplication::translate("StudentRecordsDialog", "Seek", 0));
        buttonWrite->setText(QApplication::translate("StudentRecordsDialog", "Write", 0));
        buttonPrev->setText(QApplication::translate("StudentRecordsDialog", "<-", 0));
        pushButtonAddRecord->setText(QApplication::translate("StudentRecordsDialog", "Add Record", 0));
        buttonDelete->setText(QApplication::translate("StudentRecordsDialog", "Delete", 0));
        buttonNext->setText(QApplication::translate("StudentRecordsDialog", "->", 0));
    } // retranslateUi

};

namespace Ui {
    class StudentRecordsDialog: public Ui_StudentRecordsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTRECORDSDIALOG_H
