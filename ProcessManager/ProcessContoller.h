#pragma once
#define _WIN32_DCOM
#include <iostream>
#include <vector>
using namespace std;
#include <windows.h>
#include <wbemidl.h>
#include <comutil.h>
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "comsuppw.lib")

#using <mscorlib.dll>
#using <System.dll>
#include <msclr/marshal.h>
using namespace System;
using namespace System::Collections::Generic;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;
using namespace msclr::interop;

int BSTRToInt(const BSTR);
String^ PriorityToString(int);
String^ StateToString(int);
BSTR ConvertWmiDateString(const wchar_t*);
BSTR CopyBstr(const BSTR);

ref class ProcessInfo
{
public:
	ProcessInfo();
	INT^ ProcessId;
	INT^ Priority;
	INT^ State;
	String^ Name;
	String^ Path;
	String^ Server;
	String^ CreationDate;
	
};

ref class ProcessController
{
private:
	HRESULT hres;
	String^ networkResource;
	String^ debugInfo;
	String^ userLogin;
	String^ userPassword;
	List<ProcessInfo^>^ Processes;

public:
	ProcessController();
	~ProcessController();
	String^ GetNetworkResource();
	String^ GetDebugInfo();
	void ClearDebugInfo();
	void AddDebugInfo(String^);
	void SetNetworkResource(String^);
	void SetLogin(String^);
	void SetPassword(String^);
	void ClearProcesses();
	List<ProcessInfo^>^ GetProcesses();
	void GetCurrentProcesses();
};



