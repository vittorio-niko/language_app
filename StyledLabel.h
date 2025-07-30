#ifndef STYLEDLABEL_H
#define STYLEDLABEL_H
//Qt libraries
#include <QLabel>

//Custom libraries
#include "ProjectConstants.h"

class StyledLabel: public QLabel {
    Q_OBJECT
public:
    explicit StyledLabel(const QString& label, QWidget* parent = nullptr);
};

#endif // STYLEDLABEL_H
