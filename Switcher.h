#ifndef SWITCHER_H
#define SWITCHER_H
#include <QToolButton>
#include <QIcon>
#include <QSize>
#include <QString>

#include "ProjectConstants.h"

class Switcher: public QToolButton {
    Q_OBJECT
public:
    explicit Switcher(const QString& switcherIconPath, const QSize& switcherFixedSize,
                      const QSize& switcherIconSize, const QString& switcherComment,
                      const QString& switcherStyle, QWidget* parent = nullptr);
    void disableSwitcher();
    void setContextComment(const QString& comment);
};

#endif // SWITCHER_H
