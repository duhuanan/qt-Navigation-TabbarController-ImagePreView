#ifndef QLOG_H
#define QLOG_H
#include <QDebug>

class QLog
{
public:
    static void log(const char *tag, const char *fmt, ...) {
        char buffer[1256];
        va_list vl;

        va_start(vl,fmt);
        vsprintf(buffer,fmt,vl);
        va_end(vl);
        qDebug("%s:%s", tag, buffer);
    }
};

#endif // QLOG_H
