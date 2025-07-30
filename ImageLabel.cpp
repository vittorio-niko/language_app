#include "ImageLabel.h"

ImageLabel::ImageLabel(const QString& imagePath, const QSize& size,
                       QWidget *parent): QLabel(parent) {
    QPixmap pixmap(imagePath);
    QPixmap scaledPixmap = pixmap.scaled(size, Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation);
    setPixmap(scaledPixmap);
    setFixedSize(scaledPixmap.size());
    setScaledContents(true);
}
