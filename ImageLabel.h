#ifndef IMAGELABEL_H
#define IMAGELABEL_H
#include <QLabel>
#include <QSize>
#include <QPixmap>

class ImageLabel: public QLabel {
    Q_OBJECT
public:
    explicit ImageLabel(const QString& imagePath, const QSize& size,
                        QWidget* parent = nullptr);
};

#endif // IMAGELABEL_H
