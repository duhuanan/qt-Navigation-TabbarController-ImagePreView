#ifndef QIMAGEPREVIEWVIEW_H
#define QIMAGEPREVIEWVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "qglobaldefine.h"

class QImagePreviewView : public QGraphicsView {
    Q_OBJECT
public:
    explicit QImagePreviewView(QWidget *parent = 0);
    void setImage(string imgUrl);
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    QGraphicsScene *scene;
signals:
    void onPress(bool isNext);
};

#endif // QIMAGEPREVIEWVIEW_H
