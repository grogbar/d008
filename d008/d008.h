#pragma once

#include <QtWidgets/QMainWindow>
#include <QString>
#include <QTreeWidgetItem>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
#include <stdio.h>  /* defines FILENAME_MAX */
#include <direct.h> 
#include "ui_d008.h"
#include "action.h"

struct config_t {
	// [GENERAL]
	std::string		currentpath;
	std::string		binpath;
	std::string		actionsini;
	std::string		sourcepath;
	std::string		stagingpath;
	std::string		stagingunc;
	std::string		packageroot; //	PACKAGEROOT = "$DEPLOY$-"
	unsigned		packagedigits;
	std::string		pathseparator;// = '\'
	std::string		targetvar; // = "%TARGET%"
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
	int read_config(const std::string FileName);
	int parse_config();
	int read_targetFile(std::string FileName);
	int write_config(const std::string FileName);
	void load_actionTree(void);
	void link_signals_and_slots(void);
	// VARIABLES
	std::vector<std::string> targets;
	Ui::d008Class ui;

public slots:
	void on_treeWidgetActions_itemClicked(QTreeWidgetItem* qtwitem, int i);
	//void on_actionPreferences_triggered();
    //void on_actionActions_triggered();
    //void on_actionAbout_triggered();
    void on_actionExit_triggered();
    void on_pushButtonRun_clicked();
    void on_pushButtonCancel_clicked();
    void on_lineEditCmd_textEdited(QString);
    //void on_pushButtonProfiles_clicked();
    //void on_pushButtonPackages_clicked();
    //void on_pushButtonTools_clicked();
    void on_lineEditAction_textEdited(QString);
    //void on_treeViewActions_();
    //void on_pushButtonAD_clicked();
    //void on_pushButtonFiles_clicked();
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


private:
	//void addTreeRoot(QString name, QString description);
	//void addTreeChild(QTreeWidgetItem *parent, QString name, QString description);

	config_t config;
	Action actions;
	action_t action;
	std::map<std::string, std::string>			mConfigData;  // config.ini file 





};
