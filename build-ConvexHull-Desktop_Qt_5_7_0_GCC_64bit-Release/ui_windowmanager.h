/********************************************************************************
** Form generated from reading UI file 'windowmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWMANAGER_H
#define UI_WINDOWMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_WindowManager
{
public:
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QPushButton *backgroundColorButton;
    QPushButton *saveSnapshotButton;
    QCheckBox *fullScreenCheckBox;
    QCheckBox *showAxisCheckBox;

    void setupUi(QFrame *WindowManager)
    {
        if (WindowManager->objectName().isEmpty())
            WindowManager->setObjectName(QStringLiteral("WindowManager"));
        WindowManager->resize(300, 147);
        WindowManager->setFrameShape(QFrame::NoFrame);
        WindowManager->setFrameShadow(QFrame::Raised);
        frame = new QFrame(WindowManager);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 281, 130));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        backgroundColorButton = new QPushButton(frame);
        backgroundColorButton->setObjectName(QStringLiteral("backgroundColorButton"));
        QFont font;
        font.setPointSize(10);
        backgroundColorButton->setFont(font);

        verticalLayout->addWidget(backgroundColorButton);

        saveSnapshotButton = new QPushButton(frame);
        saveSnapshotButton->setObjectName(QStringLiteral("saveSnapshotButton"));

        verticalLayout->addWidget(saveSnapshotButton);

        fullScreenCheckBox = new QCheckBox(frame);
        fullScreenCheckBox->setObjectName(QStringLiteral("fullScreenCheckBox"));
        fullScreenCheckBox->setFont(font);
        fullScreenCheckBox->setChecked(false);

        verticalLayout->addWidget(fullScreenCheckBox);

        showAxisCheckBox = new QCheckBox(frame);
        showAxisCheckBox->setObjectName(QStringLiteral("showAxisCheckBox"));

        verticalLayout->addWidget(showAxisCheckBox);


        retranslateUi(WindowManager);

        QMetaObject::connectSlotsByName(WindowManager);
    } // setupUi

    void retranslateUi(QFrame *WindowManager)
    {
        WindowManager->setWindowTitle(QApplication::translate("WindowManager", "Frame", 0));
        backgroundColorButton->setText(QApplication::translate("WindowManager", "Background Color", 0));
        saveSnapshotButton->setText(QApplication::translate("WindowManager", "Save Snapshot", 0));
        fullScreenCheckBox->setText(QApplication::translate("WindowManager", "Full Screen", 0));
        showAxisCheckBox->setText(QApplication::translate("WindowManager", "Show Axis", 0));
    } // retranslateUi

};

namespace Ui {
    class WindowManager: public Ui_WindowManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWMANAGER_H
