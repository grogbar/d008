#pragma once

#include <QtWidgets/QMainWindow>
#include <QString>
#include <QTreeWidgetItem>
#include <qfiledialog.h>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
#include <stdio.h>  /* defines FILENAME_MAX */
#include <direct.h> 
#include "ui_d008.h"
#include "Config.h"
#include "object.h"
#include "Q.h"
#include "proc.h"
#include <qdebug.h>


struct config_t {
	// [GENERAL]
	QString		currentpath;
	QString		targetfiles;
	QString		binpath;
	QString		objectsini;
	QString		sourcepath;
	QString		stagingpath;
	QString		stagingunc;
	QString		packageroot; //	PACKAGEROOT = "$DEPLOY$-"
	unsigned		packagedigits;
	QString		pathseparator;// = '\'
	QString		targetvar; // = "%TARGET%"
	int				procmax; // = 4
	// [TARGETS]
	bool viewall = 0;
	bool viewshells = 0;
	bool viewgroups = 1;
	bool viewpackages = 1;
	bool viewtools = 1;
};

class d008 : public QMainWindow
{
	Q_OBJECT

public:
	d008(QWidget *parent = Q_NULLPTR);
	int init(void);
	int read_config();
	int parse_config();
	int write_config();
	int read_targetFile(QString FileName);
	void load_objectTree(void);
	void load_object(QString parent, QString title);
	void link_signals_and_slots(void);

	// VARIABLES
	QVector<QString> targets;
	Ui::d008Class	ui;
	QFont			fontReg;
	QFont			fontBold;
	object_t		object;
	Config          config;
	Object			objects;
	Q				q = Q(objects,ui);
	
	QMap<QString, QString>	mConfigData;  // config.ini file 

public slots:
	void on_treeWidgetObjects_itemSelectionChanged(void);
	void on_listWidgetTargets_itemSelectionChanged(void);
	//void on_actionPreferences_triggered();
    //void on_actionObjects_triggered();
    //void on_actionAbout_triggered();
    void on_actionExit_triggered();
    void on_lineEditCmd_textEdited(QString);
	void on_pushButtonGroups_toggled(bool checked);
	void on_pushButtonPackages_toggled(bool checked);
	void on_pushButtonTools_toggled(bool checked);
	void on_pushButtonAll_toggled(bool checked);

	void on_pushButtonRun_clicked();
	void on_pushButtonCancel_clicked();
	void on_pushButtonStage_clicked();
	void on_pushButtonInstall_clicked();
	void on_pushButtonUninstall_clicked();
	void on_pushButtonLogs_clicked();

	void on_lineEditObject_textChanged(QString);
    //void on_treeViewObjects_();
    void on_pushButtonAD_clicked();
    void on_pushButtonFiles_clicked();
    void on_lineEditComputer_textEdited(QString);
    //void on_listViewComputers_();
    //void on_treeViewJobs_();
    //void on_frameProc_();
    //void on_menuBar_();
    //void on_menuFile_();
    //void on_menuSettings_();
    //void on_menuAbout_triggered();
	//void on_mainToolBar_();
	//void on_statusBar_();


	//QAction *actionCheck;
	//QAction *actionStage;
	//QAction *actionInstall;
	//QAction *actionUninstall;
	//QAction *actionStageInstall;
	//QAction *actionLogs;
	//QPushButton *pushButtonRun;
	//QPushButton *pushButtonStage;
	//QPushButton *pushButtonInstall;
	//QPushButton *pushButtonUninstall;
	//QPushButton *pushButtonLogs;
	//QPushButton *pushButtonCancel;



private:
	//void addTreeRoot(QString name, QString description);
	//void addTreeChild(QTreeWidgetItem *parent, QString name, QString description);

	QTreeWidgetItem *objectTreeOSs;
	QTreeWidgetItem *objectTreeShells;
	QTreeWidgetItem *objectTreeGroups;
	QTreeWidgetItem *objectTreePackages;
	QTreeWidgetItem *objectTreeTools;
	
	





};
