/********************************************************************************
** Form generated from reading UI file 'sectordialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECTORDIALOG_H
#define UI_SECTORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SectorDialog
{
public:
    QFrame *frame;
    QPushButton *readSectorButton;
    QPushButton *writeSectorButton;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelSectorNumber;
    QSpinBox *spinBox;
    QPushButton *selectSectorButton;
    QLabel *labelDataSector;
    QTextEdit *textEdit;

    void setupUi(QDialog *SectorDialog)
    {
        if (SectorDialog->objectName().isEmpty())
            SectorDialog->setObjectName(QStringLiteral("SectorDialog"));
        SectorDialog->resize(433, 277);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/sector.png"), QSize(), QIcon::Normal, QIcon::Off);
        SectorDialog->setWindowIcon(icon);
        frame = new QFrame(SectorDialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(110, 210, 281, 41));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        readSectorButton = new QPushButton(frame);
        readSectorButton->setObjectName(QStringLiteral("readSectorButton"));
        readSectorButton->setGeometry(QRect(10, 0, 111, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(readSectorButton->sizePolicy().hasHeightForWidth());
        readSectorButton->setSizePolicy(sizePolicy1);
        writeSectorButton = new QPushButton(frame);
        writeSectorButton->setObjectName(QStringLiteral("writeSectorButton"));
        writeSectorButton->setGeometry(QRect(170, 0, 111, 41));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(writeSectorButton->sizePolicy().hasHeightForWidth());
        writeSectorButton->setSizePolicy(sizePolicy2);
        horizontalLayoutWidget = new QWidget(SectorDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 391, 44));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setSpacing(22);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        labelSectorNumber = new QLabel(horizontalLayoutWidget);
        labelSectorNumber->setObjectName(QStringLiteral("labelSectorNumber"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelSectorNumber->sizePolicy().hasHeightForWidth());
        labelSectorNumber->setSizePolicy(sizePolicy3);
        QFont font;
        font.setPointSize(10);
        labelSectorNumber->setFont(font);

        horizontalLayout_2->addWidget(labelSectorNumber);

        spinBox = new QSpinBox(horizontalLayoutWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        QSizePolicy sizePolicy4(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy4);
        spinBox->setMinimumSize(QSize(100, 0));
        spinBox->setMaximumSize(QSize(90, 16777215));
        spinBox->setReadOnly(false);
        spinBox->setMaximum(3199);

        horizontalLayout_2->addWidget(spinBox);

        selectSectorButton = new QPushButton(horizontalLayoutWidget);
        selectSectorButton->setObjectName(QStringLiteral("selectSectorButton"));
        sizePolicy3.setHeightForWidth(selectSectorButton->sizePolicy().hasHeightForWidth());
        selectSectorButton->setSizePolicy(sizePolicy3);
        selectSectorButton->setMinimumSize(QSize(90, 0));

        horizontalLayout_2->addWidget(selectSectorButton);

        horizontalLayout_2->setStretch(0, 20);
        horizontalLayout_2->setStretch(2, 20);
        labelDataSector = new QLabel(SectorDialog);
        labelDataSector->setObjectName(QStringLiteral("labelDataSector"));
        labelDataSector->setGeometry(QRect(20, 70, 91, 16));
        labelDataSector->setFont(font);
        textEdit = new QTextEdit(SectorDialog);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(120, 70, 271, 121));

        retranslateUi(SectorDialog);

        QMetaObject::connectSlotsByName(SectorDialog);
    } // setupUi

    void retranslateUi(QDialog *SectorDialog)
    {
        SectorDialog->setWindowTitle(QApplication::translate("SectorDialog", "Sector", 0));
        readSectorButton->setText(QApplication::translate("SectorDialog", "Read Sector", 0));
        writeSectorButton->setText(QApplication::translate("SectorDialog", "Write Sector", 0));
        labelSectorNumber->setText(QApplication::translate("SectorDialog", "Enter Sector Number:", 0));
        selectSectorButton->setText(QApplication::translate("SectorDialog", "Select", 0));
        labelDataSector->setText(QApplication::translate("SectorDialog", "Data in Sector:", 0));
    } // retranslateUi

};

namespace Ui {
    class SectorDialog: public Ui_SectorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECTORDIALOG_H
