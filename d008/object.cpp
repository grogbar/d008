//#include "stdafx.h"
#include "object.h"
#include "toolkit.h"

// Defining static vars
//QStringList Object::vConfigData;
//QStringList Object::vObjectData;

bool isList(QString str) {
	unsigned i = 0;
	if (str.at(0) == '#' || str.at(0) == ';') return false; // I'm a comment
	while (str.at(i) != '=' && i < str.length() - 2) { i++; }
	if (str.at(i + 1) == '(')
		return true;
	else
		return false;
}


Object::Object()
{
	QStringList vObjectData;
}

Object::~Object()
{
}


int Object::read(const QString FileName) {
	QString line;
	QFile file(FileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qInfo() << "I can't open the frackin file: config.ini. " << file.errorString() << '\n';
		return 2;
	}

	QTextStream in(&file);
	while (!in.atEnd()) {
		line = in.readLine().trimmed();
		vObjectData.push_back( line );
	}
	return 0;
}

int Object::write(const QString FileName) {
	// Add blank line between objects
	for (auto i : vObjects) {
		
	}
	return 0;
}

bool Object::parse_sList(QStringList &list, const QString linein, bool flag_inList) {
	bool flag_q = false;  // '
	bool flag_qq = false;  // "
	bool flag_br = false;  // []
	bool flag_inquotes = false; // we are in quotes
	bool flag_quoted = false; // were quotes used?
	int start = 0;
	int end = 0;
	QString line = linein.trimmed();
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
			end = i-1;
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
		else if (!flag_inquotes && (line.at(i) == ',' || line.at(i) == ';' || line.at(i) == ')')) { // comma or semicolon separated values
			if (!flag_quoted) end = i-1;
			if (i && (end - start + 1>0)) 
				list.push_back(line.mid(start, end - start + 1 ));
			if (line.at(i) == ')') flag_inList = false;

			start = i + 1;
			flag_quoted = false;
		}
		// find end of list
		else if ( !flag_inquotes && line.at(i) == ')') {
			if (!flag_quoted) end = i-1;
			flag_inList = false;
			if (i & end-start+1>0) list.push_back(line.mid(start, end - start +1));  // if first char is not ')'
		}
		else if (i == line.length() - 1) {
			end = i-1;
			if (i && end - start + 1>0) list.push_back(line.mid(start, end - start + 1));
		}

	}
	return flag_inList;
}

bool Object::parse_nList(QVector<int> &list, const QString line, bool flag_inList) {
	unsigned start = 0;
	unsigned end = 0;
	size_t sz;//QString::size_type sz
	for (unsigned i = 0; i<line.length(); ++i)
	{
		if (!flag_inList && line.at(i) == '(') {
			flag_inList = true;
			start = i + 1;
		}
		else if (!flag_inList) {} // Do nothing until list starts.
		else if (line.at(i) == ',' || line.at(i) == ';' || line.at(i) ==')') {
			end = i - 1;
			list.push_back(line.mid(start, end - start + 1).toInt());
			flag_inList = (line.at(i) == ')') ? false : true;
			start = i + 1;
		}

	}
	return flag_inList;
}

int Object::parse() {
	enum lists { NONE, ACTIONS, INSTALL, UNINSTALL, PREREQUISITES, POSTREQUISITES, SUCCESS, INSTALLED, COMMENT };
	lists listType = NONE;
	object_t newObject = {};
	object_defaults(newObject);
	bool inList = false;
	size_t sz;    //QString::size_type sz
	QString temp = "source=";
	int testing = 0;
	for (auto data : Object::vObjectData) {
		//qInfo() << i << '\n';
		// Recover from bad package by assuming end of package after blank line
		// if '[' and not in list then start of object.  Save index as we can't start loading 

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
			
			newObject = {};
			listType = NONE;
			inList = false;
		}
		else if (data.at(0) == '#' || data.at(0) == ';') {
			newObject.comment.push_back(data);
		}
		else if (inList) {
			switch (listType) {
			case ACTIONS:        inList = parse_sList(newObject.objects, data, true); break;
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
				if (newObject.type != NONE) {
					switch (newObject.type) {
					case TOOL:		load_tool(newObject); break;
					case PACKAGE:	load_package(newObject); break;
					case GROUP:		load_group(newObject); break;
					case SHELL:		load_shell(newObject); break;
					case COMMENT:	load_comments(newObject); break;
					}
					newObject = {};
					listType = NONE;
					inList = false;
				}
				newObject.title = data.mid(1, data.length() - 2);
			}
			else if (data.left(7).toLower() == "source=") {
				newObject.source = data.mid(7, (data.length() - 7));
			}
			else if (data.left(11).toLower() == "packagenum=") { //Keep this unique as it becomes a directory name
				newObject.packageNum = data.mid(11, data.length()-11).toInt();
			}
			else if (data.left(6).toLower() == "shell=") {
				newObject.shell = data.mid(7, (data.length() - 8));
			}
			else if (data.left(10).toLower() == "category=") {
				newObject.category = data.mid(10, (data.length() - 11));
			}
			else if (data.left(9).toLower() == "command=") {
				newObject.command = data.mid(9, (data.length() - 10));
			}
			else if (data.left(5).toLower() == "type=") {
				if      (data.contains("tool")) { newObject.type = TOOL; }
				else if (data.contains("package")) { newObject.type = PACKAGE; }
				else if (data.contains("group")  ) { newObject.type = GROUP; }
				else if (data.contains("shell")  ) { newObject.type = SHELL; }
				else if (data.contains("os")     ) { newObject.type = OS; }
				else { newObject.type = PACKAGE; }
			}
			else if (data.left(16).toLower() == "expectedruntime=") {
			}
			else if (data.left(14).toLower() == "failedruntime=") {
			}
			else if (data.left(8).toLower() == "enabled=") {
				if (data.at(8) == '0') newObject.enabled = false;
				else newObject.enabled = true;
			}
			else if (data.left(10).toLower() == "installed=") {
				newObject.installed.push_back(data.mid(10, (data.length() - 10)));
			}
		}
		else if (data.left(8).toLower() == "objects=" || inList && listType == ACTIONS) {
			inList = parse_sList(newObject.objects, data.mid(8, data.length() - 8), false);
			listType = ACTIONS;
		}
		else if (data.left(13).toLower() == "uninstallcmd=" || inList && listType == UNINSTALL) {
			inList = parse_sList(newObject.uninstall, data.mid(13, data.length() - 13), false);
			listType = UNINSTALL;
		}
		else if (data.left(11).toLower() == "installcmd=" || inList && listType == INSTALL ) {
			inList = parse_sList(newObject.install, data.mid(11, data.length() - 11), false);
			listType = INSTALL;
		}
		else if (data.left(14).toLower() == "prerequisites=" || inList && listType == PREREQUISITES) {
			inList = parse_sList(newObject.prerequisites, data.mid(14, data.length() - 14), false);
			listType = PREREQUISITES;
		}
		else if (data.left(15).toLower() == "postrequisites=" || inList && listType == POSTREQUISITES) {
			inList = parse_sList(newObject.postrequisites, data.mid(15, data.length() - 15), false);
			listType = POSTREQUISITES;
		}
		else if (data.left(8).toLower() == "success=" || inList && listType == SUCCESS) {
			inList = parse_nList(newObject.success, data.mid(7, data.length() - 7), false);
			listType = SUCCESS;
		}
		else if (data.left(10).toLower() == "installed=" || inList && listType == INSTALLED) {
			inList = parse_sList(newObject.installed, data.mid(10, data.length() - 10), false);
			listType = INSTALLED;
		}
		else {
			qDebug() << "NOT FOUND:" << data << '\n';
			qInfo() << "????: " << data << '\n';
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

void Object::print_object_t(const object_t all) {
	if (!all.title.isEmpty())		qInfo() << "\n[" << all.title << "]" << '\n';
	if (all.type) qInfo() << "    type=" << all.type << '\n';
	if (!all.source.isEmpty())		qInfo() << "    source=\"" << all.source << "\"" << '\n';
	if (all.packageNum)	qInfo() << "    packageNum=" << all.packageNum << '\n';
	if (!all.objects.isEmpty()) {
		qInfo() << "    objects=(";
		int i = 0;
		for (auto e : all.objects) {
			if (i) qInfo() << ",";
			qInfo() << "[" << e << "]";
			i++;
		}
		qInfo() << ")" << '\n';
	}
	if (!all.install.empty()) {
		qInfo() << "    installcmd=(";
		int i = 0;
		for (auto e : all.install) {
			if (i) qInfo() << ",";
			qInfo() << e ;
			i++;
		}
		qInfo() << ")" << '\n';
	}
	if (!all.uninstall.empty())	{
		qInfo() << "    uninstall=(";
		int i = 0;
		for (auto e : all.uninstall) {
			if (i) qInfo() << ",";
			qInfo() << "\"" << e << "\"";
			i++;
		}
		qInfo() << ")" << '\n';
	}
	if (!all.prerequisites.empty())	{
		qInfo() << "    prerequisites=(";
		int i = 0;
		for (auto e : all.prerequisites) {
			if (i) qInfo() << ",";
			qInfo() << "\"" << e << "\"";
			i++;
		}
		qInfo() << ")" << '\n';
	}
	if (!all.postrequisites.empty()) {
		qInfo() << "    postrequisites=(";
		int i = 0;
		for (auto e : all.postrequisites) {
			if (i) qInfo() << ",";
			qInfo() << "\"" << e << "\"";
			i++;
		}
		qInfo() << ")" << '\n';
	}
	if (!all.enabled)			qInfo() << "    enabled=false" << '\n';
	else						qInfo() << "    enabled=true" << '\n';
	if (!all.success.empty())	{
		qInfo() << "    success=(";
		int i = 0;
		for (auto e : all.success) {
			if (i) qInfo() << ",";
			qInfo() << "\"" << e << "\"";
			i++;
		}
		qInfo() << ")" << '\n';
	}
	if (!all.expectedRuntime)
		qInfo() << "    expectedRuntime=(" << all.expectedRuntime << ")" << '\n';
	if (!all.failedRuntime)
		qInfo() << "    failedRuntime=" << all.failedRuntime << '\n';
	if (!all.shell.isEmpty())
		qInfo() << "shell=" << all.shell << '\n';
	if (!all.installed.empty())	{
		qInfo() << "    installed=(";
		int i = 0;
		for (auto e : all.installed) {
			if (i) qInfo() << ",";
			qInfo() << "\"" << e << "\"";
			i++;
		}
		qInfo() << ")" << '\n';
	}
	if (!all.category.isEmpty())	qInfo() << "    category=(" << all.category << '\n';
	if (!all.command.isEmpty())	qInfo() << "    command=" << all.command << '\n';
	if (!all.comment.isEmpty())	{
		for (auto e : all.comment) {
			qInfo()  <<  e << '\n';
		}
	}
	if (!all.index)				qInfo() << "    index=" << all.index << '\n';
}

void Object::load_shell(const object_t obj){
	shell_t s;
	//s.title = obj.title;
	s.shell = obj.shell;
	s.index = obj.index;
	shells[obj.title] = s;
}
void Object::load_group(const object_t obj){
	group_t g;
	//g.title = obj.title;
	g.objects = obj.objects;
	g.index = obj.index;
	groups[obj.title] = g;
}
void Object::load_package(const object_t obj){

	package_t p;
	//p.title = obj.title;
	p.packageNum = obj.packageNum;
	p.source = obj.source;
	p.install = obj.install;
	p.uninstall = obj.uninstall;
	p.prerequisites = obj.prerequisites;
	p.postrequisites = obj.postrequisites;
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
void Object::load_tool(const object_t obj){
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
void Object::load_comments(const object_t obj) {
	comment_t c;
	c.comment = obj.comment;
	c.index = obj.index;
}
void Object::object_defaults(object_t &o) {
	o.type = NONE;
	o.enabled = true;
	o.expectedRuntime = 300;
	o.failedRuntime = 900;
}

/*private:
	QStringList vConfigData;
	QStringList vObjectData;



*/