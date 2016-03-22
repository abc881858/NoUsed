#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <QString>

class Signature
{
public:
    Signature(QString pattern, QString mask);
    Signature(QString idapattern);

    QString pattern;
    QString mask;
};

#endif // SIGNATURE_H
