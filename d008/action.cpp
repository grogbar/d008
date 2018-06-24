//#include "stdafx.h"
#include "action.h"
#include "toolkit.h"

// Defining static vars
//std::vector<std::string> Action::vConfigData;
//std::vector<std::string> Action::vActionData;

bool isList(std::string str) {
	unsigned i = 0;
	if (str.at(0) == '#' || str.at(0) == ';') return false; // I'm a comment
	while (str.at(i) != '=' && i < str.length() - 2) { i++; }
	if (str.at(i + 1) == '(')
		return true;
	else
		return false;
}

Action::Action()
{
	std::vector<std::string> vActionData;
}

Action::~Action()
{
}


int Action::read_actions(const std::string FileName) {
	std::ifstream actionFile(FileName);


	std::string line;
	while (std::getline(actionFile, line))
	{
		vActionData.push_back( trim(line) );
	}
	return 0;
}

int Action::write_actions(const std::string FileName) {
	// Add blank line between actions
	for (auto i : vActions) {
		
	}
	return 0;
}

int Action::parse_config() { return 0; }

bool Action::parse_sList(std::vector<std::string> &list, const std::string linein, bool flag_inList) {
	bool flag_q = false;  // '
	bool flag_qq = false;  // "
	bool flag_br = false;  // []
	bool flag_inquotes = false; // we are in quotes
	bool flag_quoted = false; // were quotes used?
	int start = 0;
	int end = 0;
	std::string line = trim(linein);
	for (unsigned i = 0; i<line.length(); i++)
	{
		if (!flag_inList && line.at(i) == '(' ) {
			flag_inList = true;
			start = i + 1;
		}
		else if (!flag_inList) {} // Do nothing until list starts.
		// single quotes
		else if (!flag_inquotes && line.at(i) == '\'') { // enter single quote
			flag_q = true;
			flag_inquotes = true;
			flag_quoted = true;
			start = i + 1;
			while (line.at(i + 1) != '\'' && i<line.length()-1) i++;
		}
		else if (flag_q && line.at(i) == '\'' && line.at(i - 1) != '\\') { // exit single quote
			flag_q = false;
			flag_inquotes = false;
			end = i;
		}
		// double quotes
		else if (!flag_inquotes && line.at(i) == '"') { //enter double quote
			flag_qq = true;
			flag_inquotes = true;
			flag_quoted = true;
			start = i + 1;
			while (line.at(i + 1) != '"' && i<line.length() - 1) i++;
		}
		else if (flag_qq && line.at(i) == '"' && line.at(i - 1) != '\\') { // exit double quote
			flag_qq = false;
			flag_inquotes = false;
			end = i-1;
		}
		// brackets
		else if (!flag_inquotes && !flag_inquotes && !flag_qq && !flag_br && line.at(i) == '[') { // enter bracket
			flag_br = true;
			flag_inquotes = true;
			flag_quoted = true;
			start = i + 1;
			while (line.at(i + 1) != ']' && i<line.length() - 1) i++;
		}
		else if (flag_br && line.at(i) == ']' && line.at(i - 1) != '\\') { // exit bracket
			flag_br = false;
			flag_inquotes = false;
			end = i - 1;
		}
		// find separators
		else if (!flag_inquotes && (line.at(i) == ',' || line.at(i) == ';')) { // comma or semicolon separated values
			if (!flag_quoted) end = i-1;
			if (i & end - start + 1>0) list.push_back(line.substr(start, end - start + 1 ));

			start = i + 1;
			flag_quoted = false;
		}
		// find end of list
		else if ( !flag_inquotes && line.at(i) == ')') {
			if (!flag_quoted) end = i-1;
			flag_inList = false;
			if (i & end-start+1>0) list.push_back(line.substr(start, end - start +1));  // if first char is not ')'
		}
		else if (i == line.length() - 1) {
			end = i-1;
			if (i && end - start + 1>0) list.push_back(line.substr(start, end - start + 1));
		}

	}
	return flag_inList;
}

bool Action::parse_nList(std::vector<int> &list, const std::string line, bool flag_inList) {
	unsigned start = 0;
	unsigned end = 0;
	size_t sz;//std::string::size_type sz
	for (unsigned i = 0; i<line.length(); ++i)
	{
		if (!flag_inList && line.at(i) == '(') {
			flag_inList = true;
			start = i + 1;
		}
		else if (!flag_inList) {} // Do nothing until list starts.
		else if (line.at(i) == ',' || line.at(i) == ';') {
			list.push_back(std::stoi(line.substr(start, end - start + 1),&sz));
			start = i + 1;
		}
		else if (flag_inList && line.at(i) == ')') {
			flag_inList = false;
			list.push_back(std::stoi(line.substr(start, end - start + 1), &sz));
		}

	}
	return flag_inList;
}

int Action::parse_actions() {
	enum lists { NONE, ACTIONS, INSTALL, UNINSTALL, PREREQUISITES, POSTREQUISITES, SUCCESS, INSTALLED, COMMENT };
	lists listType = NONE;
	action_t newObject = {};
	action_defaults(newObject);
	bool inList = false;
	size_t sz;    //std::string::size_type sz
	std::string temp = "source=";
	int testing = 0;
	for (auto data : Action::vActionData) {
		//std::cout << i << std::endl;
		// Recover from bad package by assuming end of package after blank line
		// if '[' and not in list then start of action.  Save index as we can't start loading 

		if (data.length() == 0) {
			// save record
			switch (newObject.type) {
			case TOOL:		load_tool(newObject); break;
			case PACKAGE:	load_package(newObject); break;
			case GROUP:		load_group(newObject); break;
			case SHELL:		load_shell(newObject); break;
			case COMMENT:	load_comments(newObject); break;
			case NONE:		load_comments(newObject); break;
			}
			
			// testing 
			print_action_t(newObject);
			//testing++;
			//if (testing > 40) {
			//	std::cin.get();
			//	exit(0);
			//}
			// testing ----end 


			newObject = {};
			listType = NONE;
			inList = false;
		}
		else if (data.at(0) == '#' || data.at(0) == ';') {
			newObject.comment.push_back(data);
		}
		else if (inList) {
			switch (listType) {
			case ACTIONS:        inList = parse_sList(newObject.actions, data, true); break;
			case INSTALL:        inList = parse_sList(newObject.install, data, true); break;
			case UNINSTALL:      inList = parse_sList(newObject.uninstall, data, true); break;
			case PREREQUISITES:  inList = parse_sList(newObject.prerequisites, data, true); break;
			case POSTREQUISITES: inList = parse_sList(newObject.postrequisites, data, true); break;
			case SUCCESS:        inList = parse_nList(newObject.success, data, true); break;
			case INSTALLED:      inList = parse_sList(newObject.installed, data, true); break;
			case COMMENT:        inList = parse_sList(newObject.comment, data, true); break;
			}

		}
		else if ( !isList(data) ) {
			if (data.at(0) == '[' && data.at(data.length()-1)==']' )  {
				print_action_t(newObject);
				switch (newObject.type) {
				case TOOL:		load_tool(newObject); break;
				case PACKAGE:	load_package(newObject); break;
				case GROUP:		load_group(newObject); break;
				case SHELL:		load_shell(newObject); break;
				case COMMENT:	load_comments(newObject); break;
				case NONE:		load_comments(newObject); break;
				}
				newObject = {};
				listType = NONE;
				inList = false;


				newObject = {};
				newObject.title = data.substr(1, data.length() - 2);
			}
			else if (!icompare(data.substr(0, 7), std::string("source="))) {
				newObject.source = data.substr(7, (data.length() - 7));
			}
			else if (!icompare(data.substr(0, 11), std::string("packagenum="))) {
				newObject.packageNum = std::stoi(data.substr(11, data.length()-11), &sz);
			}
			else if (!icompare(data.substr(0, 6), std::string("shell="))) {
				newObject.shell = data.substr(7, (data.length() - 8));
			}
			else if (!icompare(data.substr(0, 9), std::string("category="))) {
				newObject.category = data.substr(10, (data.length() - 11));
			}
			else if (!icompare(data.substr(0, 8), std::string("command="))) {
				newObject.command = data.substr(9, (data.length() - 10));
			}
			else if (!icompare(data.substr(0, 5), std::string("type="))) {
				if      (data.find("tool")    != std::string::npos) { newObject.type = TOOL; }
				else if (data.find("package") != std::string::npos) { newObject.type = PACKAGE; }
				else if (data.find("group")   != std::string::npos) { newObject.type = GROUP; }
				else if (data.find("shell")   != std::string::npos) { newObject.type = SHELL; }
				else { newObject.type = PACKAGE; }
			}
			else if (!icompare(data.substr(0, 16), std::string("expectedruntime="))) {
			}
			else if (!icompare(data.substr(0, 14), std::string("failedruntime="))) {
			}
			else if (!icompare(data.substr(0, 8), std::string("enabled="))) {
				if (data.at(8) == '0') newObject.enabled = false;
				else newObject.enabled = true;
			}
			else if (!icompare(data.substr(0, 10), std::string("installed="))) {
				newObject.installed.push_back(data.substr(10, (data.length() - 10)));
			}
		}
		else if (!icompare(data.substr(0, 8), std::string("actions=")) || listType == ACTIONS) {
			listType = ACTIONS;
			inList = parse_sList(newObject.actions, data.substr(8, data.length() - 8), false);
		}
		else if (!icompare(data.substr(0, 13), std::string("uninstallcmd=")) || listType == UNINSTALL) {
			listType = UNINSTALL;
			inList = parse_sList(newObject.uninstall, data.substr(13, data.length() - 13), false);
		}
		else if (!icompare(data.substr(0, 11), std::string("installcmd=")) || listType == INSTALL ) {
			listType = INSTALL;
			inList = parse_sList(newObject.install, data.substr(11, data.length() - 11), false);
		}
		else if (!icompare(data.substr(0,14), std::string("prerequisites=")) || listType == PREREQUISITES) {
			listType = PREREQUISITES;
			inList = parse_sList(newObject.prerequisites, data.substr(14, data.length() - 14), false);
		}
		else if (!icompare(data.substr(0,15), std::string("postrequisites=")) || listType == POSTREQUISITES) {
			listType = POSTREQUISITES;
			inList = parse_sList(newObject.postrequisites, data.substr(15, data.length() - 15), false);
		}
		else if (!icompare(data.substr(0, 7), std::string("sucess=")) || listType == SUCCESS) {
			listType = SUCCESS;
			inList = parse_nList(newObject.success, data.substr(7, data.length() - 7), false);
		}
		else if (!icompare(data.substr(0,10), std::string("installed=")) || listType == INSTALLED) {
			listType = INSTALLED;
			inList = parse_sList(newObject.installed, data.substr(10, data.length() - 10), false);
		}
		else {
			std::cout << "????: " << data << std::endl;
			std::cin.get(); 
			exit(0);
		}
	}
	// save the last object 
	switch (newObject.type) {
	case TOOL:		load_tool(newObject); break;
	case PACKAGE:	load_package(newObject); break;
	case GROUP:		load_group(newObject); break;
	case SHELL:		load_shell(newObject); break;
	case COMMENT:	load_comments(newObject); break;
	case NONE:		load_comments(newObject); break;
	}
	return 0;
}

void Action::print_action_t(const action_t all) {
	if (!all.title.empty())		std::cout << "\n[" << all.title << "]" << std::endl;
	if (all.type) std::cout << "    type=" << all.type << std::endl;
	if (!all.source.empty())		std::cout << "    source=\"" << all.source << "\"" << std::endl;
	if (all.packageNum)	std::cout << "    packageNum=" << all.packageNum << std::endl;
	if (!all.actions.empty()) {
		std::cout << "    actions=(";
		int i = 0;
		for (auto e : all.actions) {
			if (i) std::cout << ",";
			std::cout << "[" << e << "]";
			i++;
		}
		std::cout << ")" << std::endl;
	}
	if (!all.install.empty()) {
		std::cout << "    installcmd=(";
		int i = 0;
		for (auto e : all.install) {
			if (i) std::cout << ",";
			std::cout << e ;
			i++;
		}
		std::cout << ")" << std::endl;
	}
	if (!all.uninstall.empty())	{
		std::cout << "    uninstall=(";
		int i = 0;
		for (auto e : all.uninstall) {
			if (i) std::cout << ",";
			std::cout << "\"" << e << "\"";
			i++;
		}
		std::cout << ")" << std::endl;
	}
	if (!all.prerequisites.empty())	{
		std::cout << "    prerequisites=(";
		int i = 0;
		for (auto e : all.prerequisites) {
			if (i) std::cout << ",";
			std::cout << "\"" << e << "\"";
			i++;
		}
		std::cout << ")" << std::endl;
	}
	if (!all.postrequisites.empty()) {
		std::cout << "    postrequisites=(";
		int i = 0;
		for (auto e : all.postrequisites) {
			if (i) std::cout << ",";
			std::cout << "\"" << e << "\"";
			i++;
		}
		std::cout << ")" << std::endl;
	}
	if (!all.enabled)			std::cout << "    enabled=false" << std::endl;
	else						std::cout << "    enabled=true" << std::endl;
	if (!all.success.empty())	{
		std::cout << "    success=(";
		int i = 0;
		for (auto e : all.success) {
			if (i) std::cout << ",";
			std::cout << "\"" << e << "\"";
			i++;
		}
		std::cout << ")" << std::endl;
	}
	if (!all.expectedRuntime)
		std::cout << "    expectedRuntime=(" << all.expectedRuntime << ")" << std::endl;
	if (!all.failedRuntime)
		std::cout << "    failedRuntime=" << all.failedRuntime << std::endl;
	if (!all.shell.empty())
		std::cout << "shell=" << all.shell << std::endl;
	if (!all.installed.empty())	{
		std::cout << "    installed=(";
		int i = 0;
		for (auto e : all.installed) {
			if (i) std::cout << ",";
			std::cout << "\"" << e << "\"";
			i++;
		}
		std::cout << ")" << std::endl;
	}
	if (!all.category.empty())	std::cout << "    category=(" << all.category << std::endl;
	if (!all.command.empty())	std::cout << "    command=" << all.command << std::endl;
	if (!all.comment.empty())	{
		for (auto e : all.comment) {
			std::cout  <<  e << std::endl;
		}
	}
	if (!all.index)				std::cout << "    index=" << all.index << std::endl;
}

void Action::load_shell(const action_t obj){
	shell_t s;
	//s.title = obj.title;
	s.shell = obj.shell;
	s.index = obj.index;
	shells[obj.title] = s;
}
void Action::load_group(const action_t obj){
	group_t g;
	//g.title = obj.title;
	g.actions = obj.actions;
	g.index = obj.index;
	groups[obj.title] = g;
}
void Action::load_package(const action_t obj){

	package_t p;
	//p.title = obj.title;
	p.packageNum = obj.packageNum;
	p.source = obj.source;
	p.install = obj.install;
	p.uninstall = obj.uninstall;
	p.prerequisites = obj.prerequisites;
	p.enabled = obj.enabled;
	p.success = obj.success;
	p.expectedRuntime = obj.expectedRuntime;
	p.failedRuntime = obj.failedRuntime;
	p.shell = obj.shell;
	p.installed = obj.installed;
	p.category = obj.category;
	p.index = obj.index;

	packages[obj.title] = p;
}
void Action::load_tool(const action_t obj){
	tool_t t;
	//t.title = obj.title;
	t.shell = obj.shell;
	t.command = obj.command;
	t.expectedRuntime = obj.expectedRuntime;
	t.failedRuntime = obj.failedRuntime;
	t.index = obj.index;
	t.prerequisites = obj.prerequisites;
	t.postrequisites = obj.postrequisites;
	tools[obj.title] = t;
}
void Action::load_comments(const action_t obj) {
	comment_t c;
	c.comment = obj.comment;
	c.index = obj.index;
}
void Action::action_defaults(action_t &o) {
	o.type = NONE;
	o.enabled = true;
	o.expectedRuntime = 300;
	o.failedRuntime = 900;
}

/*private:
	std::vector<std::string> vConfigData;
	std::vector<std::string> vActionData;



*/