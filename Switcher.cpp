#include "Switcher.h"

Switcher::Switcher(const QString& switcherIconPath, const QSize& switcherFixedSize,
                   const QSize& switcherIconSize, const QString& switcherComment,
                   const QString& switcherStyle, QWidget *parent): QToolButton(parent) {
    setFixedSize(switcherFixedSize);
    setIcon(QIcon(switcherIconPath));
    setIconSize(switcherIconSize);
    setToolTip(switcherComment);
    setCheckable(false);
    setStyleSheet(switcherStyle);
}

void Switcher::disableSwitcher() {
    this->setDisabled(true);
}

void Switcher::setContextComment(const QString& comment) {
    this->setToolTip(comment);
}
