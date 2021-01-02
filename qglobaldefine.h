#ifndef QGLOBELDEFINE_H
#define QGLOBELDEFINE_H

#include <vector>
#include <string>
#include "qlog.h"
#include "qimagepreview.h"

using namespace std;

#ifdef QT_NO_DEBUG
#define QLog(tag, fmt, arg)
#define QError(fmt, arg)
#else
#define QLog(tag, fmt, arg) QLog::log(tag, fmt, arg)
#define QError(fmt, arg) QLog::log("error", fmt, arg)
#endif

#define ShowImagePreview(parent, idx, urls) \
    QImagePreview preview(parent);\
    preview.setImages(urls);\
    preview.showWithIndex(idx);

#endif // QGLOBELDEFINE_H
