#ifndef HELPBUTTON_H
#define HELPBUTTON_H

#include <QToolButton>
#include <QToolTip>
#include <QTimer>
#include <QStyle>

#include "ProjectConstants.h"

class HelpButton : public QToolButton {
    Q_OBJECT
public:
    explicit HelpButton(const QString& helpText, QWidget* parent = nullptr);

protected:
    void enterEvent(QEnterEvent* event) override;

    void leaveEvent(QEvent* event) override;

private:
    QString helpText;
    QTimer *hoverTimer;
};

#endif // HELPBUTTON_H
