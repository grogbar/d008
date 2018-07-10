#include "Q.h"




Q::Q(Object& obj, Ui::d008Class& ui) : objects(obj), ui(ui)
{
	//isRunning = false;
}

unsigned Q::requestNumber = 1;


Q::~Q()
{
	workers = {};

}


void Q::init_threads(int number) { 
	for (int i = 0; i < number; i++) { procs.append(new Proc()); }
}
QVector<QString> Q::get_prerequisites(QString title) {
	QVector<QString> list = {};
	if (objects.groups.contains(title))
		list = objects.groups[title].objects;
	else if (objects.packages.contains(title))
		list = objects.packages[title].prerequisites;
	else if (objects.tools.contains(title))
		list = objects.tools[title].prerequisites;
	for (auto pre : list)
		list += get_prerequisites(pre);
	return list;
}
QVector<QString> Q::get_postrequisites(QString title) {
	QVector<QString> list;
	if (objects.tools.contains(title))
		list = objects.tools[title].postrequisites;
	else if (objects.tools.contains(title))
		list = objects.packages[title].postrequisites;
	else if (objects.tools.contains(title))
		list = objects.groups[title].postrequisites;
	for (auto pre : list)
		list += get_postrequisites(pre);
	return list;
}
QVector<QString> Q::get_objectOrder(QString title, int depth) {
	if (!depth) objectList = {}; // 
	depth++; 
	QVector<QString> post = get_postrequisites(title);
	QVector<QString> pre  = get_prerequisites(title);

	depth--; // if 0 then first time through
	return pre;
}
QVector<QString> Q::get_objectList(QString title) {
	QVector<QString> list;
	list = get_prerequisites(title), title, get_postrequisites(title);
	return list;
}
void Q::enable() {}
void Q::disable() {}
void Q::add(QString title, QVector<QString>& targets, qaction_t action) {
	q_t request;
	request.number = requestNumber++;
	request.title = title;
	request.objects = get_objectList(title);
	request.targets = targets;

	//ui.treeWidgetObjects->clear();
	ui.treeWidgetJobs->setColumnCount(1);
	ui.treeWidgetJobs->setHeaderLabels(QStringList() << "Jobs");
	QList<QTreeWidgetItem *> jobTreeItems;
	QTreeWidgetItem *item;

	// The Job
	QString jobText = title;
	jobTree = new QTreeWidgetItem(ui.treeWidgetJobs);
	jobTree->setText(0, jobText);
	ui.treeWidgetObjects->addTopLevelItem(jobTree);
	for (auto targety : objects.OSs.keys()) {
		jobTree->addChild(new QTreeWidgetItem(targets));
	}
}

	
	// Tools 
	//objectTreeTools = new QTreeWidgetItem(ui.treeWidgetObjects);
	//objectTreeTools->setText(0, "tools");
	//ui.treeWidgetObjects->addTopLevelItem(objectTreeTools);
	//for (auto key : objects.tools.keys()) {
	//	objectTreeTools->addChild(new QTreeWidgetItem(QStringList(key)));
	//}

	return;
}

//struct q_t {
//	int					number;
//	QString				title;
//  QVector<QString>	objects;
//	QVector<QString>	targets;
//	qaction_t			action;
//};
