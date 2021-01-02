#ifndef QTABBARWIDGET_H
#define QTABBARWIDGET_H

#include <QStackedWidget>
#include <functional>
#include "qnavigation.h"
#include <QPushButton>

class QTabbar : public QWidget {
private:
    std::vector<QPushButton *> buttons;
    std::function<void (int tabIdx)> onSelect;
public:
    explicit QTabbar(QWidget *parent = 0);
    void setItems(std::vector<QNavigationItem> items);
    void setSelect(int idx);
    void setSelectCallback(std::function<void (int tabIdx)> callback) {
        onSelect = callback;
    }
};

class QTabbarWidget : public QWidget {
    Q_OBJECT
public:
    explicit QTabbarWidget(QWidget *parent = 0);
    void setNavigations(std::vector<QNavigation *> &widgets);
    void setCallback(std::function<void (int tabIdx)> callback);
    QNavigation *currentNavigation();
signals:
public slots:
private:
    QStackedWidget *stackedWidget;
    std::function<void (int tabIdx)> onTabSelect;
    int selectIdx;
    std::vector<QNavigation *> navigations;
};

#endif // QTABBARWIDGET_H
