#include "qimagepreview.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QScreen>
#include "qimagepreviewview.h"
QImagePreview::QImagePreview(QWidget *parent) : QDialog(parent) {
}

void QImagePreview::setImages(std::vector<std::string> imgs) {
    imgUrls = imgs;
}

void QImagePreview::showWithIndex(int idx) {
    if(idx < 0) {
        currentIdx = 0;
    }else if(idx > (int)imgUrls.size() - 1) {
        currentIdx = imgUrls.size() - 1;
    }else {
        currentIdx = idx;
    }

    if(imgUrls.size() == 0) {
        return;
    }

    initView();
    exec();
}

void QImagePreview::onPageChange(bool isNext) {
    if(isNext) {
        stackView->next();
//        QImagePreviewView *preview = new QImagePreviewView(this);
//        preview->setImage(imgUrls[0]);
//        connect(preview, SIGNAL(onPress(bool)), this, SLOT(onPageChange(bool)));
//        stackView->pushWidget(preview);
    }else {
        stackView->pop();
    }
}

void QImagePreview::initView() {
    QRect clientRect = QGuiApplication::screens().at(0)->geometry();
    resize(clientRect.width(), clientRect.height());
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    stackView = new QNavigation(this);

    for(auto url : imgUrls) {
        QImagePreviewView *preview = new QImagePreviewView(this);
        preview->setImage(url);
        connect(preview, SIGNAL(onPress(bool)), this, SLOT(onPageChange(bool)));
        stackView->addWidget(preview);
    }

    stackView->setCurrentIndex(currentIdx);
    layout->addWidget(stackView);
    setLayout(layout);
}
