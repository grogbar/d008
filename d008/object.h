#pragma once
#ifndef object_h
#define object_h
#endif

#include <qfile.h>
//#include <iostream>
#include <qtextstream.h>
#include <QVector>
#include <QString>
#include <map>
#include <iterator>
using std::istream_iterator;
#include <algorithm>
#include <qdebug.h>
#include "toolkit.h"


enum ObjTypes { NONE,TOOL,PACKAGE,GROUP,SHELL,OS,COMMENT };


struct os_t {
	QString					title;
	QString					shell;
	QString					local;
	QString					remote;
	QString					cp;
	bool						enabled;
	QVector<QString>	comment;
	int							index;
};

struct shell_t {
	QString					title;
	QString					shell;
	bool					enabled;
	QVector<QString>	comment;
	int						index;
};

struct comment_t {
	QVector<QString>	comment;
	int index;
};

struct group_t {
	QString title;
	QVector<QString>	objects;
	bool				enabled;
	int					index;
	QVector<QString>	prerequisites;
	QVector<QString>	postrequisites;
	QVector<QString>	comment;
};

struct package_t {
	QString				title;
	unsigned			packageNum;
	QString				source;
	QVector<QString>	install;
	QVector<QString>	uninstall;
	QVector<QString>	prerequisites;
	QVector<QString>	postrequisites;
	bool				enabled;
	QVector<int>		success;
	int					expectedRuntime;
	int					failedRuntime;
	QString				shell;
	QVector<QString>	installed;
	QString				category;
	int					index;
	QVector<QString>	comment;
};

struct tool_t {
	QString					title;
	QString					shell;
	QString					command;
	int							expectedRuntime;
	int							failedRuntime;
	int							index;
	QVector<QString>	prerequisites;
	QVector<QString>	postrequisites;
	QVector<QString>	comment;
};

struct object_t {
	QString					title;
	ObjTypes				type;
	bool						enabled;
	unsigned					packageNum;
	QString					source;
	QVector<QString>	objects;
	QVector<QString>	install;
	QVector<QString>	uninstall;
	QVector<QString>	prerequisites;
	QVector<QString>	postrequisites;
	QVector<int>			success;
	int							expectedRuntime;
	int							failedRuntime;
	QString					shell;
	QVector<QString>	installed;
	QString					category;
	QString					command;
	QVector<QString>	comment;
	int							index;
};


class Object
{
public:
	Object();
	~Object();
	int read(const QString FileName);
	int write(const QString FileName);
	int parse();

	QMap<QString, os_t>			OSs;
	QMap<QString, shell_t>		shells;
	QMap<QString,group_t>		groups;
	QMap<QString,package_t>		packages;
	QMap<QString,tool_t>		tools;
	QVector<comment_t>			comment;


private:
	// Functions
	bool parse_sList(QVector<QString> &list, const QString line, bool flag_inList); // flag_inList = false unless not finished in previous run
	bool parse_nList(QVector<int> &list, const QString line, bool flag_inList); // flag_inList = false unless not finished in previous run
	void print_object_t(const object_t object);
	void load_shell(const object_t o);
	void load_group(const object_t o);
	void load_package(const object_t o);
	void load_tool(const object_t o);
	void load_comments(const object_t o);
	void object_defaults(object_t &o);
	// Vars
	QVector<QString> vConfigData;
	QVector<QString> vObjectData;
	QVector<std::pair<QString, int>> vObjects;


};
