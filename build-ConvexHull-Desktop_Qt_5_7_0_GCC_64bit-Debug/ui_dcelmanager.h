/********************************************************************************
** Form generated from reading UI file 'dcelmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DCELMANAGER_H
#define UI_DCELMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DcelManager
{
public:
    QFrame *frame3;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QSlider *wireframeWidthDcelSlider;
    QCheckBox *wireframeDcelCheckBox;
    QPushButton *wireframeColorDcelButton;
    QFrame *frame2;
    QGridLayout *gridLayout_4;
    QCheckBox *drawDcelCheckBox;
    QRadioButton *pointsDcelRadioButton;
    QRadioButton *flatDcelRadioButton;
    QRadioButton *smoothDcelRadioButton;
    QFrame *frame1;
    QGridLayout *gridLayout_3;
    QPushButton *loadDcelButton;
    QPushButton *cleanDcelButton;
    QPushButton *saveDcelButton;
    QFrame *frame4;
    QGridLayout *gridLayout_2;
    QRadioButton *triangleColorDcelRadioButton;
    QRadioButton *vertexColorDcelRadioButton;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QFrame *DcelManager)
    {
        if (DcelManager->objectName().isEmpty())
            DcelManager->setObjectName(QStringLiteral("DcelManager"));
        DcelManager->resize(310, 329);
        DcelManager->setFrameShape(QFrame::NoFrame);
        DcelManager->setFrameShadow(QFrame::Raised);
        frame3 = new QFrame(DcelManager);
        frame3->setObjectName(QStringLiteral("frame3"));
        frame3->setGeometry(QRect(11, 140, 141, 161));
        frame3->setFrameShape(QFrame::NoFrame);
        frame3->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);

        wireframeWidthDcelSlider = new QSlider(frame3);
        wireframeWidthDcelSlider->setObjectName(QStringLiteral("wireframeWidthDcelSlider"));
        wireframeWidthDcelSlider->setEnabled(false);
        wireframeWidthDcelSlider->setMinimum(1);
        wireframeWidthDcelSlider->setMaximum(4);
        wireframeWidthDcelSlider->setSingleStep(1);
        wireframeWidthDcelSlider->setValue(3);
        wireframeWidthDcelSlider->setTracking(false);
        wireframeWidthDcelSlider->setOrientation(Qt::Horizontal);
        wireframeWidthDcelSlider->setTickPosition(QSlider::TicksBelow);
        wireframeWidthDcelSlider->setTickInterval(1);

        gridLayout->addWidget(wireframeWidthDcelSlider, 1, 0, 1, 1);

        wireframeDcelCheckBox = new QCheckBox(frame3);
        wireframeDcelCheckBox->setObjectName(QStringLiteral("wireframeDcelCheckBox"));
        wireframeDcelCheckBox->setEnabled(false);
        wireframeDcelCheckBox->setChecked(true);

        gridLayout->addWidget(wireframeDcelCheckBox, 0, 0, 1, 1);

        wireframeColorDcelButton = new QPushButton(frame3);
        wireframeColorDcelButton->setObjectName(QStringLiteral("wireframeColorDcelButton"));
        wireframeColorDcelButton->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wireframeColorDcelButton->sizePolicy().hasHeightForWidth());
        wireframeColorDcelButton->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        wireframeColorDcelButton->setFont(font);

        gridLayout->addWidget(wireframeColorDcelButton, 2, 0, 1, 1);

        frame2 = new QFrame(DcelManager);
        frame2->setObjectName(QStringLiteral("frame2"));
        frame2->setGeometry(QRect(170, 8, 131, 124));
        gridLayout_4 = new QGridLayout(frame2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        drawDcelCheckBox = new QCheckBox(frame2);
        drawDcelCheckBox->setObjectName(QStringLiteral("drawDcelCheckBox"));
        drawDcelCheckBox->setEnabled(false);
        drawDcelCheckBox->setChecked(true);

        gridLayout_4->addWidget(drawDcelCheckBox, 0, 0, 1, 1);

        pointsDcelRadioButton = new QRadioButton(frame2);
        pointsDcelRadioButton->setObjectName(QStringLiteral("pointsDcelRadioButton"));
        pointsDcelRadioButton->setEnabled(false);
        pointsDcelRadioButton->setChecked(true);

        gridLayout_4->addWidget(pointsDcelRadioButton, 1, 0, 1, 1);

        flatDcelRadioButton = new QRadioButton(frame2);
        flatDcelRadioButton->setObjectName(QStringLiteral("flatDcelRadioButton"));
        flatDcelRadioButton->setEnabled(false);
        flatDcelRadioButton->setChecked(false);

        gridLayout_4->addWidget(flatDcelRadioButton, 2, 0, 1, 1);

        smoothDcelRadioButton = new QRadioButton(frame2);
        smoothDcelRadioButton->setObjectName(QStringLiteral("smoothDcelRadioButton"));
        smoothDcelRadioButton->setEnabled(false);
        smoothDcelRadioButton->setChecked(false);

        gridLayout_4->addWidget(smoothDcelRadioButton, 3, 0, 1, 1);

        frame1 = new QFrame(DcelManager);
        frame1->setObjectName(QStringLiteral("frame1"));
        frame1->setGeometry(QRect(11, 8, 141, 121));
        gridLayout_3 = new QGridLayout(frame1);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        loadDcelButton = new QPushButton(frame1);
        loadDcelButton->setObjectName(QStringLiteral("loadDcelButton"));
        loadDcelButton->setFont(font);

        gridLayout_3->addWidget(loadDcelButton, 0, 0, 1, 1);

        cleanDcelButton = new QPushButton(frame1);
        cleanDcelButton->setObjectName(QStringLiteral("cleanDcelButton"));
        cleanDcelButton->setEnabled(false);

        gridLayout_3->addWidget(cleanDcelButton, 1, 0, 1, 1);

        saveDcelButton = new QPushButton(frame1);
        saveDcelButton->setObjectName(QStringLiteral("saveDcelButton"));
        saveDcelButton->setEnabled(false);

        gridLayout_3->addWidget(saveDcelButton, 2, 0, 1, 1);

        frame4 = new QFrame(DcelManager);
        frame4->setObjectName(QStringLiteral("frame4"));
        frame4->setGeometry(QRect(170, 140, 131, 161));
        gridLayout_2 = new QGridLayout(frame4);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        triangleColorDcelRadioButton = new QRadioButton(frame4);
        triangleColorDcelRadioButton->setObjectName(QStringLiteral("triangleColorDcelRadioButton"));
        triangleColorDcelRadioButton->setEnabled(false);
        triangleColorDcelRadioButton->setFont(font);
        triangleColorDcelRadioButton->setChecked(true);

        gridLayout_2->addWidget(triangleColorDcelRadioButton, 2, 0, 1, 1);

        vertexColorDcelRadioButton = new QRadioButton(frame4);
        vertexColorDcelRadioButton->setObjectName(QStringLiteral("vertexColorDcelRadioButton"));
        vertexColorDcelRadioButton->setEnabled(false);
        vertexColorDcelRadioButton->setFont(font);
        vertexColorDcelRadioButton->setChecked(false);

        gridLayout_2->addWidget(vertexColorDcelRadioButton, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 4, 0, 1, 2);


        retranslateUi(DcelManager);

        QMetaObject::connectSlotsByName(DcelManager);
    } // setupUi

    void retranslateUi(QFrame *DcelManager)
    {
        DcelManager->setWindowTitle(QApplication::translate("DcelManager", "Frame", 0));
        wireframeDcelCheckBox->setText(QApplication::translate("DcelManager", "Wireframe", 0));
        wireframeColorDcelButton->setText(QApplication::translate("DcelManager", "Set W color", 0));
        drawDcelCheckBox->setText(QApplication::translate("DcelManager", "Draw", 0));
        pointsDcelRadioButton->setText(QApplication::translate("DcelManager", "Points", 0));
        flatDcelRadioButton->setText(QApplication::translate("DcelManager", "Flat", 0));
        smoothDcelRadioButton->setText(QApplication::translate("DcelManager", "Smooth", 0));
        loadDcelButton->setText(QApplication::translate("DcelManager", "Load DCEL", 0));
        cleanDcelButton->setText(QApplication::translate("DcelManager", "Clean DCEL", 0));
        saveDcelButton->setText(QApplication::translate("DcelManager", "Save DCEL", 0));
        triangleColorDcelRadioButton->setText(QApplication::translate("DcelManager", "T color", 0));
        vertexColorDcelRadioButton->setText(QApplication::translate("DcelManager", "V color", 0));
    } // retranslateUi

};

namespace Ui {
    class DcelManager: public Ui_DcelManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DCELMANAGER_H
