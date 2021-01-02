#include "qanimationstackedwidget.h"
#include <QPainter>
#include<algorithm>

QAnimationStackedWidget::QAnimationStackedWidget(QWidget *parent) : QStackedWidget(parent),isLoopValue(false) {
    isAnimation = false;
    //设置默认的时间间隔
    duration = 300;
    //初始化animation框架、并连接信号和槽
    animation = new QPropertyAnimation(this, QByteArray());
    connect(animation, SIGNAL(valueChanged(QVariant)), this, SLOT(valueChanged_slot(QVariant)));
    connect(animation, SIGNAL(finished()), this, SLOT(animationFinished()));
    leftPixmap = rightPixMap = nullptr;
}

void QAnimationStackedWidget::setLoop(bool isLoop) {
    isLoopValue = isLoop;
}

void QAnimationStackedWidget::next() {
    //如果正在动画，那么return
    if( isAnimation ) {
        return;
    }else if(!isLoopValue && currentIndex() >= count() - 1) {
        return;
    }

    isNext = true;
    isAnimation = true;
    int c = currentIndex();
    nextIndex = (c + 1) % count();
    widget(c)->hide();
    animation->setStartValue(geometry().width());
    animation->setEndValue(0);
    animation->setDuration(duration);
    animation->start();
}

void QAnimationStackedWidget::pop() {
    //如果正在动画，那么return
    if( isAnimation ) {
        return;
    }else if(!isLoopValue && currentIndex() <= 0) {
        return;
    }

    isNext = false;
    isAnimation = true;
    int c = currentIndex();
    nextIndex = (c - 1 + count()) % count();
    widget(c)->hide();
    animation->setStartValue(0);
    animation->setEndValue(geometry().width());
    animation->setDuration(duration);
    animation->start();
}

void QAnimationStackedWidget::valueChanged_slot(QVariant value)
{
    currentValue = value;
    update();
}

void QAnimationStackedWidget::paintEvent(QPaintEvent *e) {
    if(isAnimation) {
        QPainter paint(this);

        if(isNext) {
            QWidget *w = widget(currentIndex());
            leftPixmap = new QPixmap(w->size());
            w->render(leftPixmap);

            QWidget *nextWidget = widget(nextIndex);
            nextWidget->resize(geometry().width(), geometry().height());
            rightPixMap = new QPixmap(nextWidget->size());
            nextWidget->render(rightPixMap);
        }else {
            QWidget *nextWidget = widget(nextIndex);
            leftPixmap = new QPixmap(nextWidget->size());
            nextWidget->render(leftPixmap);
            nextWidget->resize(geometry().width(), geometry().height());

            QWidget *w = widget(currentIndex());
            rightPixMap = new QPixmap(w->size());
            w->render(rightPixMap);
        }

        paintPrevious(paint);
        paintNext(paint);
    }
}

void QAnimationStackedWidget::paintPrevious(QPainter &paint) {
    QRect r = geometry();
    double value = currentValue.toDouble();
    QRectF r1(0.0, 0.0, value, r.height());
    QRectF r2(r.width() - value, 0, value, r.height());
    paint.drawPixmap(r1, *leftPixmap, r2);
}

void QAnimationStackedWidget::paintNext(QPainter &paint) {
    QRect r = geometry();
    double value = currentValue.toDouble();
    QRectF r1(value, 0.0, r.width() - value, r.height());
    QRectF r2(0.0, 0.0, r.width() - value, r.height());
    paint.drawPixmap(r1, *rightPixMap, r2);
}

void QAnimationStackedWidget::animationFinished() {
    isAnimation = false;
    widget(currentIndex())->show();
    setCurrentIndex(nextIndex);
    delete leftPixmap;
    delete rightPixMap;
}

