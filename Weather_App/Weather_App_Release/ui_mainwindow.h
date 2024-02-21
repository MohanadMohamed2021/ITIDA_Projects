/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(666, 538);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 661, 521));
        groupBox->setStyleSheet(QString::fromUtf8("background: brown;\n"
"font: 15pt \"Segoe UI\";"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 40, 191, 181));
        label_2->setStyleSheet(QString::fromUtf8("background-color: green\n"
";\n"
""));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(460, 40, 201, 181));
        label_3->setStyleSheet(QString::fromUtf8("background-color: green;"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(240, 270, 181, 31));
        pushButton->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Segoe Script\";\n"
"background : white;"));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(340, 360, 301, 131));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("background: gray;"));

        gridLayout_2->addWidget(label_11, 0, 0, 1, 1);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName("label_12");
        label_12->setStyleSheet(QString::fromUtf8("background : green;"));

        gridLayout_2->addWidget(label_12, 0, 1, 1, 1);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName("label_13");
        label_13->setStyleSheet(QString::fromUtf8("background: gray;"));

        gridLayout_2->addWidget(label_13, 1, 0, 1, 1);

        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName("label_14");
        label_14->setStyleSheet(QString::fromUtf8("background : green;"));

        gridLayout_2->addWidget(label_14, 1, 1, 1, 1);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName("label_15");
        label_15->setStyleSheet(QString::fromUtf8("background: gray;"));

        gridLayout_2->addWidget(label_15, 2, 0, 1, 1);

        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName("label_16");
        label_16->setStyleSheet(QString::fromUtf8("background : green;"));

        gridLayout_2->addWidget(label_16, 2, 1, 1, 1);

        label_19 = new QLabel(layoutWidget);
        label_19->setObjectName("label_19");
        label_19->setStyleSheet(QString::fromUtf8("background: gray;"));

        gridLayout_2->addWidget(label_19, 3, 0, 1, 1);

        label_20 = new QLabel(layoutWidget);
        label_20->setObjectName("label_20");
        label_20->setStyleSheet(QString::fromUtf8("background : green;"));

        gridLayout_2->addWidget(label_20, 3, 1, 1, 1);

        label_21 = new QLabel(groupBox);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(200, 310, 251, 31));
        label_21->setStyleSheet(QString::fromUtf8("background : gray;"));
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(120, 230, 421, 35));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName("label_4");

        horizontalLayout->addWidget(label_4);

        lineEdit = new QLineEdit(layoutWidget1);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Unispace\";\n"
"color: black;\n"
""));

        horizontalLayout->addWidget(lineEdit);

        layoutWidget2 = new QWidget(groupBox);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(20, 360, 301, 131));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("background: gray;"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("background : green;"));

        gridLayout->addWidget(label_6, 0, 1, 1, 1);

        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("background: gray;"));

        gridLayout->addWidget(label_7, 1, 0, 1, 1);

        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("background : green;"));

        gridLayout->addWidget(label_8, 1, 1, 1, 1);

        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("background: gray;"));

        gridLayout->addWidget(label_9, 2, 0, 1, 1);

        label_10 = new QLabel(layoutWidget2);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("background : green;"));

        gridLayout->addWidget(label_10, 2, 1, 1, 1);

        label_17 = new QLabel(layoutWidget2);
        label_17->setObjectName("label_17");
        label_17->setStyleSheet(QString::fromUtf8("background: gray;"));

        gridLayout->addWidget(label_17, 3, 0, 1, 1);

        label_18 = new QLabel(layoutWidget2);
        label_18->setObjectName("label_18");
        label_18->setStyleSheet(QString::fromUtf8("background : green;"));

        gridLayout->addWidget(label_18, 3, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(190, 40, 271, 181));
        label->setScaledContents(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 666, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Weather App", nullptr));
        label_2->setText(QString());
        label_3->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "start", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Wind_Speed</span></p></body></html>", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; color:#ffffff;\">Blank</span></p></body></html>", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Description</span></p></body></html>", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; color:#ffffff;\">Blank</span></p></body></html>", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Pressure</span></p></body></html>", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; color:#ffffff;\">Blank</span></p></body></html>", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Humidity</span></p></body></html>", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; color:#ffffff;\">Blank</span></p></body></html>", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:700; color:#ffaa00;\">Information</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; font-style:italic; color:#ffffff;\">Enter the city :-</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Temperature</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; color:#ffffff;\">Blank</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Feels_like</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; color:#ffffff;\">Blank</span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Temp_Min</span></p></body></html>", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; color:#ffffff;\">Blank</span></p></body></html>", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Temp_Max</span></p></body></html>", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; color:#ffffff;\">Blank</span></p></body></html>", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
