#pragma once
#ifndef action_h
#define action_h
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iterator>
using std::istream_iterator;
#include <algorithm>
#include "toolkit.h"


enum types { NONE,TOOL,PACKAGE,GROUP,SHELL,COMMENT };


struct os_t {
	std::string					title;
	std::string					shell;
	std::string					local;
	std::string					remote;
	std::string					cp;
	bool						enabled;
	std::vector<std::string>	comment;
	int							index;
};

struct shell_t {
	std::string					title;
	std::string					shell;
	bool						enabled;
	std::vector<std::string>	comment;
	int							index;
};

struct comment_t {
	std::vector<std::string>	comment;
	int index;
};

struct group_t {
	std::string title;
	std::vector<std::string>	actions;
	bool						enabled;
	int index;
	std::vector<std::string>	comment;
};

struct package_t {
	std::string					title;
	unsigned					packageNum;
	std::string					source;
	std::vector<std::string>	install;
	std::vector<std::string>	uninstall;
	std::vector<std::string>	prerequisites;
	std::vector<std::string>	postrequisites;
	bool						enabled;
	std::vector<int>			success;
	int							expectedRuntime;
	int							failedRuntime;
	std::string					shell;
	std::vector<std::string>	installed;
	std::string					category;
	int							index;
	std::vector<std::string>	comment;
};

struct tool_t {
	std::string					title;
	std::string					shell;
	std::string					command;
	int							expectedRuntime;
	int							failedRuntime;
	int							index;
	std::vector<std::string>	prerequisites;
	std::vector<std::string>	postrequisites;
	std::vector<std::string>	comment;
};

struct action_t {
	std::string					title;
	types						type;
	bool						enabled;
	unsigned					packageNum;
	std::string					source;
	std::vector<std::string>	actions;
	std::vector<std::string>	install;
	std::vector<std::string>	uninstall;
	std::vector<std::string>	prerequisites;
	std::vector<std::string>	postrequisites;
	std::vector<int>			success;
	int							expectedRuntime;
	int							failedRuntime;
	std::string					shell;
	std::vector<std::string>	installed;
	std::string					category;
	std::string					command;
	std::vector<std::string>	comment;
	int							index;
};


class Action
{
public:
	Action();
	~Action();
	int read_actions(const std::string FileName);
	int write_actions(const std::string FileName);
	int parse_config();
	int parse_actions();

	std::map<std::string, os_t>			OSs;
	std::map<std::string, shell_t>		shells;
	std::map<std::string,group_t>		groups;
	std::map<std::string,package_t>		packages;
	std::map<std::string,tool_t>		tools;
	std::vector<comment_t>				comment;


private:
	// Functions
	bool parse_sList(std::vector<std::string> &list, const std::string line, bool flag_inList); // flag_inList = false unless not finished in previous run
	bool parse_nList(std::vector<int> &list, const std::string line, bool flag_inList); // flag_inList = false unless not finished in previous run
	void print_action_t(const action_t action);
	void load_shell(const action_t o);
	void load_group(const action_t o);
	void load_package(const action_t o);
	void load_tool(const action_t o);
	void load_comments(const action_t o);
	void action_defaults(action_t &o);
	// Vars
	std::vector<std::string> vConfigData;
	std::vector<std::string> vActionData;
	std::vector<std::pair<std::string, int>> vActions;


};
