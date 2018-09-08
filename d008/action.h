#pragma once
#ifndef action_h
#define action_h
#endif

#include <iostream>
#include <fstream>
#include <QVector>
#include <QString>
#include <map>
#include <iterator>
using std::istream_iterator;
#include <algorithm>
#include "toolkit.h"


enum types { NONE,TOOL,PACKAGE,GROUP,SHELL,OS,COMMENT };


struct os_t {
	QString					title;
	QString					shell;
	QString					local;
	QString					remote;
	QString					cp;
	bool						enabled;
	std::vector<QString>	comment;
	int							index;
};

struct shell_t {
	QString					title;
	QString					shell;
	bool					enabled;
	std::vector<QString>	comment;
	int						index;
};

struct comment_t {
	std::vector<QString>	comment;
	int index;
};

struct group_t {
	QString title;
	std::vector<QString>	actions;
	bool					enabled;
	int index;
	std::vector<QString>	comment;
};

struct package_t {
	QString					title;
	unsigned				packageNum;
	QString					source;
	std::vector<QString>	install;
	std::vector<QString>	uninstall;
	std::vector<QString>	prerequisites;
	std::vector<QString>	postrequisites;
	bool						enabled;
	std::vector<int>			success;
	int							expectedRuntime;
	int							failedRuntime;
	QString					shell;
	std::vector<QString>	installed;
	QString					category;
	int							index;
	std::vector<QString>	comment;
};

struct tool_t {
	QString					title;
	QString					shell;
	QString					command;
	int							expectedRuntime;
	int							failedRuntime;
	int							index;
	std::vector<QString>	prerequisites;
	std::vector<QString>	postrequisites;
	std::vector<QString>	comment;
};

struct action_t {
	QString					title;
	types						type;
	bool						enabled;
	unsigned					packageNum;
	QString					source;
	std::vector<QString>	actions;
	std::vector<QString>	install;
	std::vector<QString>	uninstall;
	std::vector<QString>	prerequisites;
	std::vector<QString>	postrequisites;
	std::vector<int>			success;
	int							expectedRuntime;
	int							failedRuntime;
	QString					shell;
	std::vector<QString>	installed;
	QString					category;
	QString					command;
	std::vector<QString>	comment;
	int							index;
};


class Action
{
public:
	Action();
	~Action();
	int read_actions(const QString FileName);
	int write_actions(const QString FileName);
	int parse_config();
	int parse_actions();

	std::map<QString, os_t>			OSs;
	std::map<QString, shell_t>		shells;
	std::map<QString,group_t>		groups;
	std::map<QString,package_t>		packages;
	std::map<QString,tool_t>		tools;
	std::vector<comment_t>				comment;


private:
	// Functions
	bool parse_sList(std::vector<QString> &list, const QString line, bool flag_inList); // flag_inList = false unless not finished in previous run
	bool parse_nList(std::vector<int> &list, const QString line, bool flag_inList); // flag_inList = false unless not finished in previous run
	void print_action_t(const action_t action);
	void load_shell(const action_t o);
	void load_group(const action_t o);
	void load_package(const action_t o);
	void load_tool(const action_t o);
	void load_comments(const action_t o);
	void action_defaults(action_t &o);
	// Vars
	std::vector<QString> vConfigData;
	std::vector<QString> vActionData;
	std::vector<std::pair<QString, int>> vActions;


};
