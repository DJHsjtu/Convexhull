/********************************************************************************
** Form generated from reading UI file 'convexhullmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONVEXHULLMANAGER_H
#define UI_CONVEXHULLMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ConvexHullManager
{
public:
    QPushButton *convexHullPushButton;
    QLabel *label;
    QLabel *timeLabel;
    QCheckBox *showPhasesCheckBox;

    void setupUi(QFrame *ConvexHullManager)
    {
        if (ConvexHullManager->objectName().isEmpty())
            ConvexHullManager->setObjectName(QStringLiteral("ConvexHullManager"));
        ConvexHullManager->resize(310, 148);
        ConvexHullManager->setFrameShape(QFrame::StyledPanel);
        ConvexHullManager->setFrameShadow(QFrame::Raised);
        convexHullPushButton = new QPushButton(ConvexHullManager);
        convexHullPushButton->setObjectName(QStringLiteral("convexHullPushButton"));
        convexHullPushButton->setEnabled(false);
        convexHullPushButton->setGeometry(QRect(15, 10, 281, 27));
        label = new QLabel(ConvexHullManager);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 40, 41, 17));
        timeLabel = new QLabel(ConvexHullManager);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        timeLabel->setGeometry(QRect(100, 40, 141, 17));
        showPhasesCheckBox = new QCheckBox(ConvexHullManager);
        showPhasesCheckBox->setObjectName(QStringLiteral("showPhasesCheckBox"));
        showPhasesCheckBox->setGeometry(QRect(10, 60, 151, 21));

        retranslateUi(ConvexHullManager);

        QMetaObject::connectSlotsByName(ConvexHullManager);
    } // setupUi

    void retranslateUi(QFrame *ConvexHullManager)
    {
        ConvexHullManager->setWindowTitle(QApplication::translate("ConvexHullManager", "Frame", 0));
        convexHullPushButton->setText(QApplication::translate("ConvexHullManager", "Convex Hull!", 0));
        label->setText(QApplication::translate("ConvexHullManager", "Time: ", 0));
        timeLabel->setText(QApplication::translate("ConvexHullManager", "0.0", 0));
        showPhasesCheckBox->setText(QApplication::translate("ConvexHullManager", "Show Phases", 0));
    } // retranslateUi

};

namespace Ui {
    class ConvexHullManager: public Ui_ConvexHullManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONVEXHULLMANAGER_H
