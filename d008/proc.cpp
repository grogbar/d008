#include "proc.h"
#include <synchapi.h>

Proc::Proc()
{
}


Proc::~Proc()
{
}

void Proc::set_command(QString& cmd) { command = cmd; }

int Proc::run() { 
	qDebug() << command << '\n';
	Sleep(15000);
	return 0;
}



/*
int Proc::run(QString& cmd) {


	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;
	if (CreateProcess(path, cmd.toStdString().c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
		CreateProcessAsUserW(
			_In_opt_ HANDLE hToken,
			_In_opt_ LPCWSTR lpApplicationName,
			_Inout_opt_ LPWSTR lpCommandLine,
			_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
			_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
			_In_ BOOL bInheritHandles,
			_In_ DWORD dwCreationFlags,
			_In_opt_ LPVOID lpEnvironment,
			_In_opt_ LPCWSTR lpCurrentDirectory,
			_In_ LPSTARTUPINFOW lpStartupInfo,
			_Out_ LPPROCESS_INFORMATION lpProcessInformation
		);



	{
		WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}
}

//Determine the session ID of current logged--on user:
DWORD Proc::GetCurrentSessionId()
{
	WTS_SESSION_INFO *pSessionInfo;
	DWORD n_sessions = 0;
	BOOL ok = WTSEnumerateSessions(WTS_CURRENT_SERVER, 0, 1, &pSessionInfo, &n_sessions);
	if (!ok)
		return 0;

	DWORD SessionId = 0;

	for (DWORD i = 0; i < n_sessions; ++i)
	{
		if (pSessionInfo[i].State == WTSActive)
		{
			SessionId = pSessionInfo[i].SessionId;
			break;
		}
	}

	WTSFreeMemory(pSessionInfo);
	return SessionId;
}

bool LaunchProcess(const char *process_path)
{
	DWORD SessionId = GetCurrentSessioId();
	if (SessionId == 0)    // no-one logged in
		return false;

	HANDLE hToken;
	BOOL ok = WTSQueryUserToken(SessionId, &hToken);
	if (!ok)
		return false;

	void *environment = NULL;
	ok = CreateEnvironmentBlock(&environment, hToken, TRUE);

	if (!ok)
	{
		CloseHandle(hToken);
		return false;
	}

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi = {};
	si.lpDesktop = "winsta0\\default";

	// Do NOT want to inherit handles here
	DWORD dwCreationFlags = NORMAL_PRIORITY_CLASS | CREATE_UNICODE_ENVIRONMENT;
	ok = CreateProcessAsUser(hToken, process_path, NULL, NULL, NULL, FALSE,
		dwCreationFlags, environment, NULL, &si, &pi);

	DestroyEnvironmentBlock(environment);
	CloseHandle(hToken);

	if (!ok)
		return false;

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	return true;
}

//void Proc::get_shell(QString shell) {
//	qDebug() << QString::fromStdString(shell);
//}
//QString Proc::get_command() { return command; }
//void Proc::set_command(QString cmd) { command = cmd; }
//
//void Proc::parse_command(void) {
//	bool bracketsfound = true; // This referrs to my finding a match for a known switch.  Not just a bracket
//	while (command.at(0) == '[' && bracketsfound) {
//		// [CMD]
//	}
//}
//void Proc::replace_user(QString &usr) {
//	replace("%USER%", usr);
//} // %USER%
//void Proc::replace_password(QString &pw) {
//	replace("%PASSWORD%", pw);
//} // %PASSWORD%
//void Proc::replace_options(QString &opt) {
//	replace("%OPTIONS%", opt);
//} // %OPTIONS%
//void Proc::replace(QString placeholder, QString newstr) {
//	size_t at = command.find(placeholder);
//	size_t len = placeholder.length();
//	command.replace(at, len, newstr);
//	return;
//}



//[psexec]
//type = shell
//shell = psexec.exe \\%TARGET% -u %USER% -p %PASSWORD% %OPTIONS% %COMMAND%
//
//[powershell]
//type = shell
//shell = powershell.exe - Computername %TARGET% -CREDENTIAL %USER% -FILE %COMMAND%






/*== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == =
MS version of fork()
https://msdn.microsoft.com/en-us/library/aa379608%28VS.85%29.aspx
== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == =*/
//#include <windows.h>
//#include <Tchar.h>
//
//#define DESKTOP_ALL (DESKTOP_READOBJECTS | DESKTOP_CREATEWINDOW | \
//DESKTOP_CREATEMENU | DESKTOP_HOOKCONTROL | DESKTOP_JOURNALRECORD | \
//DESKTOP_JOURNALPLAYBACK | DESKTOP_ENUMERATE | DESKTOP_WRITEOBJECTS | \
//DESKTOP_SWITCHDESKTOP | STANDARD_RIGHTS_REQUIRED)
//
//#define WINSTA_ALL (WINSTA_ENUMDESKTOPS | WINSTA_READATTRIBUTES | \
//WINSTA_ACCESSCLIPBOARD | WINSTA_CREATEDESKTOP | \
//WINSTA_WRITEATTRIBUTES | WINSTA_ACCESSGLOBALATOMS | \
//WINSTA_EXITWINDOWS | WINSTA_ENUMERATE | WINSTA_READSCREEN | \
//STANDARD_RIGHTS_REQUIRED)
//
//#define GENERIC_ACCESS (GENERIC_READ | GENERIC_WRITE | \
//GENERIC_EXECUTE | GENERIC_ALL)
//
//BOOL AddAceToWindowStation(HWINSTA hwinsta, PSID psid);
//
//BOOL AddAceToDesktop(HDESK hdesk, PSID psid);
//
//BOOL GetLogonSID(HANDLE hToken, PSID *ppsid);
//
//VOID FreeLogonSID(PSID *ppsid);
//

/*
BOOL Proc::StartInteractiveClientProcess(
	LPTSTR lpszUsername,    // client to log on
	LPTSTR lpszDomain,      // domain of client's account
	LPTSTR lpszPassword,    // client's password
	LPTSTR lpCommandLine    // command line to execute
)
{
	HANDLE      hToken;
	HDESK       hdesk = NULL;
	HWINSTA     hwinsta = NULL, hwinstaSave = NULL;
	PROCESS_INFORMATION pi;
	PSID pSid = NULL;
	STARTUPINFO si;
	BOOL bResult = FALSE;

	// Log the client on to the local computer.

	if (!LogonUser(
		lpszUsername,
		lpszDomain,
		lpszPassword,
		LOGON32_LOGON_INTERACTIVE,
		LOGON32_PROVIDER_DEFAULT,
		&hToken))
	{
		goto Cleanup;
	}

	// Save a handle to the caller's current window station.

	if ((hwinstaSave = GetProcessWindowStation()) == NULL)
		goto Cleanup;

	// Get a handle to the interactive window station.

	hwinsta = OpenWindowStation(
		_T("winsta0"),                   // the interactive window station 
		FALSE,                       // handle is not inheritable
		READ_CONTROL | WRITE_DAC);   // rights to read/write the DACL

	if (hwinsta == NULL)
		goto Cleanup;

	// To get the correct default desktop, set the caller's 
	// window station to the interactive window station.

	if (!SetProcessWindowStation(hwinsta))
		goto Cleanup;

	// Get a handle to the interactive desktop.

	hdesk = OpenDesktop(
		_T("default"),     // the interactive window station 
		0,             // no interaction with other desktop processes
		FALSE,         // handle is not inheritable
		READ_CONTROL | // request the rights to read and write the DACL
		WRITE_DAC |
		DESKTOP_WRITEOBJECTS |
		DESKTOP_READOBJECTS);

	// Restore the caller's window station.

	if (!SetProcessWindowStation(hwinstaSave))
		goto Cleanup;

	if (hdesk == NULL)
		goto Cleanup;

	// Get the SID for the client's logon session.

	if (!GetLogonSID(hToken, &pSid))
		goto Cleanup;

	// Allow logon SID full access to interactive window station.

	if (!AddAceToWindowStation(hwinsta, pSid))
		goto Cleanup;

	// Allow logon SID full access to interactive desktop.

	if (!AddAceToDesktop(hdesk, pSid))
		goto Cleanup;

	// Impersonate client to ensure access to executable file.

	if (!ImpersonateLoggedOnUser(hToken))
		goto Cleanup;

	// Initialize the STARTUPINFO structure.
	// Specify that the process runs in the interactive desktop.

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.lpDesktop = TEXT("winsta0\\default");

	// Launch the process in the client's logon session.

	bResult = CreateProcessAsUser(
		hToken,            // client's access token
		NULL,              // file to execute
		lpCommandLine,     // command line
		NULL,              // pointer to process SECURITY_ATTRIBUTES
		NULL,              // pointer to thread SECURITY_ATTRIBUTES
		FALSE,             // handles are not inheritable
		NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE,   // creation flags
		NULL,              // pointer to new environment block 
		NULL,              // name of current directory 
		&si,               // pointer to STARTUPINFO structure
		&pi                // receives information about new process
	);

	// End impersonation of client.

	RevertToSelf();

	if (bResult && pi.hProcess != INVALID_HANDLE_VALUE)
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
	}

	if (pi.hThread != INVALID_HANDLE_VALUE)
		CloseHandle(pi.hThread);

Cleanup:

	if (hwinstaSave != NULL)
		SetProcessWindowStation(hwinstaSave);

	// Free the buffer for the logon SID.

	if (pSid)
		FreeLogonSID(&pSid);

	// Close the handles to the interactive window station and desktop.

	if (hwinsta)
		CloseWindowStation(hwinsta);

	if (hdesk)
		CloseDesktop(hdesk);

	// Close the handle to the client's access token.

	if (hToken != INVALID_HANDLE_VALUE)
		CloseHandle(hToken);

	return bResult;
}

BOOL Proc::AddAceToWindowStation(HWINSTA hwinsta, PSID psid)
{
	ACCESS_ALLOWED_ACE   *pace = NULL;
	ACL_SIZE_INFORMATION aclSizeInfo;
	BOOL                 bDaclExist;
	BOOL                 bDaclPresent;
	BOOL                 bSuccess = FALSE;
	DWORD                dwNewAclSize;
	DWORD                dwSidSize = 0;
	DWORD                dwSdSizeNeeded;
	PACL                 pacl;
	PACL                 pNewAcl = NULL;
	PSECURITY_DESCRIPTOR psd = NULL;
	PSECURITY_DESCRIPTOR psdNew = NULL;
	PVOID                pTempAce;
	SECURITY_INFORMATION si = DACL_SECURITY_INFORMATION;
	unsigned int         i;

	__try
	{
		// Obtain the DACL for the window station.

		if (!GetUserObjectSecurity(
			hwinsta,
			&si,
			psd,
			dwSidSize,
			&dwSdSizeNeeded)
			)
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				psd = (PSECURITY_DESCRIPTOR)HeapAlloc(
					GetProcessHeap(),
					HEAP_ZERO_MEMORY,
					dwSdSizeNeeded);

				if (psd == NULL)
					__leave;

				psdNew = (PSECURITY_DESCRIPTOR)HeapAlloc(
					GetProcessHeap(),
					HEAP_ZERO_MEMORY,
					dwSdSizeNeeded);

				if (psdNew == NULL)
					__leave;

				dwSidSize = dwSdSizeNeeded;

				if (!GetUserObjectSecurity(
					hwinsta,
					&si,
					psd,
					dwSidSize,
					&dwSdSizeNeeded)
					)
					__leave;
			}
			else
				__leave;

		// Create a new DACL.

		if (!InitializeSecurityDescriptor(
			psdNew,
			SECURITY_DESCRIPTOR_REVISION)
			)
			__leave;

		// Get the DACL from the security descriptor.

		if (!GetSecurityDescriptorDacl(
			psd,
			&bDaclPresent,
			&pacl,
			&bDaclExist)
			)
			__leave;

		// Initialize the ACL.

		ZeroMemory(&aclSizeInfo, sizeof(ACL_SIZE_INFORMATION));
		aclSizeInfo.AclBytesInUse = sizeof(ACL);

		// Call only if the DACL is not NULL.

		if (pacl != NULL)
		{
			// get the file ACL size info
			if (!GetAclInformation(
				pacl,
				(LPVOID)&aclSizeInfo,
				sizeof(ACL_SIZE_INFORMATION),
				AclSizeInformation)
				)
				__leave;
		}

		// Compute the size of the new ACL.

		dwNewAclSize = aclSizeInfo.AclBytesInUse +
			(2 * sizeof(ACCESS_ALLOWED_ACE)) + (2 * GetLengthSid(psid)) -
			(2 * sizeof(DWORD));

		// Allocate memory for the new ACL.

		pNewAcl = (PACL)HeapAlloc(
			GetProcessHeap(),
			HEAP_ZERO_MEMORY,
			dwNewAclSize);

		if (pNewAcl == NULL)
			__leave;

		// Initialize the new DACL.

		if (!InitializeAcl(pNewAcl, dwNewAclSize, ACL_REVISION))
			__leave;

		// If DACL is present, copy it to a new DACL.

		if (bDaclPresent)
		{
			// Copy the ACEs to the new ACL.
			if (aclSizeInfo.AceCount)
			{
				for (i = 0; i < aclSizeInfo.AceCount; i++)
				{
					// Get an ACE.
					if (!GetAce(pacl, i, &pTempAce))
						__leave;

					// Add the ACE to the new ACL.
					if (!AddAce(
						pNewAcl,
						ACL_REVISION,
						MAXDWORD,
						pTempAce,
						((PACE_HEADER)pTempAce)->AceSize)
						)
						__leave;
				}
			}
		}

		// Add the first ACE to the window station.

		pace = (ACCESS_ALLOWED_ACE *)HeapAlloc(
			GetProcessHeap(),
			HEAP_ZERO_MEMORY,
			sizeof(ACCESS_ALLOWED_ACE) + GetLengthSid(psid) -
			sizeof(DWORD));

		if (pace == NULL)
			__leave;

		pace->Header.AceType = ACCESS_ALLOWED_ACE_TYPE;
		pace->Header.AceFlags = CONTAINER_INHERIT_ACE |
			INHERIT_ONLY_ACE | OBJECT_INHERIT_ACE;
		pace->Header.AceSize = LOWORD(sizeof(ACCESS_ALLOWED_ACE) +
			GetLengthSid(psid) - sizeof(DWORD));
		pace->Mask = GENERIC_ACCESS;

		if (!CopySid(GetLengthSid(psid), &pace->SidStart, psid))
			__leave;

		if (!AddAce(
			pNewAcl,
			ACL_REVISION,
			MAXDWORD,
			(LPVOID)pace,
			pace->Header.AceSize)
			)
			__leave;

		// Add the second ACE to the window station.

		pace->Header.AceFlags = NO_PROPAGATE_INHERIT_ACE;
		pace->Mask = WINSTA_ALL;

		if (!AddAce(
			pNewAcl,
			ACL_REVISION,
			MAXDWORD,
			(LPVOID)pace,
			pace->Header.AceSize)
			)
			__leave;

		// Set a new DACL for the security descriptor.

		if (!SetSecurityDescriptorDacl(
			psdNew,
			TRUE,
			pNewAcl,
			FALSE)
			)
			__leave;

		// Set the new security descriptor for the window station.

		if (!SetUserObjectSecurity(hwinsta, &si, psdNew))
			__leave;

		// Indicate success.

		bSuccess = TRUE;
	}
	__finally
	{
		// Free the allocated buffers.

		if (pace != NULL)
			HeapFree(GetProcessHeap(), 0, (LPVOID)pace);

		if (pNewAcl != NULL)
			HeapFree(GetProcessHeap(), 0, (LPVOID)pNewAcl);

		if (psd != NULL)
			HeapFree(GetProcessHeap(), 0, (LPVOID)psd);

		if (psdNew != NULL)
			HeapFree(GetProcessHeap(), 0, (LPVOID)psdNew);
	}

	return bSuccess;

}

BOOL Proc::AddAceToDesktop(HDESK hdesk, PSID psid)
{
	ACL_SIZE_INFORMATION aclSizeInfo;
	BOOL                 bDaclExist;
	BOOL                 bDaclPresent;
	BOOL                 bSuccess = FALSE;
	DWORD                dwNewAclSize;
	DWORD                dwSidSize = 0;
	DWORD                dwSdSizeNeeded;
	PACL                 pacl;
	PACL                 pNewAcl = NULL;
	PSECURITY_DESCRIPTOR psd = NULL;
	PSECURITY_DESCRIPTOR psdNew = NULL;
	PVOID                pTempAce;
	SECURITY_INFORMATION si = DACL_SECURITY_INFORMATION;
	unsigned int         i;

	__try
	{
		// Obtain the security descriptor for the desktop object.

		if (!GetUserObjectSecurity(
			hdesk,
			&si,
			psd,
			dwSidSize,
			&dwSdSizeNeeded))
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				psd = (PSECURITY_DESCRIPTOR)HeapAlloc(
					GetProcessHeap(),
					HEAP_ZERO_MEMORY,
					dwSdSizeNeeded);

				if (psd == NULL)
					__leave;

				psdNew = (PSECURITY_DESCRIPTOR)HeapAlloc(
					GetProcessHeap(),
					HEAP_ZERO_MEMORY,
					dwSdSizeNeeded);

				if (psdNew == NULL)
					__leave;

				dwSidSize = dwSdSizeNeeded;

				if (!GetUserObjectSecurity(
					hdesk,
					&si,
					psd,
					dwSidSize,
					&dwSdSizeNeeded)
					)
					__leave;
			}
			else
				__leave;
		}

		// Create a new security descriptor.

		if (!InitializeSecurityDescriptor(
			psdNew,
			SECURITY_DESCRIPTOR_REVISION)
			)
			__leave;

		// Obtain the DACL from the security descriptor.

		if (!GetSecurityDescriptorDacl(
			psd,
			&bDaclPresent,
			&pacl,
			&bDaclExist)
			)
			__leave;

		// Initialize.

		ZeroMemory(&aclSizeInfo, sizeof(ACL_SIZE_INFORMATION));
		aclSizeInfo.AclBytesInUse = sizeof(ACL);

		// Call only if NULL DACL.

		if (pacl != NULL)
		{
			// Determine the size of the ACL information.

			if (!GetAclInformation(
				pacl,
				(LPVOID)&aclSizeInfo,
				sizeof(ACL_SIZE_INFORMATION),
				AclSizeInformation)
				)
				__leave;
		}

		// Compute the size of the new ACL.

		dwNewAclSize = aclSizeInfo.AclBytesInUse +
			sizeof(ACCESS_ALLOWED_ACE) +
			GetLengthSid(psid) - sizeof(DWORD);

		// Allocate buffer for the new ACL.

		pNewAcl = (PACL)HeapAlloc(
			GetProcessHeap(),
			HEAP_ZERO_MEMORY,
			dwNewAclSize);

		if (pNewAcl == NULL)
			__leave;

		// Initialize the new ACL.

		if (!InitializeAcl(pNewAcl, dwNewAclSize, ACL_REVISION))
			__leave;

		// If DACL is present, copy it to a new DACL.

		if (bDaclPresent)
		{
			// Copy the ACEs to the new ACL.
			if (aclSizeInfo.AceCount)
			{
				for (i = 0; i < aclSizeInfo.AceCount; i++)
				{
					// Get an ACE.
					if (!GetAce(pacl, i, &pTempAce))
						__leave;

					// Add the ACE to the new ACL.
					if (!AddAce(
						pNewAcl,
						ACL_REVISION,
						MAXDWORD,
						pTempAce,
						((PACE_HEADER)pTempAce)->AceSize)
						)
						__leave;
				}
			}
		}

		// Add ACE to the DACL.

		if (!AddAccessAllowedAce(
			pNewAcl,
			ACL_REVISION,
			DESKTOP_ALL,
			psid)
			)
			__leave;

		// Set new DACL to the new security descriptor.

		if (!SetSecurityDescriptorDacl(
			psdNew,
			TRUE,
			pNewAcl,
			FALSE)
			)
			__leave;

		// Set the new security descriptor for the desktop object.

		if (!SetUserObjectSecurity(hdesk, &si, psdNew))
			__leave;

		// Indicate success.

		bSuccess = TRUE;
	}
	__finally
	{
		// Free buffers.

		if (pNewAcl != NULL)
			HeapFree(GetProcessHeap(), 0, (LPVOID)pNewAcl);

		if (psd != NULL)
			HeapFree(GetProcessHeap(), 0, (LPVOID)psd);

		if (psdNew != NULL)
			HeapFree(GetProcessHeap(), 0, (LPVOID)psdNew);
	}

	return bSuccess;
}

int  Proc::Run2(QString cmd) {
	try
	{

		DWORD dwErr;
		TCHAR bufProgName[1000] = _T("");
		TCHAR bufParameters[1000] = _T("");

		::lstrcat(bufProgName, _T(cmd.toStdString()));
		::lstrcat(bufParameters, _T(" -help"));

		SHELLEXECUTEINFO ShExecInfo;
		ZeroMemory(&ShExecInfo, sizeof(ShExecInfo));
		ShExecInfo.cbSize = sizeof(ShExecInfo);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = NULL;
		ShExecInfo.lpVerb = NULL;
		ShExecInfo.lpFile = bufProgName;
		ShExecInfo.lpParameters = bufParameters;
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_SHOWNORMAL;
		ShExecInfo.hInstApp = NULL;
		int res = ShellExecuteEx(&ShExecInfo);
		if (!res)
		{
			dwErr = GetLastError();
			return -1;
		}

	}
	catch (...)
	{
		qInfo()  << "ShellFail: " << dwError;
		return -1;

	}
}
*/