#ifndef QANIMATIONSTACKEDWIDGET_H
#define QANIMATIONSTACKEDWIDGET_H

#include <QStackedWidget>
#include <QPropertyAnimation>

class QAnimationStackedWidget : public QStackedWidget
{
    Q_OBJECT
    public:
        explicit QAnimationStackedWidget(QWidget *parent = 0);
        void paintEvent(QPaintEvent *);
        //设置动画持续的间隔
        void setDuration(int );
        void setLoop(bool isLoop);
        ~QAnimationStackedWidget() {}
    signals:

    public slots:
        //属性动画值改变的槽
        void valueChanged_slot(QVariant );
        //动画切换完成
        void animationFinished();
        //前一页
        void next();
        //下一页
        virtual void pop();
    private:
        void paintPrevious(QPainter &);
        void paintNext(QPainter &);
    protected:
        QPropertyAnimation *animation; //动画框架
        int duration;                   //动画的持续时间
        bool isAnimation;               //是否正在动画
        QVariant       currentValue;    //被Animation动画改变的值
        int         nextIndex;          //下一个要切换的索引
        bool isNext, isLoopValue;
        QPixmap *leftPixmap, *rightPixMap;
};

#endif // QANIMATIONSTACKEDWIDGET_H
