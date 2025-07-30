#ifndef SUBMITCOURSEDIALOG_H
#define SUBMITCOURSEDIALOG_H
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>

#include "StyledLabel.h"
#include "ProjectConstants.h"

class SubmitCourseDialog : public QDialog {
    Q_OBJECT
public:
    SubmitCourseDialog(QWidget *parent = nullptr);
private:
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // SUBMITCOURSEDIALOG_H
