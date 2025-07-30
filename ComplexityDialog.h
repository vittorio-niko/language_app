#ifndef COMPLEXITYDIALOG_H
#define COMPLEXITYDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

#include "Complexity.h"
#include "StyledLabel.h"
#include "ProjectConstants.h"

class ComplexityDialog : public QDialog {
    Q_OBJECT
public:
    explicit ComplexityDialog(QWidget *parent = nullptr);
    Complexity getSelectedComplexity() const;
signals:
    void complexityChosen(Complexity complexity);

private slots:
    void onAccept();

private:
    StyledLabel *label;
    QRadioButton *radioEasy;
    QRadioButton *radioHard;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // COMPLEXITYDIALOG_H
