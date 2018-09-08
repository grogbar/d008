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
void Q::init_tree() {
	ui.treeWidgetJobs->clear();
	ui.treeWidgetJobs->setColumnCount(1);
	ui.treeWidgetJobs->setHeaderLabels(QStringList("Jobs"));
}
QStringList Q::get_prerequisites(QString title) {
	QStringList list = {};
	if (objects.groups.contains(title))
		list = QStringList(objects.groups[title].objects);
	else if (objects.packages.contains(title)) {
		package_t test = objects.packages[title];
		list = objects.packages[title].prerequisites;
	}
	else if (objects.tools.contains(title))
		list = objects.tools[title].prerequisites;
	for (auto pre : list)
		list += get_prerequisites(pre);
	return list;
}
QStringList Q::get_postrequisites(QString title) {
	QStringList list;
	if (objects.tools.contains(title))
		list = objects.tools[title].postrequisites;
	else if (objects.packages.contains(title))
		list = objects.packages[title].postrequisites;
	for (auto post : list)
		list += get_postrequisites(post);
	return list;
}
QStringList Q::set_objectOrder(QString title, int depth) {
	if (!depth) objectList.clear();
	depth++; 
	QStringList post = get_postrequisites(title);
	QStringList pre  = get_prerequisites(title);
	QStringList order = pre << title << post;
	for (auto a : order) {
		for (auto b : order) {
			if (a == b) {} // do nothing
			else if ( get_postrequisites(a).contains(b) ) {

			}
			else if (get_prerequisites)
		}
	}
	depth--; // if 0 then first time through
	return order;
}
QStringList Q::get_objectList(QString title) {
	QStringList list;
	list << get_prerequisites(title) << title << get_postrequisites(title);
	return list;
}
void Q::enable() {}
void Q::disable() {}
void Q::add(QString title, QStringList& targets, qaction_t action) {
	q_t request;
	request.number = requestNumber++;
	request.title = title;
	request.objects = get_objectList(title);
	request.targets = targets;


	// The Job
	QTreeWidgetItem *jobItem;
	QString jobText = title;
	QStringList objs = get_objectList(title);
	jobItem = new QTreeWidgetItem(ui.treeWidgetJobs);
	jobItem->setText(0, jobText);
	ui.treeWidgetJobs->addTopLevelItem(jobItem);
	// The targets
	for (auto target : targets) {
		QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(target));
		// list each object for each child
		for (auto obj : objs) {
			child->addChild(new QTreeWidgetItem(QStringList(obj)));
		}
		jobItem->addChild(child);
	}
	
	//ui.treeWidgetObjects->addTopLevelItem(jobTree);
	//for (auto targety : objects.OSs.keys()) {
	//	jobTree->addChild(new QTreeWidgetItem(targets));
	//}
}
