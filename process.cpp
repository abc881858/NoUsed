#include "process.h"
#include <QString>
#include <QDebug>

Process::Process() : process_handle_(INVALID_HANDLE_VALUE)
{
    rbuf.base = nullptr;
}

Process::~Process()
{
    VirtualFreeEx(process_handle_, rbuf.base, 0, MEM_RELEASE);
    CloseHandle(process_handle_);
    process_handle_ = INVALID_HANDLE_VALUE;
    rbuf.free = rbuf.base = nullptr;
}

void Process::Attach(QString window)
{
    HWND hwnd = FindWindow(nullptr,(LPCWSTR)window.utf16());
    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid);
    process_id_ = pid;
    qDebug() << "process_id_= " << process_id_;
    DWORD rights = PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_SUSPEND_RESUME | SYNCHRONIZE;
    HANDLE handle = OpenProcess(rights, FALSE, pid);
    process_handle_ = handle;
    qDebug() << "process_handle_= " << process_handle_;
    rbuf.base = ::VirtualAllocEx(process_handle_, nullptr, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    rbuf.free = (char*)rbuf.base + 0x100;
    qDebug() << "rbuf.base= " << rbuf.base;
    qDebug() << "rbuf.free= " << rbuf.free;
}

void Process::GetRemoteModule(QString filename, MODULEENTRY32* lpme) //"steamclient.dll"
{
    QByteArray ba = filename.toLatin1();
    const char* ch = ba.data();

    HANDLE snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id_);

    MODULEENTRY32 me;
    if (!lpme)
    {
        lpme = &me;
    }

    lpme->dwSize = sizeof(MODULEENTRY32);
    if (Module32First(snapshot, lpme))
    {
//        do {
//            if (!_stricmp(lpme->szModule, ch))
//            {
//                break;
//            }
//        } while (Module32Next(snapshot, lpme));
    }

    CloseHandle(snapshot);
}

void Process::ReadData(void* dest, const void* src, unsigned int bytes)
{
    SIZE_T n;
    ReadProcessMemory(process_handle_, src, dest, bytes, &n);
}
