#include "qtabbarwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

QTabbar::QTabbar(QWidget *parent) : QWidget(parent) {
    this->onSelect = nullptr;
}

void QTabbar::setItems(std::vector<QNavigationItem> items) {
    this->setStyleSheet("background-color:#fff");
    QHBoxLayout *hBox = new QHBoxLayout(this);
    hBox->setSpacing(0);

    for(int i = 0; i < (int)items.size(); i++) {
        auto &item = items[i];
        QString str(item.title().c_str());
        QPushButton *titleLabel = new QPushButton(this);
        titleLabel->setFlat(true);
        titleLabel->setText(str);

        connect(titleLabel, &QPushButton::clicked, [i, this]() {
            setSelect(i);
        });

        buttons.push_back(titleLabel);
        hBox->addWidget(titleLabel, 1);
    }

    setLayout(hBox);
    setSelect(0);

}

void QTabbar::setSelect(int idx) {
    for(int i = 0; i < (int)buttons.size(); i++) {
        QPushButton *label = buttons[i];

        if(idx == i) {
            label->setStyleSheet("QPushButton{color:#289fff;text-align:center;}QPushButton:pressed{background:transparent}");
        }else {
            label->setStyleSheet("QPushButton{color:#232323;text-align:center;}QPushButton:pressed{background:transparent}");
        }
    }

    if(this->onSelect != nullptr) {
        this->onSelect(idx);
    }
}

QTabbarWidget::QTabbarWidget(QWidget *parent) : QWidget(parent) {
    selectIdx = 0;
}

QNavigation *QTabbarWidget::currentNavigation() {
    return navigations.at(selectIdx);
}

void QTabbarWidget::setNavigations(std::vector<QNavigation *> &widgets) {
    navigations = widgets;
    std::vector<QNavigationItem> items;
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    stackedWidget = new QStackedWidget(this);

    for(auto nav : widgets) {
        stackedWidget->addWidget(nav);
        items.push_back(nav->item());
    }

    stackedWidget->setCurrentIndex(0);
    QTabbar *tabbar = new QTabbar(this);
    tabbar->setItems(items);
    tabbar->setSelectCallback([this](int idx) {
        this->selectIdx = idx;
        this->stackedWidget->setCurrentIndex(idx);

        if(this->onTabSelect) {
            this->onTabSelect(idx);
        }
    });

    vLayout->setSpacing(0);
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->addWidget(stackedWidget);
    vLayout->addWidget(tabbar);
    setLayout(vLayout);
}
