/********************************************************************************
** Form generated from reading UI file 'GUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUIClass
{
public:
    QWidget *centralWidget;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox;
    QCheckBox *cb_deleteComments;
    QCheckBox *cb_changeLoops;
    QCheckBox *cb_ChangeVariables;
    QGroupBox *groupBox_2;
    QSpinBox *sp_AmountVariables;
    QSpinBox *sp_AmountCodes;
    QLabel *label_2;
    QLabel *label_3;
    QCheckBox *cb_AddJunk;
    QCheckBox *cb_JunkerSum;
    QCheckBox *cb_JunkerSub;
    QCheckBox *cb_JunkerMul;
    QCheckBox *cb_JunkerConnected;
    QCheckBox *cb_JunkerSemiConnected;
    QCheckBox *cb_JunkerNonConnected;
    QCheckBox *cb_JunkerInc;
    QCheckBox *cb_DeleteEnters;
    QGroupBox *groupBox_3;
    QCheckBox *cb_Encryption;
    QCheckBox *cb_EncToFile;
    QCheckBox *cb_EncOnlyFor;
    QCheckBox *cb_DeleteSpace;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *b_LoadFile;
    QLabel *label;
    QLabel *fileNameLabelIn;
    QLabel *fileNameLabelOut;
    QPushButton *b_SaveFile;
    QLabel *label_4;
    QPushButton *b_openFile;
    QPushButton *pushButton;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *GUIClass)
    {
        if (GUIClass->objectName().isEmpty())
            GUIClass->setObjectName(QString::fromUtf8("GUIClass"));
        GUIClass->resize(900, 430);
        GUIClass->setMinimumSize(QSize(900, 430));
        GUIClass->setMaximumSize(QSize(900, 430));
        centralWidget = new QWidget(GUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 60, 631, 192));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(650, 20, 241, 361));
        cb_deleteComments = new QCheckBox(groupBox);
        cb_deleteComments->setObjectName(QString::fromUtf8("cb_deleteComments"));
        cb_deleteComments->setGeometry(QRect(10, 20, 209, 17));
        cb_changeLoops = new QCheckBox(groupBox);
        cb_changeLoops->setObjectName(QString::fromUtf8("cb_changeLoops"));
        cb_changeLoops->setGeometry(QRect(10, 40, 209, 17));
        cb_ChangeVariables = new QCheckBox(groupBox);
        cb_ChangeVariables->setObjectName(QString::fromUtf8("cb_ChangeVariables"));
        cb_ChangeVariables->setGeometry(QRect(10, 260, 209, 17));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 60, 221, 191));
        sp_AmountVariables = new QSpinBox(groupBox_2);
        sp_AmountVariables->setObjectName(QString::fromUtf8("sp_AmountVariables"));
        sp_AmountVariables->setEnabled(false);
        sp_AmountVariables->setGeometry(QRect(170, 20, 42, 22));
        sp_AmountVariables->setMinimum(1);
        sp_AmountCodes = new QSpinBox(groupBox_2);
        sp_AmountCodes->setObjectName(QString::fromUtf8("sp_AmountCodes"));
        sp_AmountCodes->setEnabled(false);
        sp_AmountCodes->setGeometry(QRect(170, 50, 42, 22));
        sp_AmountCodes->setMinimum(1);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 20, 101, 16));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 50, 161, 16));
        cb_AddJunk = new QCheckBox(groupBox_2);
        cb_AddJunk->setObjectName(QString::fromUtf8("cb_AddJunk"));
        cb_AddJunk->setGeometry(QRect(0, 0, 209, 17));
        cb_JunkerSum = new QCheckBox(groupBox_2);
        cb_JunkerSum->setObjectName(QString::fromUtf8("cb_JunkerSum"));
        cb_JunkerSum->setEnabled(false);
        cb_JunkerSum->setGeometry(QRect(10, 80, 70, 17));
        cb_JunkerSum->setChecked(true);
        cb_JunkerSub = new QCheckBox(groupBox_2);
        cb_JunkerSub->setObjectName(QString::fromUtf8("cb_JunkerSub"));
        cb_JunkerSub->setEnabled(false);
        cb_JunkerSub->setGeometry(QRect(70, 80, 70, 17));
        cb_JunkerSub->setChecked(true);
        cb_JunkerMul = new QCheckBox(groupBox_2);
        cb_JunkerMul->setObjectName(QString::fromUtf8("cb_JunkerMul"));
        cb_JunkerMul->setEnabled(false);
        cb_JunkerMul->setGeometry(QRect(140, 80, 70, 17));
        cb_JunkerMul->setChecked(true);
        cb_JunkerConnected = new QCheckBox(groupBox_2);
        cb_JunkerConnected->setObjectName(QString::fromUtf8("cb_JunkerConnected"));
        cb_JunkerConnected->setEnabled(false);
        cb_JunkerConnected->setGeometry(QRect(10, 100, 191, 17));
        cb_JunkerConnected->setChecked(true);
        cb_JunkerConnected->setTristate(false);
        cb_JunkerSemiConnected = new QCheckBox(groupBox_2);
        cb_JunkerSemiConnected->setObjectName(QString::fromUtf8("cb_JunkerSemiConnected"));
        cb_JunkerSemiConnected->setEnabled(false);
        cb_JunkerSemiConnected->setGeometry(QRect(10, 120, 191, 17));
        cb_JunkerSemiConnected->setChecked(true);
        cb_JunkerNonConnected = new QCheckBox(groupBox_2);
        cb_JunkerNonConnected->setObjectName(QString::fromUtf8("cb_JunkerNonConnected"));
        cb_JunkerNonConnected->setEnabled(false);
        cb_JunkerNonConnected->setGeometry(QRect(10, 140, 181, 17));
        cb_JunkerNonConnected->setChecked(true);
        cb_JunkerInc = new QCheckBox(groupBox_2);
        cb_JunkerInc->setObjectName(QString::fromUtf8("cb_JunkerInc"));
        cb_JunkerInc->setEnabled(false);
        cb_JunkerInc->setGeometry(QRect(10, 160, 201, 17));
        cb_JunkerInc->setChecked(true);
        cb_DeleteEnters = new QCheckBox(groupBox);
        cb_DeleteEnters->setObjectName(QString::fromUtf8("cb_DeleteEnters"));
        cb_DeleteEnters->setEnabled(false);
        cb_DeleteEnters->setGeometry(QRect(10, 320, 221, 17));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 280, 221, 41));
        cb_Encryption = new QCheckBox(groupBox_3);
        cb_Encryption->setObjectName(QString::fromUtf8("cb_Encryption"));
        cb_Encryption->setGeometry(QRect(0, 0, 209, 17));
        cb_EncToFile = new QCheckBox(groupBox_3);
        cb_EncToFile->setObjectName(QString::fromUtf8("cb_EncToFile"));
        cb_EncToFile->setEnabled(false);
        cb_EncToFile->setGeometry(QRect(0, 20, 70, 17));
        cb_EncOnlyFor = new QCheckBox(groupBox_3);
        cb_EncOnlyFor->setObjectName(QString::fromUtf8("cb_EncOnlyFor"));
        cb_EncOnlyFor->setEnabled(false);
        cb_EncOnlyFor->setGeometry(QRect(99, 20, 101, 20));
        cb_DeleteSpace = new QCheckBox(groupBox);
        cb_DeleteSpace->setObjectName(QString::fromUtf8("cb_DeleteSpace"));
        cb_DeleteSpace->setEnabled(true);
        cb_DeleteSpace->setGeometry(QRect(10, 340, 221, 17));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setGeometry(QRect(30, 20, 210, 20));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(410, 20, 210, 20));
        b_LoadFile = new QPushButton(centralWidget);
        b_LoadFile->setObjectName(QString::fromUtf8("b_LoadFile"));
        b_LoadFile->setGeometry(QRect(240, 20, 20, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(380, 20, 21, 20));
        fileNameLabelIn = new QLabel(centralWidget);
        fileNameLabelIn->setObjectName(QString::fromUtf8("fileNameLabelIn"));
        fileNameLabelIn->setGeometry(QRect(10, 260, 301, 16));
        fileNameLabelOut = new QLabel(centralWidget);
        fileNameLabelOut->setObjectName(QString::fromUtf8("fileNameLabelOut"));
        fileNameLabelOut->setGeometry(QRect(10, 280, 301, 16));
        b_SaveFile = new QPushButton(centralWidget);
        b_SaveFile->setObjectName(QString::fromUtf8("b_SaveFile"));
        b_SaveFile->setGeometry(QRect(620, 20, 20, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 20, 12, 20));
        b_openFile = new QPushButton(centralWidget);
        b_openFile->setObjectName(QString::fromUtf8("b_openFile"));
        b_openFile->setEnabled(false);
        b_openFile->setGeometry(QRect(560, 260, 75, 23));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(250, 310, 221, 61));
        GUIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GUIClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(GUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 900, 21));
        GUIClass->setMenuBar(menuBar);

        retranslateUi(GUIClass);

        QMetaObject::connectSlotsByName(GUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *GUIClass)
    {
        GUIClass->setWindowTitle(QCoreApplication::translate("GUIClass", "obfCoder", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GUIClass", "Settings", nullptr));
        cb_deleteComments->setText(QCoreApplication::translate("GUIClass", "Delete comments", nullptr));
        cb_changeLoops->setText(QCoreApplication::translate("GUIClass", "Change loops", nullptr));
        cb_ChangeVariables->setText(QCoreApplication::translate("GUIClass", "Rename variables", nullptr));
        groupBox_2->setTitle(QString());
        label_2->setText(QCoreApplication::translate("GUIClass", "Number of variables", nullptr));
        label_3->setText(QCoreApplication::translate("GUIClass", "Number of methods per variable", nullptr));
        cb_AddJunk->setText(QCoreApplication::translate("GUIClass", "Add Additional code", nullptr));
        cb_JunkerSum->setText(QCoreApplication::translate("GUIClass", "Sum", nullptr));
        cb_JunkerSub->setText(QCoreApplication::translate("GUIClass", "Difference", nullptr));
        cb_JunkerMul->setText(QCoreApplication::translate("GUIClass", "Multiply", nullptr));
        cb_JunkerConnected->setText(QCoreApplication::translate("GUIClass", "Loop For connected", nullptr));
        cb_JunkerSemiConnected->setText(QCoreApplication::translate("GUIClass", "Loop For semi-connected", nullptr));
        cb_JunkerNonConnected->setText(QCoreApplication::translate("GUIClass", "Loop For unconnected", nullptr));
        cb_JunkerInc->setText(QCoreApplication::translate("GUIClass", "Incrementation", nullptr));
        cb_DeleteEnters->setText(QCoreApplication::translate("GUIClass", "Delete transitions to new line", nullptr));
        groupBox_3->setTitle(QString());
        cb_Encryption->setText(QCoreApplication::translate("GUIClass", "Encryption", nullptr));
        cb_EncToFile->setText(QCoreApplication::translate("GUIClass", "To file", nullptr));
        cb_EncOnlyFor->setText(QCoreApplication::translate("GUIClass", "Only loops for", nullptr));
        cb_DeleteSpace->setText(QCoreApplication::translate("GUIClass", "Delete unnecessary spaces", nullptr));
        lineEdit->setText(QString());
        lineEdit_2->setText(QString());
        b_LoadFile->setText(QCoreApplication::translate("GUIClass", "F", nullptr));
        label->setText(QCoreApplication::translate("GUIClass", "Out", nullptr));
        fileNameLabelIn->setText(QCoreApplication::translate("GUIClass", "Input File Name:", nullptr));
        fileNameLabelOut->setText(QCoreApplication::translate("GUIClass", "Output File Name:", nullptr));
        b_SaveFile->setText(QCoreApplication::translate("GUIClass", "F", nullptr));
        label_4->setText(QCoreApplication::translate("GUIClass", "In", nullptr));
        b_openFile->setText(QCoreApplication::translate("GUIClass", "Open", nullptr));
        pushButton->setText(QCoreApplication::translate("GUIClass", "Execute", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUIClass: public Ui_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
