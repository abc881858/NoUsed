#ifndef MODULE_H
#define MODULE_H

#include "process.h"
#include "signature.h"

class Module
{
public:
    Module();
    ~Module();
    void Init(Process& process, QString dllname);
    const unsigned char *FindPattern(QString signature, QString mask);
    const unsigned char *FindPattern(Signature signature);
    void *GetAddress(uint offset = 0) const;
private:
    MODULEENTRY32 module_entry_;
    void* data_;
};

#endif // MODULE_H
