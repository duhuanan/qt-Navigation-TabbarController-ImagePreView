#ifndef QFILEDOWNLOADMANAGER_H
#define QFILEDOWNLOADMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <mutex>
#include <functional>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

class FunctionTransfer : public QObject {
    Q_OBJECT
public:
    explicit FunctionTransfer(QObject *parent = 0);
    static void execinmain(std::function<void()> f);
signals:
    void comming(std::function<void()> f);
public slots:
    void exec(std::function<void()> f);
private:
    pthread_t threadId;
};

class QFileDownloadManager : QObject {
    Q_OBJECT
public:
    typedef std::map<std::string, std::function<void (QPixmap &)>> QFunMap;
    typedef QFunMap* funMap_t;
    QFileDownloadManager();

    static QFileDownloadManager *fileManager() {
        static QFileDownloadManager *manager = nullptr;
        static std::once_flag oc;
        std::call_once(oc, [&] () {
            manager = new QFileDownloadManager();
        });

        return manager;
    }

    std::string download(std::string url, std::function<void (QPixmap &)> callback);
    void clearKey(std::vector<std::string> keys);
public slots:
    void replyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager netManager;
    std::map<std::string, funMap_t> funMap;

    void startDownload(std::string url);
    void loadFile(std::string &url, std::string filepath);
};

#endif // QFILEDOWNLOADMANAGER_H
