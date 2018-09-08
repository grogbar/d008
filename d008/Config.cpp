#include "Config.h"


Config::Config()
{
	currentpath = QString::fromStdString(GetCurrentWorkingDir());
	targetfiles = currentpath;
	binpath = currentpath + "\bin";
	objectsini = currentpath + "\\objects.ini";
	stagingpath = "c:\\windows\\installer\\";
	stagingunc = "//%TARGET%//c$//windows//installer//";
	packageroot = "$DEPLOY$-";
	packagedigits = 6;
	targetvar = "%TARGET%";
	procmax = 4;
	// [TARGETS]
	viewall = 0;
	viewshells = 0;
	viewgroups = 1;
	viewpackages = 1;
	viewtools = 1;
	iniFile = currentpath + "\\config.ini";

}


Config::~Config()
{
}

int  Config::write() { 
	//QFile file(iniFile);
	QFile file(currentpath + "config.txt"); // testing
	int i, cnum;
	QString text, line, ckey, key, val;

	cnum = 0;
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		qInfo() << "Could not write to " << currentpath + "config.txt";
		return 2;

	QTextStream out(&file);
	
	qInfo() << "Write better code here. I want the original to be updated, vs replaced";
	QRegExp numbers("\\d*");  // a digit (\d), zero or more times (*)
	for (auto e : entry.keys())
	{
		if (e.at(0) == 'C' && numbers.exactMatch(e.right(1))) { out << '#' << entry.value(e) << '\n'; }
		else { out << e << '=' << entry.value(e); }
	}
	return 0;
}
int  Config::read(QMap<QString,QString> *entry) {
	QFile file(iniFile);
	int i, cnum;
	QString text, line, ckey, key, val;

	cnum = 0;
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		int err = file.error();
		qInfo() << "I can't open the frackin file: config.ini. " << file.errorString() << ":" << err << '\n';
		return 2;
	}

	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine().trimmed();

		if (line.isEmpty()) {}
		else if ((line.at(0) == '#' || line.at(0) == ';')) {
			ckey = "C" + QString::number(cnum);
			(*entry)[ckey] = line;
			cnum++;
		}
		else {
			i = 0;
			while (line.at(i) != '=' && i<line.length() - 1) i++;
			if (i < line.length() - 1) {
				key = line.left(i); 
				val = line.right(line.length()-i-1);
				(*entry)[key.trimmed()] = val.trimmed();
			}
		}

	}
	file.close();
	return 0;
}
int  Config::parse() {
	QMap<QString, QString>::iterator item = entry.begin();
//	while (item != entry.end()) {
	for (auto item : entry.keys()) {
		if (item.toUpper() == "STAGINGPATH") stagingpath = entry.value(item).trimmed();
		else if (item.toUpper() == "TARGETFILES") targetfiles = entry.value(item).trimmed();
		else if (item.toUpper() == "STAGINGUNC") stagingunc = entry.value(item).trimmed();
		else if (item.toUpper() == "OBJECTSINI") objectsini = entry.value(item).trimmed();
		else if (item.toUpper() == "PACKAGEROOT") packageroot = entry.value(item).trimmed();
		else if (item.toUpper() == "PACKAGEDIGITS")  packagedigits = entry.value(item).trimmed().toInt();
		else if (item.toUpper() == "STAGINGUNC") stagingunc = entry.value(item).trimmed();
		else if (item.toUpper() == "TARGETVAR") targetvar = entry.value(item).trimmed();
		else if (item.toUpper() == "PROCMAX") procmax = entry.value(item).trimmed().toInt();
		else if (item.toUpper() == "VIEWALL") viewall = (entry.value(item).trimmed() == "1") ? 1 : 0;
		else if (item.toUpper() == "VIEWSHELLS") viewshells = (entry.value(item).trimmed() == "1") ? 1 : 0;
		else if (item.toUpper() == "VIEWGROUPS") viewgroups = (entry.value(item).trimmed() == "1") ? 1 : 0;
		else if (item.toUpper() == "VIEWPACKAGES") viewpackages = (entry.value(item).trimmed() == "1") ? 1 : 0;
		else if (item.toUpper() == "VIEWTOOLS") viewtools = (entry.value(item).trimmed() == "1") ? 1 : 0;
		//item++;
	}
	return 0;
}
