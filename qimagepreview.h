#ifndef QIMAGEPREVIEW_H
#define QIMAGEPREVIEW_H
#include <QDialog>
#include <vector>
#include <string>
#include "qnavigation.h"

class QImagePreview : public QDialog {
    Q_OBJECT
private:
    int currentIdx;
    std::vector<std::string> imgUrls;
    QNavigation *stackView;
    void initView();
public:
    QImagePreview(QWidget *parent);

    /**
      设置图片数组
     * @brief setImages
     * @param imgs
     */
    void setImages(std::vector<std::string> imgs);

    /**
      显示
     * @brief showWithIndex
     * @param idx
     */
    void showWithIndex(int idx = 0);

public slots:
    void onPageChange(bool isNext);
};

#endif // QIMAGEPREVIEW_H
