#include "qimagepreviewview.h"
#include "qfiledownloadmanager.h"

QImagePreviewView::QImagePreviewView(QWidget *parent) : QGraphicsView(parent) {
    scene = nullptr;
}

void QImagePreviewView::setImage(string imgUrl) {
    QFileDownloadManager::fileManager()->download(imgUrl, [&](QPixmap &pix) {
        scene = new QGraphicsScene(this);
        scene->addPixmap(pix);
        setScene(scene);
        fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    });
}

void QImagePreviewView::mousePressEvent(QMouseEvent *event) {
    emit this->onPress(event->x() > this->width() / 2.0);
}

void QImagePreviewView::resizeEvent(QResizeEvent *event) {
    if(scene != nullptr) {
        fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }

    QGraphicsView::resizeEvent(event);
}
