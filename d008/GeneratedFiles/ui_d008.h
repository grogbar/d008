/********************************************************************************
** Form generated from reading UI file 'd008.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_D008_H
#define UI_D008_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_d008Class
{
public:
    QAction *actionPreferences;
    QAction *actionObjects;
    QAction *actionAbout;
    QAction *actionExit;
    QAction *actionCheck;
    QAction *actionStage;
    QAction *actionInstall;
    QAction *actionUninstall;
    QAction *actionStageInstall;
    QAction *actionLogs;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButtonRun;
    QPushButton *pushButtonStage;
    QPushButton *pushButtonInstall;
    QPushButton *pushButtonUninstall;
    QPushButton *pushButtonLogs;
    QPushButton *pushButtonCancel;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEditCmd;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_Objects;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonGroups;
    QPushButton *pushButtonPackages;
    QPushButton *pushButtonTools;
    QPushButton *pushButtonAll;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEditObject;
    QTreeWidget *treeWidgetObjects;
    QFrame *line_4;
    QVBoxLayout *verticalLayout_Targets;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonAD;
    QPushButton *pushButtonFiles;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEditComputer;
    QListWidget *listWidgetTargets;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radialGroups;
    QRadioButton *radialPackages;
    QSpacerItem *horizontalSpacer_4;
    QProgressBar *progressBar;
    QTreeView *treeViewJobs;
    QFrame *line_1;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QFrame *frameProc;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QMenu *menuAbout;
    QMenu *menuObjects;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *d008Class)
    {
        if (d008Class->objectName().isEmpty())
            d008Class->setObjectName(QStringLiteral("d008Class"));
        d008Class->resize(911, 499);
        actionPreferences = new QAction(d008Class);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        actionObjects = new QAction(d008Class);
        actionObjects->setObjectName(QStringLiteral("actionObjects"));
        actionAbout = new QAction(d008Class);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionExit = new QAction(d008Class);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionCheck = new QAction(d008Class);
        actionCheck->setObjectName(QStringLiteral("actionCheck"));
        actionStage = new QAction(d008Class);
        actionStage->setObjectName(QStringLiteral("actionStage"));
        actionInstall = new QAction(d008Class);
        actionInstall->setObjectName(QStringLiteral("actionInstall"));
        actionUninstall = new QAction(d008Class);
        actionUninstall->setObjectName(QStringLiteral("actionUninstall"));
        actionStageInstall = new QAction(d008Class);
        actionStageInstall->setObjectName(QStringLiteral("actionStageInstall"));
        actionLogs = new QAction(d008Class);
        actionLogs->setObjectName(QStringLiteral("actionLogs"));
        centralWidget = new QWidget(d008Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        pushButtonRun = new QPushButton(centralWidget);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));

        horizontalLayout_6->addWidget(pushButtonRun);

        pushButtonStage = new QPushButton(centralWidget);
        pushButtonStage->setObjectName(QStringLiteral("pushButtonStage"));

        horizontalLayout_6->addWidget(pushButtonStage);

        pushButtonInstall = new QPushButton(centralWidget);
        pushButtonInstall->setObjectName(QStringLiteral("pushButtonInstall"));

        horizontalLayout_6->addWidget(pushButtonInstall);

        pushButtonUninstall = new QPushButton(centralWidget);
        pushButtonUninstall->setObjectName(QStringLiteral("pushButtonUninstall"));

        horizontalLayout_6->addWidget(pushButtonUninstall);

        pushButtonLogs = new QPushButton(centralWidget);
        pushButtonLogs->setObjectName(QStringLiteral("pushButtonLogs"));

        horizontalLayout_6->addWidget(pushButtonLogs);

        pushButtonCancel = new QPushButton(centralWidget);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));

        horizontalLayout_6->addWidget(pushButtonCancel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_6);

        lineEditCmd = new QLineEdit(centralWidget);
        lineEditCmd->setObjectName(QStringLiteral("lineEditCmd"));

        verticalLayout->addWidget(lineEditCmd);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_Objects = new QVBoxLayout();
        verticalLayout_Objects->setSpacing(6);
        verticalLayout_Objects->setObjectName(QStringLiteral("verticalLayout_Objects"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButtonGroups = new QPushButton(centralWidget);
        pushButtonGroups->setObjectName(QStringLiteral("pushButtonGroups"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonGroups->sizePolicy().hasHeightForWidth());
        pushButtonGroups->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButtonGroups->setFont(font);
        pushButtonGroups->setIconSize(QSize(16, 16));
        pushButtonGroups->setCheckable(true);
        pushButtonGroups->setChecked(true);

        horizontalLayout_2->addWidget(pushButtonGroups);

        pushButtonPackages = new QPushButton(centralWidget);
        pushButtonPackages->setObjectName(QStringLiteral("pushButtonPackages"));
        pushButtonPackages->setCheckable(true);
        pushButtonPackages->setChecked(true);

        horizontalLayout_2->addWidget(pushButtonPackages);

        pushButtonTools = new QPushButton(centralWidget);
        pushButtonTools->setObjectName(QStringLiteral("pushButtonTools"));
        pushButtonTools->setCheckable(true);
        pushButtonTools->setChecked(true);

        horizontalLayout_2->addWidget(pushButtonTools);

        pushButtonAll = new QPushButton(centralWidget);
        pushButtonAll->setObjectName(QStringLiteral("pushButtonAll"));
        pushButtonAll->setCheckable(true);

        horizontalLayout_2->addWidget(pushButtonAll);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_Objects->addLayout(horizontalLayout_2);

        lineEditObject = new QLineEdit(centralWidget);
        lineEditObject->setObjectName(QStringLiteral("lineEditObject"));

        verticalLayout_Objects->addWidget(lineEditObject);

        treeWidgetObjects = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidgetObjects->setHeaderItem(__qtreewidgetitem);
        treeWidgetObjects->setObjectName(QStringLiteral("treeWidgetObjects"));
        treeWidgetObjects->setSortingEnabled(false);
        treeWidgetObjects->setHeaderHidden(true);

        verticalLayout_Objects->addWidget(treeWidgetObjects);


        horizontalLayout_3->addLayout(verticalLayout_Objects);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_4);

        verticalLayout_Targets = new QVBoxLayout();
        verticalLayout_Targets->setSpacing(6);
        verticalLayout_Targets->setObjectName(QStringLiteral("verticalLayout_Targets"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButtonAD = new QPushButton(centralWidget);
        pushButtonAD->setObjectName(QStringLiteral("pushButtonAD"));
        pushButtonAD->setCheckable(true);

        horizontalLayout_4->addWidget(pushButtonAD);

        pushButtonFiles = new QPushButton(centralWidget);
        pushButtonFiles->setObjectName(QStringLiteral("pushButtonFiles"));
        pushButtonFiles->setCheckable(true);

        horizontalLayout_4->addWidget(pushButtonFiles);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_Targets->addLayout(horizontalLayout_4);

        lineEditComputer = new QLineEdit(centralWidget);
        lineEditComputer->setObjectName(QStringLiteral("lineEditComputer"));

        verticalLayout_Targets->addWidget(lineEditComputer);

        listWidgetTargets = new QListWidget(centralWidget);
        listWidgetTargets->setObjectName(QStringLiteral("listWidgetTargets"));
        listWidgetTargets->setMinimumSize(QSize(160, 0));
        listWidgetTargets->setMaximumSize(QSize(16777215, 16777215));
        listWidgetTargets->setFrameShadow(QFrame::Sunken);
        listWidgetTargets->setLineWidth(2);
        listWidgetTargets->setSortingEnabled(true);

        verticalLayout_Targets->addWidget(listWidgetTargets);


        horizontalLayout_3->addLayout(verticalLayout_Targets);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        radialGroups = new QRadioButton(centralWidget);
        radialGroups->setObjectName(QStringLiteral("radialGroups"));
        radialGroups->setChecked(true);

        horizontalLayout_5->addWidget(radialGroups);

        radialPackages = new QRadioButton(centralWidget);
        radialPackages->setObjectName(QStringLiteral("radialPackages"));

        horizontalLayout_5->addWidget(radialPackages);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_5);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        verticalLayout_2->addWidget(progressBar);

        treeViewJobs = new QTreeView(centralWidget);
        treeViewJobs->setObjectName(QStringLiteral("treeViewJobs"));

        verticalLayout_2->addWidget(treeViewJobs);


        horizontalLayout->addLayout(verticalLayout_2);

        line_1 = new QFrame(centralWidget);
        line_1->setObjectName(QStringLiteral("line_1"));
        line_1->setFrameShape(QFrame::VLine);
        line_1->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_1);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setMinimumSize(QSize(200, 0));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 198, 424));
        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        frameProc = new QFrame(centralWidget);
        frameProc->setObjectName(QStringLiteral("frameProc"));
        frameProc->setFrameShape(QFrame::StyledPanel);
        frameProc->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(frameProc);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        d008Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(d008Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 911, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        menuObjects = new QMenu(menuBar);
        menuObjects->setObjectName(QStringLiteral("menuObjects"));
        d008Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(d008Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        d008Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(d008Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        d008Class->setStatusBar(statusBar);
        QWidget::setTabOrder(lineEditObject, treeWidgetObjects);
        QWidget::setTabOrder(treeWidgetObjects, lineEditComputer);
        QWidget::setTabOrder(lineEditComputer, listWidgetTargets);
        QWidget::setTabOrder(listWidgetTargets, pushButtonRun);
        QWidget::setTabOrder(pushButtonRun, pushButtonStage);
        QWidget::setTabOrder(pushButtonStage, pushButtonInstall);
        QWidget::setTabOrder(pushButtonInstall, pushButtonUninstall);
        QWidget::setTabOrder(pushButtonUninstall, pushButtonLogs);
        QWidget::setTabOrder(pushButtonLogs, pushButtonCancel);
        QWidget::setTabOrder(pushButtonCancel, lineEditCmd);
        QWidget::setTabOrder(lineEditCmd, pushButtonGroups);
        QWidget::setTabOrder(pushButtonGroups, pushButtonPackages);
        QWidget::setTabOrder(pushButtonPackages, pushButtonTools);
        QWidget::setTabOrder(pushButtonTools, pushButtonAll);
        QWidget::setTabOrder(pushButtonAll, pushButtonAD);
        QWidget::setTabOrder(pushButtonAD, pushButtonFiles);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuObjects->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionExit);
        menuSettings->addAction(actionPreferences);
        menuSettings->addAction(actionObjects);
        menuAbout->addAction(actionAbout);
        menuObjects->addAction(actionCheck);
        menuObjects->addAction(actionStage);
        menuObjects->addAction(actionInstall);
        menuObjects->addAction(actionUninstall);
        menuObjects->addAction(actionStageInstall);
        menuObjects->addAction(actionLogs);

        retranslateUi(d008Class);

        QMetaObject::connectSlotsByName(d008Class);
    } // setupUi

    void retranslateUi(QMainWindow *d008Class)
    {
        d008Class->setWindowTitle(QApplication::translate("d008Class", "deploy", Q_NULLPTR));
        actionPreferences->setText(QApplication::translate("d008Class", "Preferences", Q_NULLPTR));
        actionObjects->setText(QApplication::translate("d008Class", "Objects", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("d008Class", "About", Q_NULLPTR));
        actionExit->setText(QApplication::translate("d008Class", "E&xit", Q_NULLPTR));
        actionCheck->setText(QApplication::translate("d008Class", "0 Check", Q_NULLPTR));
        actionStage->setText(QApplication::translate("d008Class", "1 Stage", Q_NULLPTR));
        actionInstall->setText(QApplication::translate("d008Class", "2 Install", Q_NULLPTR));
        actionUninstall->setText(QApplication::translate("d008Class", "3 Uninstall", Q_NULLPTR));
        actionStageInstall->setText(QApplication::translate("d008Class", "4 Stage & Install", Q_NULLPTR));
        actionLogs->setText(QApplication::translate("d008Class", "Logs", Q_NULLPTR));
        pushButtonRun->setText(QApplication::translate("d008Class", "Run", Q_NULLPTR));
        pushButtonStage->setText(QApplication::translate("d008Class", "Stage", Q_NULLPTR));
        pushButtonInstall->setText(QApplication::translate("d008Class", "Install", Q_NULLPTR));
        pushButtonUninstall->setText(QApplication::translate("d008Class", "Uninstall", Q_NULLPTR));
        pushButtonLogs->setText(QApplication::translate("d008Class", "Logs", Q_NULLPTR));
        pushButtonCancel->setText(QApplication::translate("d008Class", "Cancel", Q_NULLPTR));
        pushButtonGroups->setText(QApplication::translate("d008Class", "Groups", Q_NULLPTR));
        pushButtonPackages->setText(QApplication::translate("d008Class", "Packages", Q_NULLPTR));
        pushButtonTools->setText(QApplication::translate("d008Class", "Tools", Q_NULLPTR));
        pushButtonAll->setText(QApplication::translate("d008Class", "All", Q_NULLPTR));
        pushButtonAD->setText(QApplication::translate("d008Class", "AD", Q_NULLPTR));
        pushButtonFiles->setText(QApplication::translate("d008Class", "Files", Q_NULLPTR));
        radialGroups->setText(QApplication::translate("d008Class", "Groups", Q_NULLPTR));
        radialPackages->setText(QApplication::translate("d008Class", "Packages", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("d008Class", "File", Q_NULLPTR));
        menuSettings->setTitle(QApplication::translate("d008Class", "Settings", Q_NULLPTR));
        menuAbout->setTitle(QApplication::translate("d008Class", "Help", Q_NULLPTR));
        menuObjects->setTitle(QApplication::translate("d008Class", "Objects", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class d008Class: public Ui_d008Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_D008_H
