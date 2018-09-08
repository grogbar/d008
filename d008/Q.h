#pragma once
/*
This is structered as a queue of processes to run
*/
#include <qstring.h>
#include <QVector>
#include "proc.h"
#include <stdio.h>
#include <mutex>
#include <thread>
#include "ui_d008.h"
#include "object.h"

enum qaction_t { RUN,STAGE,INSTALL,UNINSTALL};

struct q_t {
	int					number;
	QString				title;
	QStringList	objects;
	QStringList	targets;
	qaction_t			action;
};


class Q
{
private:
	// VAR's
	bool			isRunning;
	QVector<Proc>	workers;
	QVector<q_t>	requests;
	Object&			objects;
	QStringList objectList;
	QVector<Proc*>	procs;
	Ui::d008Class	&ui;
	static unsigned	requestNumber;
	QList<QTreeWidgetItem *> jobTree;
	QTreeWidgetItem *jobItem;

public:
	Q();
	Q(Object &objects, Ui::d008Class &ui);
	~Q();
	void init_threads(int number);
	void init_tree();
	QStringList get_objectList(QString title);
	void add(QString title, QStringList& targets, qaction_t action);
	QStringList Q::get_prerequisites(QString title);
	QStringList Q::get_postrequisites(QString title);
	QStringList Q::set_objectOrder(QString title, int depth = 0);
	void Q::enable();
	void Q::disable();
	

};

