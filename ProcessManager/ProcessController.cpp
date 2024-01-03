#include "ProcessContoller.h"

IWbemLocator* WMILocatorG = NULL;
IWbemServices* WMIServiceG = NULL;

int BSTRToInt(const BSTR);
String^ PriorityToString(int);
String^ StateToString(int);
BSTR ConvertWmiDateString(const wchar_t*);
BSTR CopyBstr(const BSTR);

ProcessInfo::ProcessInfo() 
{
    this->ProcessId = gcnew INT(-1);
    this->Priority = gcnew INT(-1);
    this->State = gcnew INT(-1);
    this->Name = gcnew String("Default");
    this->Path = gcnew String("Default");
    this->Server = gcnew String("Default");
    this->CreationDate = gcnew String("Default");
}

ProcessController::ProcessController() 
{
    marshal_context mContext;
    debugInfo = gcnew String("");

    userLogin = nullptr;
    userPassword = nullptr;

    networkResource = gcnew String(L"\\\\.\\ROOT\\CIMV2");
    Processes = gcnew List<ProcessInfo^>();

    debugInfo += String::Format("Початок роботи програми\n");

    hres = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    if (FAILED(hres))
    {
        debugInfo += String::Format("Не Вдалося Ініціалізувати бібліотеку COM.Помилка коду = 0x{0:X}\n", hres);
    }

    hres = CoInitializeSecurity(nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
       RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr);

    if (FAILED(hres))
    {
        debugInfo += String::Format("Не Вдалося безпечно ініціалізувати.Код помилки = 0х{0:X}\n", hres);
    }

    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&WMILocatorG);

    if (FAILED(hres))
    {
        debugInfo += String::Format("Не Вдалося створити Iwbemlocator об’єкт.Помилка коду = 0x{0:X}\n", hres);
    }

    hres = WMILocatorG->ConnectServer(_bstr_t(mContext.marshal_as<const wchar_t*>(networkResource)), NULL, NULL, 0, NULL, 0, 0, &WMIServiceG);

    if (FAILED(hres))
    {
        debugInfo += String::Format("Не Вдалося підключитися. Помилка коду = 0x{0:X}\n", hres);
        WMILocatorG->Release();
    }

    hres = CoSetProxyBlanket(WMIServiceG, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
        RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

    if (FAILED(hres))
    {
        debugInfo += String::Format("Не вдалося встановити безпеку на сервері.Помилка коду = 0x{0:X}\n", hres);
        WMILocatorG->Release();
        WMIServiceG->Release();
    }

    hres = CoSetProxyBlanket(WMIServiceG, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
        RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

    if (FAILED(hres))
    {
        debugInfo += String::Format("Не вдалося встановити безпеку на сервері.Помилка коду = 0x{0:X}\n", hres);
        WMILocatorG->Release();
        WMIServiceG->Release();
    }
}

ProcessController::~ProcessController() 
{

}

// Getting all info about processes
void ProcessController::GetCurrentProcesses()
{
    marshal_context mContext;

    //hres = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    //if (FAILED(hres))
    //{
    //    debugInfo += String::Format("Не Вдалося Ініціалізувати бібліотеку COM.Помилка коду = 0x{0:X}\n", hres);
    //}

    //hres = CoInitializeSecurity(nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
    //RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr);

    if (FAILED(hres))
    {
        debugInfo += String::Format("Не Вдалося безпечно ініціалізувати.Код помилки = 0х{0:X}\n", hres);
    }

    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&WMILocatorG);

    if (FAILED(hres))
    {
        debugInfo += String::Format("Не Вдалося створити Iwbemlocator об’єкт.Помилка коду = 0x{0:X}\n", hres);
    }

    hres = WMILocatorG->ConnectServer(_bstr_t(mContext.marshal_as<const wchar_t*>(networkResource)),
                                      _bstr_t(mContext.marshal_as<const wchar_t*>(userLogin)),
                                      _bstr_t(mContext.marshal_as<const wchar_t*>(userPassword)), 0, NULL, 0, 0, &WMIServiceG);

    if (FAILED(hres))
    {
        if (hres == -2147023174) 
        {
            debugInfo += String::Format("Не було знайдено комп'ютера з вказаним ім'ям або вказаний сервер не є доступним:{0}\n", networkResource);
        }
        debugInfo += String::Format("Не Вдалося підключитися. Помилка коду = 0x{0:X}\n", hres);
        WMILocatorG->Release();
    }

    hres = CoSetProxyBlanket(WMIServiceG, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
        RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

    if (FAILED(hres))
    {
        debugInfo += String::Format("Не вдалося встановити безпеку на сервері.Помилка коду = 0x{0:X}\n", hres);
        WMILocatorG->Release();
        WMIServiceG->Release();
    }

    hres = CoSetProxyBlanket(WMIServiceG, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
        RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

    if (FAILED(hres))
    {
        debugInfo += String::Format("Не вдалося встановити безпеку на сервері.Помилка коду = 0x{0:X}\n", hres);
        WMILocatorG->Release();
        WMIServiceG->Release();
    }

    // SELECT * FROM Win32_Process request
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = WMIServiceG->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_Process"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);

    if (FAILED(hres))
    {
        debugInfo += String::Format("Помилка виклику WQL Query. Помилка коду = 0x{0:X}\n", hres);
    }
    


    // Retrieving info from Win32_Process
    IWbemClassObject* WMIClassObject = NULL;
    ULONG uReturn = 0;   

    while (pEnumerator && SUCCEEDED(pEnumerator->Next(WBEM_INFINITE, 1, &WMIClassObject, &uReturn)) && uReturn != 0) 
    {
       ProcessInfo^ tempProcessInfo = gcnew ProcessInfo;

       VARIANT vtTemp; // Temp variant
       VariantInit(&vtTemp); // Init variant

       // Retrieving ProcessId
       WMIClassObject->Get(L"ProcessId", 0, &vtTemp, 0, 0);
       tempProcessInfo->ProcessId = gcnew INT(vtTemp.intVal);
       VariantClear(&vtTemp);
       //

       // Retrieving Name
       WMIClassObject->Get(L"Name", 0, &vtTemp, 0, 0);
       tempProcessInfo->Name = gcnew String(vtTemp.bstrVal);
       VariantClear(&vtTemp);
       //

       // Retrieving Priority
       hres = WMIClassObject->Get(L"Priority", 0, &vtTemp, 0, 0);
       tempProcessInfo->Priority = gcnew INT(vtTemp.intVal);
       VariantClear(&vtTemp);
       //

       // Retrieving Creation Date
       hres = WMIClassObject->Get(L"CreationDate", 0, &vtTemp, 0, 0);   
       BSTR dateTempstring = ConvertWmiDateString(vtTemp.bstrVal);
       tempProcessInfo->CreationDate = gcnew String(dateTempstring);
       SysFreeString(dateTempstring);
       VariantClear(&vtTemp);
       //
       
       // Retrieving Path
       WMIClassObject->Get(L"__PATH", 0, &vtTemp, nullptr, nullptr);
       tempProcessInfo->Path = gcnew String(vtTemp.bstrVal);
       VariantClear(&vtTemp);
       //
        
       // Retrieving Server
       WMIClassObject->Get(L"__SERVER", 0, &vtTemp, nullptr, nullptr);
       BSTR serverTempstring = CopyBstr(vtTemp.bstrVal);
       tempProcessInfo->Server = gcnew String(serverTempstring);
       SysFreeString(serverTempstring);
       VariantClear(&vtTemp);
       //  
       
       Processes->Add(tempProcessInfo); // Save info into List

       WMIClassObject->Release();
    }
    //

    pEnumerator->Release();

   // Retrieving Process State
    hres = WMIServiceG->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_Thread"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);

    if (FAILED(hres))
    {
        debugInfo += String::Format("Помилка виклику WQL Query. Помилка коду = 0x{0:X}\n", hres);
    }

    while (pEnumerator && SUCCEEDED(pEnumerator->Next(WBEM_INFINITE, 1, &WMIClassObject, &uReturn)) && uReturn != 0)
    {
        VARIANT vtProp;
        VariantInit(&vtProp);

        WMIClassObject->Get(L"ProcessHandle", 0, &vtProp, 0, 0);

        // Iterate over Processes to set process state
        for (int i = 0; i < this->Processes->Count; i++) 
        {
            
            // If thread process id and process id are the same, it means they relate to the same process 
            if (*this->Processes[i]->ProcessId == BSTRToInt(vtProp.bstrVal))
            {
                VariantClear(&vtProp);
                WMIClassObject->Get(L"ThreadState", 0, &vtProp, 0, 0);

                if (*this->Processes[i]->State == 2) 
                {
                    break;
                } 
                else if (*this->Processes[i]->State == 3)
                {
                    break;
                }
                else if (*this->Processes[i]->State == 1)
                {
                    break;
                }
                else if (*this->Processes[i]->State == 0)
                {
                    break;
                }

                this->Processes[i]->State = gcnew INT(vtProp.intVal);

                break;
            }
        }

        VariantClear(&vtProp);
        WMIClassObject->Release();
    }
    
   pEnumerator->Release();

}

void ProcessController::ClearProcesses()
{
    Processes->Clear();
    debugInfo += String::Format("Список процесів оновлено\n");
}

int BSTRToInt(const BSTR bstr) {
    // Convert BSTR to wide character string (wchar_t*)
    const wchar_t* wideStr = static_cast<const wchar_t*>(bstr);

    // Convert wide character string to integer
    int result = _wtoi(wideStr);

    return result;
}

String^ PriorityToString(int priority) 
{
    if (priority == 0) 
    {
        return "IDLE";
    } 
    else if (priority > 0 && priority < 5) 
    {
        return "BELOW_NORMAL";
    }
    else if (priority == 5)
    {
        return "NORMAL";
    }
    else if (priority > 5 && priority < 10)
    {
        return "ABOVE_NORMAL";
    }
    else if (priority > 9 && priority < 15)
    {
        return "HIGH";
    }
    else if (priority > 14 && priority < 25)
    {
        return "HIGHEST";
    }
    else if (priority > 24 && priority < 32)
    {
        return "HIGHEST_POSSIBLE";
    }
    else 
    {
        return "ERROR";
    }
}

String^ StateToString(int state) 
{
    switch (state)
    {
    case 0:
        return "Initialized";
        break;

    case 1:
        return "Ready";
        break;

    case 2:
        return "Running";
        break;

    case 3:
        return "Standby";
        break;

    case 4:
        return "Terminated";
        break;

    case 5:
        return "Waiting";
        break;

    case 6:
        return "Transition";
        break;


    default:
        return "Unknown";
        break;
    }
}

BSTR ConvertWmiDateString(const wchar_t* wmiDateString) {
    SYSTEMTIME sysTime;
    int year, month, day, hour, minute, second;

    // Extract components from the WMI date string
    swscanf_s(wmiDateString, L"%04d%02d%02d%02d%02d%02d",
        &year, &month, &day, &hour, &minute, &second);

    // Populate the SYSTEMTIME structure
    sysTime.wYear = static_cast<WORD>(year);
    sysTime.wMonth = static_cast<WORD>(month);
    sysTime.wDay = static_cast<WORD>(day);
    sysTime.wHour = static_cast<WORD>(hour);
    sysTime.wMinute = static_cast<WORD>(minute);
    sysTime.wSecond = static_cast<WORD>(second);
    sysTime.wMilliseconds = 0;

    // Format the date and time into a string
    wchar_t buffer[100]; // Adjust the buffer size as needed
    int result = swprintf_s(buffer, L"%04d-%02d-%02d %02d:%02d:%02d",
        sysTime.wYear, sysTime.wMonth, sysTime.wDay,
        sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

    if (result > 0) {
        // Convert the formatted string to BSTR
        return SysAllocString(buffer);;
    }
    else {
        return SysAllocString(L"Error formatting date string");
    }
}

BSTR CopyBstr(const BSTR source) {
    if (source == nullptr) {
        // Обработка нулевого указателя, если необходимо
        return nullptr;
    }

    // Получение длины исходной строки
    int length = SysStringLen(source);

    // Выделение памяти для новой строки
    BSTR copiedString = SysAllocStringLen(nullptr, length);

    if (copiedString) {
        // Копирование содержимого
        wcscpy_s(copiedString, length + 1, source);
    }

    return copiedString;
}

String^ ProcessController::GetNetworkResource()
{
    return networkResource;
}

void ProcessController::SetNetworkResource(String^ newNetworkResource) 
{
    if (newNetworkResource == L"LocalComputer" || newNetworkResource == L"" || newNetworkResource == L"Local")
    {
        newNetworkResource = L".";
    }
    String^ newNetworkResourceFull = L"\\\\";
    newNetworkResourceFull += newNetworkResource;
    newNetworkResourceFull += L"\\ROOT\\CIMV2";
    networkResource = newNetworkResourceFull;
}

String^ ProcessController::GetDebugInfo()
{
    return debugInfo;
}

void ProcessController::AddDebugInfo(String^ addInfo)
{
    debugInfo += addInfo;
}

void ProcessController::ClearDebugInfo() 
{
    debugInfo = gcnew String("");
}

List<ProcessInfo^>^ ProcessController::GetProcesses() 
{
    return Processes;
}

void ProcessController::SetLogin(String^ newLogin)
{
    if (newLogin == L"LocalUser" || newLogin == L"" || newLogin == L"Local")
    {
        newLogin = nullptr;
    }
    userLogin = newLogin;
}

void ProcessController::SetPassword(String^ newPassword)
{
    if (newPassword == L"LocalPassword" || newPassword == L"" || newPassword == L"Local")
    {
        newPassword = nullptr;
    }
    userPassword = newPassword;
}