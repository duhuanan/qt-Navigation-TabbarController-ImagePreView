#include "qnavigation.h"

QNavigation::QNavigation(QWidget *parent) : QAnimationStackedWidget(parent) {
    isLoopValue = false;
}

void QNavigation::pushWidget(QWidget *ctl) {
    if(count() == 0) {
        addWidget(ctl);
        setCurrentWidget(ctl);
        return;
    }

    //如果正在动画，那么return
    if( isAnimation ) {
        return;
    }

    isNext = true;
    isAnimation = true;
    int c = currentIndex();
    nextIndex = c + 1;
    addWidget(ctl);
    widget(c)->hide();
    animation->setStartValue(geometry().width());
    animation->setEndValue(0);
    animation->setDuration(duration);
    animation->start();
}
