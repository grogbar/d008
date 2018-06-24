/********************************************************************************
** Form generated from reading UI file 'd008.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_D008_H
#define UI_D008_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QAction *actionActions;
    QAction *actionAbout;
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QFrame *line_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButtonRun;
    QPushButton *pushButtonCancel;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEditCmd;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_Actions;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonProfiles;
    QPushButton *pushButtonPackages;
    QPushButton *pushButtonTools;
    QPushButton *pushButtonAll;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEditAction;
    QTreeWidget *treeWidgetActions;
    QFrame *line_4;
    QVBoxLayout *verticalLayout_Targets;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonAD;
    QPushButton *pushButtonFiles;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEditComputer;
    QListWidget *listWidgetTargets;
    QFrame *line_2;
    QTreeView *treeViewJobs;
    QFrame *line_1;
    QFrame *frameProc;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *d008Class)
    {
        if (d008Class->objectName().isEmpty())
            d008Class->setObjectName(QStringLiteral("d008Class"));
        d008Class->resize(919, 346);
        actionPreferences = new QAction(d008Class);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        actionActions = new QAction(d008Class);
        actionActions->setObjectName(QStringLiteral("actionActions"));
        actionAbout = new QAction(d008Class);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionExit = new QAction(d008Class);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(d008Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        pushButtonRun = new QPushButton(centralWidget);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));

        horizontalLayout_6->addWidget(pushButtonRun);

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
        verticalLayout_Actions = new QVBoxLayout();
        verticalLayout_Actions->setSpacing(6);
        verticalLayout_Actions->setObjectName(QStringLiteral("verticalLayout_Actions"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButtonProfiles = new QPushButton(centralWidget);
        pushButtonProfiles->setObjectName(QStringLiteral("pushButtonProfiles"));

        horizontalLayout_2->addWidget(pushButtonProfiles);

        pushButtonPackages = new QPushButton(centralWidget);
        pushButtonPackages->setObjectName(QStringLiteral("pushButtonPackages"));

        horizontalLayout_2->addWidget(pushButtonPackages);

        pushButtonTools = new QPushButton(centralWidget);
        pushButtonTools->setObjectName(QStringLiteral("pushButtonTools"));

        horizontalLayout_2->addWidget(pushButtonTools);

        pushButtonAll = new QPushButton(centralWidget);
        pushButtonAll->setObjectName(QStringLiteral("pushButtonAll"));

        horizontalLayout_2->addWidget(pushButtonAll);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_Actions->addLayout(horizontalLayout_2);

        lineEditAction = new QLineEdit(centralWidget);
        lineEditAction->setObjectName(QStringLiteral("lineEditAction"));

        verticalLayout_Actions->addWidget(lineEditAction);

        treeWidgetActions = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidgetActions->setHeaderItem(__qtreewidgetitem);
        treeWidgetActions->setObjectName(QStringLiteral("treeWidgetActions"));

        verticalLayout_Actions->addWidget(treeWidgetActions);


        horizontalLayout_3->addLayout(verticalLayout_Actions);

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

        horizontalLayout_4->addWidget(pushButtonAD);

        pushButtonFiles = new QPushButton(centralWidget);
        pushButtonFiles->setObjectName(QStringLiteral("pushButtonFiles"));

        horizontalLayout_4->addWidget(pushButtonFiles);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_Targets->addLayout(horizontalLayout_4);

        lineEditComputer = new QLineEdit(centralWidget);
        lineEditComputer->setObjectName(QStringLiteral("lineEditComputer"));

        verticalLayout_Targets->addWidget(lineEditComputer);

        listWidgetTargets = new QListWidget(centralWidget);
        listWidgetTargets->setObjectName(QStringLiteral("listWidgetTargets"));

        verticalLayout_Targets->addWidget(listWidgetTargets);


        horizontalLayout_3->addLayout(verticalLayout_Targets);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        treeViewJobs = new QTreeView(centralWidget);
        treeViewJobs->setObjectName(QStringLiteral("treeViewJobs"));

        horizontalLayout->addWidget(treeViewJobs);

        line_1 = new QFrame(centralWidget);
        line_1->setObjectName(QStringLiteral("line_1"));
        line_1->setFrameShape(QFrame::VLine);
        line_1->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_1);

        frameProc = new QFrame(centralWidget);
        frameProc->setObjectName(QStringLiteral("frameProc"));
        frameProc->setFrameShape(QFrame::StyledPanel);
        frameProc->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(frameProc);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        d008Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(d008Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 919, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        d008Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(d008Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        d008Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(d008Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        d008Class->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionExit);
        menuSettings->addAction(actionPreferences);
        menuSettings->addAction(actionActions);
        menuAbout->addAction(actionAbout);

        retranslateUi(d008Class);
        QObject::connect(treeWidgetActions, SIGNAL(clicked(QModelIndex)), lineEditCmd, SLOT(paste()));

        QMetaObject::connectSlotsByName(d008Class);
    } // setupUi

    void retranslateUi(QMainWindow *d008Class)
    {
        d008Class->setWindowTitle(QApplication::translate("d008Class", "deploy", nullptr));
        actionPreferences->setText(QApplication::translate("d008Class", "Preferences", nullptr));
        actionActions->setText(QApplication::translate("d008Class", "Actions", nullptr));
        actionAbout->setText(QApplication::translate("d008Class", "About", nullptr));
        actionExit->setText(QApplication::translate("d008Class", "E&xit", nullptr));
        pushButtonRun->setText(QApplication::translate("d008Class", "Run", nullptr));
        pushButtonCancel->setText(QApplication::translate("d008Class", "Cancel", nullptr));
        pushButtonProfiles->setText(QApplication::translate("d008Class", "Profiles", nullptr));
        pushButtonPackages->setText(QApplication::translate("d008Class", "Packages", nullptr));
        pushButtonTools->setText(QApplication::translate("d008Class", "Tools", nullptr));
        pushButtonAll->setText(QApplication::translate("d008Class", "All", nullptr));
        pushButtonAD->setText(QApplication::translate("d008Class", "AD", nullptr));
        pushButtonFiles->setText(QApplication::translate("d008Class", "Files", nullptr));
        menuFile->setTitle(QApplication::translate("d008Class", "File", nullptr));
        menuSettings->setTitle(QApplication::translate("d008Class", "Settings", nullptr));
        menuAbout->setTitle(QApplication::translate("d008Class", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class d008Class: public Ui_d008Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_D008_H
