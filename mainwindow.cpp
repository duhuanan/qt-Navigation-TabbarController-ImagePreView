#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qglobaldefine.h"
#include "qimagepreviewview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800, 600);
    this->setWindowTitle("SKLJDLAKSHDLASD");
    std::vector<QNavigation *> navs;
    std::vector<std::string> urls;
    urls.push_back("https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fattachments.gfan.com%2Fforum%2Fattachments2%2Fday_110915%2F1109151356c0717d7e6a91e985.jpg&refer=http%3A%2F%2Fattachments.gfan.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=jpeg?sec=1612106199&t=340188ab75e7c01df77f9c1f662f6136");
    urls.push_back("https://ss2.baidu.com/-vo3dSag_xI4khGko9WTAnF6hhy/zhidao/pic/item/adaf2edda3cc7cd968cd92783801213fb90e91ab.jpg");
    urls.push_back("https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fb.zol-img.com.cn%2Fdesk%2Fbizhi%2Fimage%2F1%2F1680x1050%2F1349289433496.jpg&refer=http%3A%2F%2Fb.zol-img.com.cn&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=jpeg?sec=1612106199&t=5e0d556b8cd1a32fc93ed9c778923465");
    for(int i = 0; i < 3; i++) {
        QNavigation *nav = new QNavigation(ui->centralWidget);
        QImagePreviewView *preview = new QImagePreviewView(this);
        preview->setImage(urls[i]);
        connect(preview, SIGNAL(onPress(bool)), this, SLOT(onPageChange(bool)));
        nav->pushWidget(preview);
        navs.push_back(nav);
    }

    ui->centralWidget->setNavigations(navs);
}

void MainWindow::onPageChange(bool isNext) {
    if(isNext) {
        QImagePreviewView *preview = new QImagePreviewView(this);
        preview->setImage("https://ss2.baidu.com/-vo3dSag_xI4khGko9WTAnF6hhy/zhidao/pic/item/adaf2edda3cc7cd968cd92783801213fb90e91ab.jpg");
        connect(preview, SIGNAL(onPress(bool)), this, SLOT(onPageChange(bool)));
        ui->centralWidget->currentNavigation()->pushWidget(preview);
    }else {
        ui->centralWidget->currentNavigation()->pop();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
