#include "qfiledownloadmanager.h"
#include <QCryptographicHash>
#include <QFileInfo>
#include <QDir>
#include <thread>
#include <stdlib.h>
#include "qglobaldefine.h"

FunctionTransfer main_thread_forward;

FunctionTransfer::FunctionTransfer(QObject *parent) : QObject(parent) {
    threadId = pthread_self();
    connect(this,SIGNAL(comming(std::function<void()>)),this,SLOT(exec(std::function<void()>)),Qt::BlockingQueuedConnection);
}

void FunctionTransfer::execinmain(std::function<void()> f) {
    main_thread_forward.exec(f);
}

void FunctionTransfer::exec(std::function<void()> f) {
    if(pthread_self() == threadId) {
        f();
    } else {
        emit this->comming(f);
    }
}

QFileDownloadManager::QFileDownloadManager() {
    netManager.setAutoDeleteReplies(true);
}

std::string QFileDownloadManager::download(std::string url, std::function<void (QPixmap &)> callback) {
    std::string uniqueKey = to_string(QDateTime::currentMSecsSinceEpoch() * 1000000 + rand() % 1000000);
    std::map<std::string, funMap_t>::iterator it = funMap.find(url);

    if(it == funMap.end()) {
        funMap_t mapPt = new QFunMap();
        mapPt->insert(make_pair(uniqueKey, callback));
        funMap[url] = mapPt;
        startDownload(url);
    }else {
        funMap_t mapPt = it->second;
        mapPt->insert(make_pair(uniqueKey, callback));
    }

    return uniqueKey;
}

QString hashName(std::string dir, std::string url) {
    QByteArray str(url.c_str());
    QByteArray md5Value = QCryptographicHash::hash(str, QCryptographicHash::Md5).toHex();
    QString filename = md5Value;

    QDir qdir;

    if(!qdir.exists(dir.c_str())) {
        qdir.mkpath(dir.c_str());//创建多级目录，如果已存在则会返回去true
    }

    filename = dir.c_str() + filename;
    return filename;
}

void QFileDownloadManager::startDownload(std::string url) {
    std::string tmpStr = url;
    QString name = hashName("./images/", tmpStr);
    QFileInfo fInfo(name);

    if(fInfo.exists() && fInfo.size() > 3) {
        loadFile(tmpStr, name.toStdString());
        QLog("1231231sfasdf23", "%d", fInfo.size());
    }else {
        QLog("1231231sfasdf21231231231231233", "%d", fInfo.size());
        QNetworkRequest request;
        request.setUrl(QUrl(tmpStr.c_str()));
        connect(&netManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
        netManager.get(request);
    }
}

void QFileDownloadManager::clearKey(std::vector<string> keys) {
    for(std::map<std::string, funMap_t>::iterator it = funMap.begin(); it != funMap.end(); it++) {
        for(std::string &key : keys) {
            QFunMap::iterator tIt = it->second->find(key);

            if(tIt != it->second->end()) {
                it->second->erase(tIt);
            }
        }
    }
}

void QFileDownloadManager::loadFile(std::string &tmpUrl, std::string filepath) {
    std::string url = tmpUrl;
    std::thread t([url, filepath, this]() {
        QPixmap *pixmap = new QPixmap(filepath.c_str());
        FunctionTransfer::execinmain([url, pixmap, this] {
            std::map<std::string, funMap_t>::iterator it = funMap.find(url);

            if(it != funMap.end()) {
                for(QFunMap::iterator vIt = it->second->begin(); vIt != it->second->end(); vIt++) {
                    vIt->second(*pixmap);
                }

                delete it->second;
                delete pixmap;
                funMap.erase(it);
            }
        });
    });
    t.detach();
}

void QFileDownloadManager::replyFinished(QNetworkReply *reply) {
    if(reply->error() == QNetworkReply::NoError) {
        std::string url = reply->url().url().toStdString();
        QString name = hashName("./images/", url);
        QFile avatorFile(name);

        if(avatorFile.open(QIODevice::ReadWrite)) {
            avatorFile.write(reply->readAll());
            avatorFile.flush();
            avatorFile.close();
        }

        loadFile(url, name.toStdString());
    }
}
