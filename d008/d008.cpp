#include "d008.h"
#include "toolkit.h"



d008::d008(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

int d008::init() {
	//Objects
	// [GENERAL]
	config.currentpath	= QString::fromStdString(GetCurrentWorkingDir());
	config.targetfiles  = config.currentpath;
	config.binpath = config.currentpath + "\\bin";
	config.objectsini = config.currentpath + "\\objects.ini";
	config.stagingpath	= "c:\\windows\\installer\\";
	config.stagingunc	= "\\\\%TARGET%\\c$\\windows\\installer\\";
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

	QString configini = config.currentpath + "\\config.ini";
	if (int rc = config.read(&mConfigData)) exit(rc);
	//config.parse();
	//read_config();
	parse_config();
	objects.read( config.objectsini );
	objects.parse();
	load_objectTree();
	read_targetFile(".\\workstations.txt");
	link_signals_and_slots();
	// INIT UI
	fontReg.setBold(false);
	fontReg.setWeight(50);
	fontBold.setBold(true);
	fontBold.setWeight(75);

	ui.actionCheck->setDisabled(true); // enable when both target and object
	ui.actionStage->setDisabled(true); // enable when both target and object
	ui.actionInstall->setDisabled(true); // enable when both target and object
	ui.actionUninstall->setDisabled(true); // enable when both target and object
	ui.actionLogs->setDisabled(true); // enable when both target and object
	ui.pushButtonRun->setDisabled(true); // enable when both target and tool object
	ui.pushButtonStage->setDisabled(true); // enable when both target and group/package object
	ui.pushButtonInstall->setDisabled(true); // enable when both target and group/package object
	ui.pushButtonUninstall->setDisabled(true); // enable when both target and group/package object
	ui.pushButtonLogs->setDisabled(true); // enable when target selected
	ui.pushButtonCancel->setDisabled(true); // enable when proc runs
	objectTreeOSs->setHidden(true);
	objectTreeShells->setHidden(true);
	ui.pushButtonGroups->setFont(fontBold);
	ui.pushButtonPackages->setFont(fontBold);
	ui.pushButtonTools->setFont(fontBold);
	ui.listWidgetTargets->setSelectionMode(QAbstractItemView::MultiSelection);
	q.init_tree();
	// Instantiate Q
	// q = Q( objects , ui );  // in header?

	//addTreeRoot(QString name, QString description);
	//addTreeChild(QTreeWidgetItem *parent,	QString name, QString description);
	return 0;
}

// ====MEMBER FUNCTIONS=========================================================
int d008::write_config() { 
	return 0;  
}

int d008::read_config() {

	int i, cnum;
	QString text, line, ckey, key, val;

	cnum = 0;


	QFile configFile(".\\config.ini");
	if (!configFile.open(QIODevice::ReadOnly)) {
		qInfo() << "I can't open the frackin file: .\\config.ini. "
			<< configFile.errorString() << '\n';
		return 2;
	}

	while (!configFile.atEnd()) {
		line = configFile.readLine().trimmed();
		if (line.isEmpty()) {}
		else if ((line.at(0) == '#' || line.at(0) == ';')) {
			ckey = "C" + QString::number(cnum);
			mConfigData[ckey] = line.trimmed();
			cnum++;
		}
		else {
			i = 0;
			while (line.at(i) != '=' && i < line.length() - 1) i++;
			if (i < line.length() - 1) {
				key = line.left(i).trimmed();
				val = line.right(i + 1).trimmed();
				mConfigData[key] = val;
			}
		}

	}
	return 0;
}

int d008::parse_config() {
	QMap<QString, QString>::iterator item = mConfigData.begin();
	for (auto item : mConfigData.keys()) {
		if      (item.toUpper() == "STAGINGPATH") config.stagingpath = mConfigData.value(item).trimmed();
		else if (item.toUpper() == "TARGETFILES") config.targetfiles = mConfigData.value(item).trimmed();
		else if (item.toUpper() == "STAGINGUNC") config.stagingunc = mConfigData.value(item).trimmed();
		else if (item.toUpper() == "ACTIONSINI") config.objectsini = mConfigData.value(item).trimmed();
		else if (item.toUpper() == "PACKAGEROOT") config.packageroot = mConfigData.value(item).trimmed();
		else if (item.toUpper() == "PACKAGEDIGITS")  config.packagedigits = mConfigData.value(item).toInt();
		else if (item.toUpper() == "STAGINGUNC") config.stagingunc = mConfigData.value(item).trimmed();
		else if (item.toUpper() == "TARGETVAR") config.targetvar = mConfigData.value(item).trimmed();
		else if (item.toUpper() == "PROCMAX") config.procmax = mConfigData.value(item).toInt();
		else if (item.toUpper() == "VIEWALL") config.viewall			= (mConfigData.value(item).trimmed() == "1") ? 1 : 0;
		else if (item.toUpper() == "VIEWSHELLS") config.viewshells		= (mConfigData.value(item).trimmed() == "1") ? 1 : 0;
		else if (item.toUpper() == "VIEWGROUPS") config.viewgroups		= (mConfigData.value(item).trimmed() == "1") ? 1 : 0;
		else if (item.toUpper() == "VIEWPACKAGES") config.viewpackages	= (mConfigData.value(item).trimmed() == "1") ? 1 : 0;
		else if (item.toUpper() == "VIEWTOOLS") config.viewtools		= (mConfigData.value(item).trimmed() == "1") ? 1 : 0;
	}
	return 0;
}
int d008::read_targetFile(QString FileName) {
	QString line;


	QFile targetFile(FileName);
	if (!targetFile.open(QIODevice::ReadOnly)) {
		qInfo() << "I can't open the frackin file: " << FileName << targetFile.errorString() << '\n';
		return 2;
	}

	ui.listWidgetTargets->clear();
	while (!targetFile.atEnd()) {
		line = targetFile.readLine().trimmed();
		//targets.push_back(line.trimmed());
		if (line.trimmed().length() > 0)
			ui.listWidgetTargets->addItem(line.trimmed());
	}
	return 0;
}
void d008::load_objectTree(void) {
	//ui.treeWidgetObjects->clear();
	ui.treeWidgetObjects->setColumnCount(1);
	ui.treeWidgetObjects->setHeaderLabels(QStringList() << "Objects");
	QList<QTreeWidgetItem *> objectTreeItems;
	QTreeWidgetItem *item;

	// OSs
	objectTreeOSs = new QTreeWidgetItem(ui.treeWidgetObjects);
	objectTreeOSs->setText(0, "OSs");
	ui.treeWidgetObjects->addTopLevelItem(objectTreeOSs);
	for (auto key : objects.OSs.keys())	{
		objectTreeOSs->addChild(new QTreeWidgetItem(QStringList(key))); 
	}

	// Shells 
	objectTreeShells = new QTreeWidgetItem(ui.treeWidgetObjects);
	objectTreeShells->setText(0, "shells");
	ui.treeWidgetObjects->addTopLevelItem(objectTreeShells);
	for (auto key : objects.shells.keys()) {
		objectTreeShells->addChild(new QTreeWidgetItem(QStringList(key)));
	}

	// Groups 
	objectTreeGroups = new QTreeWidgetItem(ui.treeWidgetObjects);
	objectTreeGroups->setText(0, "groups");
	ui.treeWidgetObjects->addTopLevelItem(objectTreeGroups);
	for (auto key : objects.groups.keys()) {
		objectTreeGroups->addChild(new QTreeWidgetItem(QStringList(key)));
	}

	// Packages
	objectTreePackages = new QTreeWidgetItem(ui.treeWidgetObjects);
	objectTreePackages->setText(0, "packages");
	ui.treeWidgetObjects->addTopLevelItem(objectTreePackages);
	for (auto key : objects.packages.keys()) {
		objectTreePackages->addChild(new QTreeWidgetItem(QStringList(key)));
	}

	// Tools 
	objectTreeTools = new QTreeWidgetItem(ui.treeWidgetObjects);
	objectTreeTools->setText(0, "tools");
	ui.treeWidgetObjects->addTopLevelItem(objectTreeTools);
	for (auto key : objects.tools.keys()) {
		objectTreeTools->addChild(new QTreeWidgetItem(QStringList(key)));
	}

	return;
}
void d008::load_object(QString parent , QString title) {
	object = {};
	qDebug() << parent;
	qDebug() << title;
	//enum types { NONE, TOOL, PACKAGE, GROUP, SHELL, OS, COMMENT };
	if (parent == "groups") {
		object.type = GROUP;
		object.title = title;
		object.objects = objects.groups[object.title].objects;
	}
	else if (parent == "packages") {
		object.type = PACKAGE;
		object.title = title;
		object.packageNum = objects.packages[object.title].packageNum;
		object.source = objects.packages[object.title].source;
		object.install = objects.packages[object.title].install;
		object.uninstall = objects.packages[object.title].uninstall;
		object.prerequisites = objects.packages[object.title].prerequisites;
		object.enabled = objects.packages[object.title].enabled;
		object.success = objects.packages[object.title].success;
		object.expectedRuntime = objects.packages[object.title].expectedRuntime;
		object.failedRuntime = objects.packages[object.title].failedRuntime;
		object.shell = objects.packages[object.title].shell;
		object.installed = objects.packages[object.title].installed;
		object.category = objects.packages[object.title].category;
		object.index = objects.packages[object.title].index;
	}
	else if (parent == "tools") {
		object.shell = objects.tools[object.title].shell;
		object.command = objects.tools[object.title].command;
		object.expectedRuntime = objects.tools[object.title].expectedRuntime;
		object.failedRuntime = objects.tools[object.title].failedRuntime;
		object.prerequisites = objects.tools[object.title].prerequisites;
		object.postrequisites = objects.tools[object.title].postrequisites;
	}
	return;
}
//void d008::update_objectTree(void) {
//	QTreeWidgetItemIterator it(ui.treeWidgetObjects);
	//while (*it) {
	//	if ((*it)->text(0) == "searched")
	//		break;
	//	++it;
	//}
//}
void d008::link_signals_and_slots(void) {
	connect(ui.treeWidgetObjects, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(on_treeWidgetObjects_itemClicked(QTreeWidgetItem* item, int)) );
	
	//QObject::connect(treeWidgetObjects, SIGNAL(clicked(QModelIndex)), lineEditCmd, SLOT(paste()));

	//QObject *actionPreferences;
	//QObject *actionObjects;
	//QObject *actionAbout;
	//QObject *actionExit;
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
	//QVBoxLayout *verticalLayout_Objects;
	//QHBoxLayout *horizontalLayout_2;
	//QPushButton *pushButtonProfiles;
	//QPushButton *pushButtonPackages;
	//QPushButton *pushButtonTools;
	//QSpacerItem *horizontalSpacer_3;
	//QLineEdit *lineEditObject;
	//QTreeWidget *treeWidgetObjects;
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
	// If processes running... ARE YOU SURE?!
	// 
	exit(0);
}
void d008::on_actionExit_triggered() { exit(0); /*for now, just exit*/ }
//void d008::on_actionPreferences_triggered(){ }
//void d008::on_actionObjects_triggered(){ }
//void d008::on_actionAbout_triggered(){ }

void d008::on_lineEditCmd_textEdited(QString cmdQstr){  }
void d008::on_lineEditObject_textChanged(QString objectQstr) {
	QTreeWidgetItemIterator it(ui.treeWidgetObjects);
	while (*it) {
		if (!(*it)->parent()) {
			if (objectQstr.isEmpty()) (*it)->setExpanded(false);
			else (*it)->setExpanded(true);
		}
		else if (!(*it)->childCount() && (*it)->text(0).contains(objectQstr))
			(*it)->setHidden(false);
		else
			(*it)->setHidden(true);
		++it;
	}
}
void d008::on_lineEditComputer_textEdited(QString targetQstr) {
	/*
	Options:
	-Add this item to selection list on enter (And select???)  I rather like this one.
	-Only this item?
	-Only list those items matched? (like objects)
	*/


}

void d008::on_treeWidgetObjects_itemSelectionChanged(void) { 
	QTreeWidgetItem	*a = ui.treeWidgetObjects->currentItem();
	///object = selection.at(0);
	//QString qtitle = ui.treeWidgetObjects->currentItem()->text(0);
	//QString qitem = qtwitem->data(0, Qt::UserRole).toString();
	ui.lineEditCmd->clear();
	if (a->parent()) {
		// Get object name 
		QString title  = ui.treeWidgetObjects->currentItem()->text(0);
		QString parent = ui.treeWidgetObjects->currentItem()->parent()->text(0);
		load_object(parent, title);
		if (a->parent()->text(0) == "packages" ) {
			ui.pushButtonRun->setEnabled(false);
			ui.pushButtonStage->setEnabled(true);
			ui.pushButtonInstall->setEnabled(true);
			ui.pushButtonUninstall->setEnabled(true);
			ui.lineEditCmd->setText(title);
		}
		else if (a->parent()->text(0) == "groups") {
			ui.pushButtonRun->setEnabled(false);
			ui.pushButtonStage->setEnabled(true);
			ui.pushButtonInstall->setEnabled(true);
			ui.pushButtonUninstall->setEnabled(true);


		}
		else if (a->parent()->text(0) == "tools") {
			ui.pushButtonRun->setEnabled(true);
			ui.pushButtonStage->setEnabled(false);
			ui.pushButtonInstall->setEnabled(false);
			ui.pushButtonUninstall->setEnabled(false);
		}
	}
}
void d008::on_listWidgetTargets_itemSelectionChanged() {
	targets.clear();
	foreach(QListWidgetItem* item, ui.listWidgetTargets->selectedItems())
		targets += item->text();
	qDebug() << targets;
}

void d008::on_pushButtonGroups_toggled(bool checked){
	if (checked) {
		objectTreeGroups->setHidden(false);
		ui.pushButtonGroups->setFont(fontBold);
	}
	else {
		objectTreeGroups->setHidden(true);
		ui.pushButtonGroups->setFont(fontReg);
	}
}
void d008::on_pushButtonPackages_toggled(bool checked){
	if (checked) {
		ui.pushButtonStage->setHidden(false);
		ui.pushButtonInstall->setHidden(false);
		ui.pushButtonUninstall->setHidden(false);
		objectTreePackages->setHidden(false);
		ui.pushButtonPackages->setFont(fontBold);
	}
	else {
		ui.pushButtonStage->setHidden(true);
		ui.pushButtonInstall->setHidden(true);
		ui.pushButtonUninstall->setHidden(true);
		objectTreePackages->setHidden(true);
		ui.pushButtonPackages->setFont(fontReg);
	}
}
void d008::on_pushButtonTools_toggled(bool checked){ 
	if (checked) {
		ui.pushButtonRun->setHidden(false);
		objectTreeTools->setHidden(false);
		ui.pushButtonTools->setFont(fontBold);
	} 
	else {
		ui.pushButtonRun->setHidden(true);
		objectTreeTools->setHidden(true);
		ui.pushButtonTools->setFont(fontReg);
	}
}
void d008::on_pushButtonAll_toggled(bool checked) { 
	if (checked) {
		ui.pushButtonGroups->setChecked(true);
		ui.pushButtonPackages->setChecked(true);
		ui.pushButtonTools->setChecked(true);
		objectTreeOSs->setHidden(false);
		objectTreeShells->setHidden(false);
		objectTreeGroups->setHidden(false);
		objectTreePackages->setHidden(false);
		objectTreeTools->setHidden(false);
		ui.pushButtonGroups->setFont(fontBold);
		ui.pushButtonPackages->setFont(fontBold);
		ui.pushButtonTools->setFont(fontBold);
		ui.pushButtonAll->setFont(fontBold);
	}
	else {
		objectTreeOSs->setHidden(true);
		objectTreeShells->setHidden(true);
		ui.pushButtonAll->setFont(fontReg);
	}
}
void d008::on_pushButtonRun_clicked() { 
	q.add(object.title, targets, RUN);
}
void d008::on_pushButtonStage_clicked() { 
	q.add(object.title, targets, STAGE);
}
void d008::on_pushButtonInstall_clicked() { 
	q.add( object.title, targets, INSTALL); 
}
void d008::on_pushButtonUninstall_clicked() { 
	q.add(object.title, targets, UNINSTALL);
}
void d008::on_pushButtonLogs_clicked() { }
void d008::on_pushButtonCancel_clicked() { } // maybe replace this with rclick cancel on Q item
void d008::on_pushButtonAD_clicked(){ }
void d008::on_pushButtonFiles_clicked(){ 
	QString filename = QFileDialog::getOpenFileName(this, "Target Computers", config.targetfiles, "Text File (*.txt)");
	ui.listWidgetTargets->clear();
	read_targetFile(filename);
}

//void d008::on_treeViewJobs_(){ }
//void d008::on_frameProc_(){ }
//void d008::on_menuBar_(){ }
//void d008::on_menuFile_(){ }
//void d008::on_menuSettings_(){ }
//void d008::on_menuAbout_triggered(){ }
//void d008::on_mainToolBar_(){ }
//void d008::on_statusBar_(){ }
//QAction *objectCheck;
//QAction *objectStage;
//QAction *objectInstall;
//QAction *objectUninstall;
//QAction *objectStageInstall;
//QAction *objectLogs;
