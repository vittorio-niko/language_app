#include "StyledLabel.h"

StyledLabel::StyledLabel(const QString& label, QWidget *parent):
    QLabel(label, parent) {
    setStyleSheet(Styles::labelStyle);
    setWordWrap(true);
}
