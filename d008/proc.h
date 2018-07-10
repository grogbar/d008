#pragma once
#include <stdio.h>
#include <string>
#include <qstring.h>
#include <qdebug.h>

#include <ctime>
#include <windows.h>
#include <Tchar.h>

#define DESKTOP_ALL (DESKTOP_READOBJECTS | DESKTOP_CREATEWINDOW | \
DESKTOP_CREATEMENU | DESKTOP_HOOKCONTROL | DESKTOP_JOURNALRECORD | \
DESKTOP_JOURNALPLAYBACK | DESKTOP_ENUMERATE | DESKTOP_WRITEOBJECTS | \
DESKTOP_SWITCHDESKTOP | STANDARD_RIGHTS_REQUIRED)

#define WINSTA_ALL (WINSTA_ENUMDESKTOPS | WINSTA_READATTRIBUTES | \
WINSTA_ACCESSCLIPBOARD | WINSTA_CREATEDESKTOP | \
WINSTA_WRITEATTRIBUTES | WINSTA_ACCESSGLOBALATOMS | \
WINSTA_EXITWINDOWS | WINSTA_ENUMERATE | WINSTA_READSCREEN | \
STANDARD_RIGHTS_REQUIRED)

#define GENERIC_ACCESS (GENERIC_READ | GENERIC_WRITE | \
GENERIC_EXECUTE | GENERIC_ALL)


class Proc
{
public:
	Proc();
	~Proc();
	int run();
	void Proc::set_command(QString& cmd);

	//VARIABLES
	QString command;

};
/*	int run(QString& cmd);
	DWORD Proc::GetCurrentSessionId();
	bool LaunchProcess(const char *process_path);

private:
	BOOL Proc::StartInteractiveClientProcess(
		LPTSTR lpszUsername,    // client to log on
		LPTSTR lpszDomain,      // domain of client's account
		LPTSTR lpszPassword,    // client's password
		LPTSTR lpCommandLine    // command line to execute
	);
	BOOL Proc::AddAceToWindowStation(HWINSTA hwinsta, PSID psid);
	BOOL Proc::AddAceToDesktop(HDESK hdesk, PSID psid);

	// VAR's
	QString command;	// The final command to run
	//QString t;		// The target machine
	int	pid;
	int rc;			// return code
	std::clock_t	start;
	std::clock_t	end;
*/



//[psexec]
//type = shell
//shell = psexec.exe \\%TARGET% -u %USER% -p %PASSWORD% %OPTIONS% %COMMAND%
//
//[powershell]
//type = shell
//shell = powershell.exe - Computername %TARGET% -CREDENTIAL %USER% -FILE %COMMAND%