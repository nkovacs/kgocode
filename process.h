#ifndef PROCESS_H
#define PROCESS_H

#include <QVector>
#include <QString>

enum ProcClass
{
    FUNC,
    VAR,
    CONST,
    TYPE,
    PACKAGE,
    PANIC
};

struct TypeInfo
{
    ProcClass class_;
    QString name_, type_;

    bool parseString(const QString& str);
    static ProcClass parseClass(const QString& s);
};

const int TIMEOUT = 5000;

/**
 * Handles the communication to the gocode process.
 */
class Process
{
public:
    Process();
    virtual ~Process();
    QVector<TypeInfo> getCompletions(const QString &filename, const QByteArray& ustart, const QByteArray &uend);
};

#endif // PROCESS_H
