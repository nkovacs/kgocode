#include "process.h"
#include <QProcess>

Process::Process()
{
}

Process::~Process()
{
    // close the daemon
    QProcess p;
    p.start("gocode", QStringList() << "close");
    p.waitForFinished(TIMEOUT);
}

QVector<TypeInfo> Process::getCompletions(const QByteArray& ustart, const QByteArray& uend)
{
    QStringList args;
    args << "-f=csv" << "autocomplete" << QString("c") + QString::number(ustart.length());

    QProcess p;
    p.start("gocode", args);

    if(!p.waitForStarted(TIMEOUT))
        return QVector<TypeInfo>();

    p.write(ustart);
    p.write(uend);
    p.closeWriteChannel();

    if(!p.waitForFinished(TIMEOUT))
        return QVector<TypeInfo>();

    QStringList lines = QString(p.readAllStandardOutput()).split("\n");
    QVector<TypeInfo> out;
    out.reserve(lines.size());

    TypeInfo info;

    for(int i = 0, e = lines.size(); i < e; ++i)
        if(info.parseString(lines[i]))
            out.push_back(info);

    return out;
}

bool TypeInfo::parseString(const QString &str)
{
    QStringList fields = str.split(",,");

    if(fields.size() != 3) return false;

    class_ = parseClass(fields[0]);
    name_  = fields[1];
    type_  = fields[2];

    return true;
}

// should be better / faster than creating and initializing a QMap
ProcClass TypeInfo::parseClass(const QString &s)
{
    if(s == "func")
        return FUNC;

    if(s == "var")
        return VAR;

    if(s == "const")
        return CONST;

    if(s == "type")
        return TYPE;

    if(s == "package")
        return PACKAGE;

    return PANIC;
}
