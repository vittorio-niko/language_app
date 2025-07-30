#ifndef RESULTPAGE_H
#define RESULTPAGE_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "StyledLabel.h"
#include "ImageLabel.h"
#include "ProjectConstants.h"

class ResultPage: public QWidget {
    Q_OBJECT
public:
    explicit ResultPage(const QString& courseName,
                        int coursePercent,
                        QWidget* parent = nullptr);
signals:
    void returnRequired();
private:
    QPushButton *returnButton;
};

#endif // RESULTPAGE_H
