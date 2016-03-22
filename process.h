#ifndef PROCESS_H
#define PROCESS_H

#include <windows.h>
#include <TlHelp32.h>
#include <stdint.h>
//#include <string>
//#include <sstream>
//#include <algorithm>

static const char wildcard = '?';

struct rbuf_t
{
    void* base;
    void* free;
};

class QString;

class Process
{
public:
    Process();
    ~Process();
    void Attach(QString window);
    void GetRemoteModule(QString filename, MODULEENTRY32W *lpme);
    void ReadData(void *dest, const void *src, unsigned int bytes);
private:
    int process_id_;
    HANDLE process_handle_;
    rbuf_t rbuf;
};

#endif // PROCESS_H
