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
	QVector<QString>	objects;
	QVector<QString>	targets;
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
	QVector<QString> objectList;
	QVector<Proc*>	procs;
	Ui::d008Class	&ui;
	static unsigned	requestNumber;
	QTreeWidgetItem *jobTree;

public:
	Q();
	Q(Object &objects, Ui::d008Class &ui);
	~Q();
	void init_threads(int number);
	QVector<QString> get_objectList(QString title);
	void add(QString title, QVector<QString>& targets, qaction_t action);
	QVector<QString> Q::get_prerequisites(QString title);
	QVector<QString> Q::get_postrequisites(QString title);
	QVector<QString> Q::get_objectOrder(QString title, int depth = 0);
	void Q::enable();
	void Q::disable();
	

};

