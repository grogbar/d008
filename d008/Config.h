#pragma once
#include <qmap.h>
#include <QString>
#include <qfile.h>
#include <qtextstream.h>
#include <qdebug.h>
#include "toolkit.h"


class Config
{
public:
	Config();
	~Config();
	int write();
	int read(QMap<QString, QString> *item);
	int parse();

	// [GENERAL]
	
	QString		currentpath;
	QString		targetfiles;
	QString		binpath;
	QString		objectsini;
	QString		sourcepath;
	QString		stagingpath;
	QString		stagingunc;
	QString		packageroot; //	PACKAGEROOT = "$DEPLOY$-"
	int			packagedigits;
	QString		pathseparator;// = '\'
	QString		targetvar; // = "%TARGET%"
	int			procmax; // = 4
	QString		iniFile;

	bool viewall = 0;
	bool viewshells = 0;
	bool viewgroups = 1;
	bool viewpackages = 1;
	bool viewtools = 1;
	QMap<QString, QString>	entry;  // config.ini file 

private:

};

