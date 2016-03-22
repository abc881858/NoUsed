#include "module.h"
#include "utils.h"
#include <QByteArray>

void Module::Init(Process &process, QString dllname)
{
    if (data_ != nullptr)
    {
        free(data_);
    }
    data_ = nullptr;

    process.GetRemoteModule(dllname, &module_entry_);
    data_ = malloc(module_entry_.modBaseSize);

    data_ = new tagMODULEENTRY32W;

    process.ReadData(data_, module_entry_.modBaseAddr, module_entry_.modBaseSize);
}

const unsigned char* Module::FindPattern(QString signature, QString mask)
{
    const unsigned char* pattern = utils::FindPattern(data_, module_entry_.modBaseSize, signature, mask);
    return (const unsigned char*)(pattern - (const unsigned char*)data_);
}

const unsigned char* Module::FindPattern(Signature signature)
{
    return FindPattern(signature.pattern, signature.mask);
}

void* Module::GetAddress(uint offset) const
{
    return module_entry_.modBaseAddr + offset;
}
