#include "HelpButton.h"

HelpButton::HelpButton(const QString& helpText, QWidget* parent):
    QToolButton(parent), helpText(helpText) {
    setText("Help");
    setToolButtonStyle(Qt::ToolButtonTextOnly);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(Proportions::helpButtonSize);

    setStyleSheet(Styles::helpButtonStyle);

    //Timer for some delay
    hoverTimer = new QTimer(this);
    hoverTimer->setSingleShot(true);
    connect(hoverTimer, &QTimer::timeout, this, [=](){
        QToolTip::showText(QCursor::pos(), helpText, this, rect());
    });
}

void HelpButton::enterEvent(QEnterEvent* event) {
    QToolButton::enterEvent(event);
    hoverTimer->start(Time::helpInfoDelay);
}

void HelpButton::leaveEvent(QEvent* event) {
    QToolButton::leaveEvent(event);
    hoverTimer->stop();
    QToolTip::hideText();
}
