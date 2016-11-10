/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>
#include "GUI/glcanvas.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionTrimesh;
    QAction *actionSkel;
    QAction *actionWindow;
    QAction *actionDCEL;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    GLcanvas *glCanvas;
    QMenuBar *menuBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QToolBox *toolBox;
    QWidget *page_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(897, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setBaseSize(QSize(800, 600));
        actionTrimesh = new QAction(MainWindow);
        actionTrimesh->setObjectName(QStringLiteral("actionTrimesh"));
        actionSkel = new QAction(MainWindow);
        actionSkel->setObjectName(QStringLiteral("actionSkel"));
        actionWindow = new QAction(MainWindow);
        actionWindow->setObjectName(QStringLiteral("actionWindow"));
        actionDCEL = new QAction(MainWindow);
        actionDCEL->setObjectName(QStringLiteral("actionDCEL"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        glCanvas = new GLcanvas(centralWidget);
        glCanvas->setObjectName(QStringLiteral("glCanvas"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(glCanvas->sizePolicy().hasHeightForWidth());
        glCanvas->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(glCanvas);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 897, 25));
        MainWindow->setMenuBar(menuBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        sizePolicy.setHeightForWidth(dockWidget->sizePolicy().hasHeightForWidth());
        dockWidget->setSizePolicy(sizePolicy);
        dockWidget->setMinimumSize(QSize(486, 233));
        dockWidget->setAutoFillBackground(false);
        dockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidget->setAllowedAreas(Qt::NoDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        dockWidgetContents->setLayoutDirection(Qt::RightToLeft);
        horizontalLayout_2 = new QHBoxLayout(dockWidgetContents);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        scrollArea = new QScrollArea(dockWidgetContents);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setMinimumSize(QSize(150, 0));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 148, 530));
        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_2->addWidget(scrollArea);

        toolBox = new QToolBox(dockWidgetContents);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setMinimumSize(QSize(312, 0));
        toolBox->setLayoutDirection(Qt::LeftToRight);
        toolBox->setFrameShape(QFrame::StyledPanel);
        toolBox->setFrameShadow(QFrame::Raised);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 310, 499));
        toolBox->addItem(page_2, QStringLiteral("Page 2"));
        scrollArea->raise();

        horizontalLayout_2->addWidget(toolBox);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        actionTrimesh->setText(QApplication::translate("MainWindow", "Trimesh", 0));
        actionSkel->setText(QApplication::translate("MainWindow", "Skel", 0));
        actionWindow->setText(QApplication::translate("MainWindow", "Window", 0));
        actionDCEL->setText(QApplication::translate("MainWindow", "DCEL", 0));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWindow", "Page 2", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
