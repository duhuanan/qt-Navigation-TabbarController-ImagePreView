#ifndef QNAVIGATION_H
#define QNAVIGATION_H
#include "qanimationstackedwidget.h"

class QNavigationItem {
private:
    std::string mTitle, mNormalImage, mSelectImage;
    std::string mNormalColor, mSelectColor;
public:
    QNavigationItem(std::string t,
                    std::string ni,
                    std::string si) {
        mTitle = t;
        mNormalImage = ni;
        mSelectImage = si;
        mNormalColor = "#232323";
        mSelectColor = "#289bFF";
    }

    std::string title() {
        return mTitle;
    }

    std::string normalImage() {
        return mNormalImage;
    }

    std::string selectImage() {
        return mSelectImage;
    }

    std::string normalColor() {
        return mNormalColor;
    }

    std::string selectColor() {
        return mSelectColor;
    }

    void setTitle(std::string t) {
        mTitle = t;
    }

    void setNormalImage(std::string ni) {
        mNormalImage = ni;
    }

    void setSelectImage(std::string si) {
        mSelectImage = si;
    }

    void setNormalColor(std::string ni) {
        mNormalColor = ni;
    }

    void setSelectColor(std::string si) {
        mSelectColor = si;
    }
};

class QNavigation : public QAnimationStackedWidget
{
public:
    explicit QNavigation(QWidget *parent = 0);
    void pushWidget(QWidget *ctl);

    virtual QNavigationItem item() {
        QNavigationItem tItem("主页", "", "");
        return tItem;
    }
};

#endif // QNAVIGATION_H
