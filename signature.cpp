#include "signature.h"

Signature::Signature(QString pattern, QString mask): pattern(pattern), mask(mask)
{

}

Signature::Signature(QString idapattern)
{
//    idapattern.erase(std::remove(idapattern.begin(), idapattern.end(), ' '), idapattern.end());
//    for (auto it = idapattern.cbegin(); it != idapattern.cend();)
//    {
//        if (*it == wildcard)
//        {
//            pattern += '\0';
//            mask += wildcard;
//            it++;
//            continue;
//        }
//        QString cur(it, it + 2);
//        std::stringstream converter(cur);
//        uint16_t current = 0;
//        converter >> std::hex >> current >> std::dec;
//        char real_current = static_cast<char>(current);
//        pattern += real_current;
//        mask += 'x';
//        it += 2;
//    }
}
