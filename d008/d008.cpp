#include "d008.h"
#include "toolkit.h"


d008::d008(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}
int d008::init() {
	//Actions
	// [GENERAL]
	config.currentpath	= GetCurrentWorkingDir();
	config.binpath = config.currentpath + "\bin";
	config.actionsini = config.currentpath + "\\actions.ini";
	config.stagingpath	= "c:\\windows\\installer\\";
	config.stagingunc	= "//%TARGET%//c$//windows//installer//";
	config.packageroot	= "$DEPLOY$-";
	config.packagedigits = 6;
	config.targetvar	= "%TARGET%";
	config.procmax		= 4;
	// [TARGETS]
	config.viewall = 0;
	config.viewshells = 0;
	config.viewgroups = 1;
	config.viewpackages = 1;
	config.viewtools = 1;

	std::string configini = config.currentpath + "\\config.ini";
	read_config( configini ); 
	parse_config();
	actions.read_actions( config.actionsini );
	actions.parse_actions();
	load_actionTree();
	read_targetFile(".\\workstations.txt");
	link_signals_and_slots();



	//addTreeRoot(QString name, QString description);
	//addTreeChild(QTreeWidgetItem *parent,	QString name, QString description);
	return 0;
}

// ====MEMBER FUNCTIONS=========================================================
int d008::write_config(const std::string FileName) { return 0;  }
int d008::read_config(const std::string FileName) {
	std::ifstream configFile(FileName);
	int i,cnum;
	std::string text,line,ckey,key,val;

	cnum = 0;
	while (std::getline(configFile, text))
	{
		line = trim(text);
		if (line.empty()) {}
		else if ((line.at(0) == '#' || line.at(0) == ';') ) {
			ckey = "C" + std::to_string(cnum);
			mConfigData[ckey] = trim(line);
			cnum++;
		}
		else {
			i = 0;
			while (line.at(i) != '=' && i<line.length()-1) i++;
			if (i < line.length() - 1) {
				key = trim(line.substr(0, i));
				val = trim(line.substr(i + 1, line.length() - i + 1));
				mConfigData[key] = val;
			}
		}
		
	}
	return 0;
}
int d008::parse_config() {
	std::map<std::string, std::string>::iterator item = mConfigData.begin();
	while (item != mConfigData.end()) {
		if      (upper(item->first) == "STAGINGPATH") config.stagingpath = trim(item->second);
		else if (upper(item->first) == "STAGINGUNC") config.stagingunc = trim(item->second);
		else if (upper(item->first) == "ACTIONSINI") config.actionsini = trim(item->second);
		else if (upper(item->first) == "PACKAGEROOT") config.packageroot = trim(item->second);
		else if (upper(item->first) == "PACKAGEDIGITS")  config.packagedigits = atoi(trim(item->second).c_str());
		else if (upper(item->first) == "STAGINGUNC") config.stagingunc = trim(item->second);
		else if (upper(item->first) == "TARGETVAR") config.targetvar = trim(item->second);
		else if (upper(item->first) == "PROCMAX") config.procmax = atoi(trim(item->second).c_str());
		else if (upper(item->first) == "VIEWALL") config.viewall			= (trim(item->second) == "1") ? 1 : 0;
		else if (upper(item->first) == "VIEWSHELLS") config.viewshells		= (trim(item->second) == "1") ? 1 : 0;
		else if (upper(item->first) == "VIEWGROUPS") config.viewgroups		= (trim(item->second) == "1") ? 1 : 0;
		else if (upper(item->first) == "VIEWPACKAGES") config.viewpackages	= (trim(item->second) == "1") ? 1 : 0;
		else if (upper(item->first) == "VIEWTOOLS") config.viewtools		= (trim(item->second) == "1") ? 1 : 0;
		item++;
	}
	return 0;
}
int d008::read_targetFile(std::string FileName) {
	std::ifstream targetFile(FileName);
	std::string line;
	
	ui.listWidgetTargets->clear();
	while (std::getline(targetFile, line))
	{
		targets.push_back(trim(line));
		ui.listWidgetTargets->addItem(QString::fromStdString(trim(line)));
	}
	return 0;
}
void d008::load_actionTree(void) {
	ui.treeWidgetActions->setColumnCount(1); 
	ui.treeWidgetActions->setHeaderLabels(QStringList() << "Actions");
	QStringList qactions = (QStringList() << "OSs"<<"Shells" << "Profiles" << "Packages" << "Tools");
	QList<QTreeWidgetItem *> actionTreeItems;
	QTreeWidgetItem *item;

	// OSs
	QTreeWidgetItem *actionTreeOSs;
	actionTreeOSs = new QTreeWidgetItem(ui.treeWidgetActions);
	actionTreeOSs->setText(0, "OSs");
	ui.treeWidgetActions->addTopLevelItem(actionTreeOSs);
	std::map<std::string, os_t>::iterator os = actions.OSs.begin();
	while (os != actions.OSs.end()) {
		actionTreeOSs->addChild(new QTreeWidgetItem(QStringList(QString::fromStdString(os->first))));
		os++;
	}

	// Shells 
	QTreeWidgetItem *actionTreeShells;
	actionTreeShells = new QTreeWidgetItem(ui.treeWidgetActions);
	actionTreeShells->setText(0, "shells");
	ui.treeWidgetActions->addTopLevelItem(actionTreeShells);
	std::map<std::string, shell_t>::iterator shell = actions.shells.begin();
	while (shell != actions.shells.end()) { 
		actionTreeShells->addChild(new QTreeWidgetItem(QStringList(QString::fromStdString(shell->first))));
		shell++;
	}

	// Groups 
	QTreeWidgetItem *actionTreeGroups;
	actionTreeGroups = new QTreeWidgetItem(ui.treeWidgetActions);
	actionTreeGroups->setText(0, "groups");
	ui.treeWidgetActions->addTopLevelItem(actionTreeGroups);
	std::map<std::string, group_t>::iterator group = actions.groups.begin();
	while (group != actions.groups.end()) {
		actionTreeGroups->addChild(new QTreeWidgetItem(QStringList(QString::fromStdString(group->first))));
		group++;
	}

	// Packages
	QTreeWidgetItem *actionTreePackages;
	actionTreePackages = new QTreeWidgetItem(ui.treeWidgetActions);
	actionTreePackages->setText(0, "packages");
	ui.treeWidgetActions->addTopLevelItem(actionTreePackages);
	std::map<std::string, package_t>::iterator package = actions.packages.begin();
	while (package != actions.packages.end()) {
		actionTreeGroups->addChild(new QTreeWidgetItem(QStringList(QString::fromStdString(package->first))));
		package++;
	}

	// Tools 
	QTreeWidgetItem *actionTreeTools;
	actionTreeTools = new QTreeWidgetItem(ui.treeWidgetActions);
	actionTreeTools->setText(0, "tools");
	ui.treeWidgetActions->addTopLevelItem(actionTreeTools);
	std::map<std::string, tool_t>::iterator tool = actions.tools.begin();
	while (tool != actions.tools.end()) {
		actionTreeGroups->addChild(new QTreeWidgetItem(QStringList(QString::fromStdString(tool->first))));
		tool++;
	}
	return;
}
void d008::link_signals_and_slots(void) {
	connect(ui.treeWidgetActions, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(on_treeWidgetActions_itemClicked(QTreeWidgetItem* item, int)) );
	
	//QObject::connect(treeWidgetActions, SIGNAL(clicked(QModelIndex)), lineEditCmd, SLOT(paste()));

	//QAction *actionPreferences;
	//QAction *actionActions;
	//QAction *actionAbout;
	//QAction *actionExit;
	//QWidget *centralWidget;
	//QGridLayout *gridLayout;
	//QHBoxLayout *horizontalLayout;
	//QFrame *line_3;
	//QVBoxLayout *verticalLayout;
	//QHBoxLayout *horizontalLayout_6;
	//QPushButton *pushButtonRun;
	//QPushButton *pushButtonCancel;
	//QSpacerItem *horizontalSpacer;
	//QLineEdit *lineEditCmd;
	//QHBoxLayout *horizontalLayout_3;
	//QVBoxLayout *verticalLayout_Actions;
	//QHBoxLayout *horizontalLayout_2;
	//QPushButton *pushButtonProfiles;
	//QPushButton *pushButtonPackages;
	//QPushButton *pushButtonTools;
	//QSpacerItem *horizontalSpacer_3;
	//QLineEdit *lineEditAction;
	//QTreeWidget *treeWidgetActions;
	//QFrame *line_4;
	//QVBoxLayout *verticalLayout_Targets;
	//QHBoxLayout *horizontalLayout_4;
	//QPushButton *pushButtonAD;
	//QPushButton *pushButtonFiles;
	//QSpacerItem *horizontalSpacer_2;
	//QLineEdit *lineEditComputer;
	//QListWidget *listWidgetTargets;
	//QFrame *line_2;
	//QTreeView *treeViewJobs;
	//QFrame *line_1;
	//QFrame *frameProc;
	//QMenuBar *menuBar;
	//QMenu *menuFile;
	//QMenu *menuSettings;
	//QMenu *menuAbout;
	//QToolBar *mainToolBar;
	//QStatusBar *statusBar;
}

// ====SLOTS===================================================================
void on_actionExit_triggered(){
	exit(0);
}
//void d008::on_actionPreferences_triggered(){ }
//void d008::on_actionActions_triggered(){ }
//void d008::on_actionAbout_triggered(){ }
void d008::on_actionExit_triggered() { exit(0); /*for now, just exit*/ }
void d008::on_pushButtonRun_clicked(){ }
void d008::on_pushButtonCancel_clicked(){ }
void d008::on_lineEditCmd_textEdited(QString cmdQstr){  }
//void d008::on_pushButtonProfiles_clicked(){ }
//void d008::on_pushButtonPackages_clicked(){ }
//void d008::on_pushButtonTools_clicked(){ }
void d008::on_lineEditAction_textEdited(QString actionQstr){ }
//void d008::on_treeViewActions_(){ }
//void d008::on_pushButtonAD_clicked(){ }
//void d008::on_pushButtonFiles_clicked(){ }
void d008::on_lineEditComputer_textEdited(QString targetQstr){ }
//void d008::on_listViewComputers_(){ }
//void d008::on_treeViewJobs_(){ }
void d008::on_treeWidgetActions_itemClicked(QTreeWidgetItem* qtwitem, int i) {
	QString qtitle = ui.treeWidgetActions->currentItem()->text(0);
	QString qitem = qtwitem->data(0, Qt::UserRole).toString();
	ui.lineEditAction->clear();
	ui.lineEditAction->setText("Hello cruel world\0");
	//ui.lineEditCmd->setText(QString::fromStdString(config.actionsini));
}
//void d008::on_frameProc_(){ }
//void d008::on_menuBar_(){ }
//void d008::on_menuFile_(){ }
//void d008::on_menuSettings_(){ }
//void d008::on_menuAbout_triggered(){ }
//void d008::on_mainToolBar_(){ }
//void d008::on_statusBar_(){ }
