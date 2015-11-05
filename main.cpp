#include <stdio.h>

#include <Windows.h>
#include <TlHelp32.h>

DWORD switchToPid;

int wCharToChar(wchar_t *WStr,char *CStr){
    size_t len = wcslen(WStr) + 1;
    size_t converted = 0;
    return wcstombs_s(&converted, CStr, len, WStr, _TRUNCATE);
}

BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam)
{
    DWORD currentWindowPID;
    GetWindowThreadProcessId(hwnd,&currentWindowPID);
    if((currentWindowPID == switchToPid) && IsWindowVisible(hwnd) && (GetParent(hwnd) == NULL)){
        ShowWindow(hwnd,SW_MAXIMIZE);
        UpdateWindow(hwnd);
        SetForegroundWindow(hwnd);
    }
    return true;
}

int main(int argc, char *argv[])
{
    DWORD FrontWindowPID = 0;
    DWORD switchPIDS[50];
    int i,j;

    for(i = 1; i < argc; i++){
        switchPIDS[i] = 0;
    }

    HWND hwnd = GetForegroundWindow();
    GetWindowThreadProcessId(hwnd,&FrontWindowPID);
    char PidName[300];

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if(hSnapshot == NULL){
        return -1;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if ( !Process32First(hSnapshot,&pe32) )
    {
        CloseHandle(hSnapshot);
        return -2;
    }

    while ( 1 )
    {
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (Process32Next(hSnapshot,&pe32) == FALSE)
            break;
        wCharToChar(pe32.szExeFile,PidName);
        printf("%d\n",argc);
        for(i = 1; i < argc; i++){
            if(!strcmp(PidName,argv[i])){
                switchPIDS[i]=pe32.th32ProcessID;
            }
        }
    }

    for(i = 1; i < argc; i++){
        if(FrontWindowPID == switchPIDS[i]){
            break;
        }
    }

    if(i >= argc){
        i = 0;
    }
/*
    i++;
    if(i>=argc)
        i = 1;
*/
    if(j = i+1; j != i; j = (j+1)%(argc-1)){
        if(j == 0){
            if(i == 0)
                break;
            else
                j = 1;
        }
        if
    }

    switchToPid = switchPIDS[i];
 //   switchToPid = (FrontWindowPID == PuttyPID ? FirefoxPID : PuttyPID);
 //   EnumWindows(lpEnumFunc,NULL);
    return 0;
}
