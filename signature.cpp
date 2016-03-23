#include "signature.h"
#include <stdint.h>
#include <string>
#include <sstream>
#include <algorithm>

Signature::Signature(QString pattern, QString mask): pattern(pattern), mask(mask)
{

}

Signature::Signature(QString str)
{
    QString r = str.remove(QChar(' '));
    std::string idapattern = r.toStdString();

    for (auto it = idapattern.cbegin(); it != idapattern.cend();)
    {
        if (*it == wildcard)
        {
            pattern += '\0';
            mask += wildcard;
            it++;
            continue;
        }
        std::string cur(it, it + 2);
        std::stringstream converter(cur);
        uint16_t current = 0;
        converter >> std::hex >> current >> std::dec;
        char real_current = static_cast<char>(current);
        pattern += real_current;
        mask += 'x';
        it += 2;

        qDebug() << "pattern= " << pattern;
        qDebug() << "mask= " << mask;
    }
}
