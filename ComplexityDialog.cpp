#include "ComplexityDialog.h"

ComplexityDialog::ComplexityDialog(QWidget *parent): QDialog(parent) {
    setWindowTitle(Titles::complexityDialogTitle);
    setWindowIcon(QIcon(Paths::mainWindowIconPath));
    setFixedSize(Proportions::complexityDialogSize);

    label = new StyledLabel(Texts::chooseComplexity, this);
    radioEasy = new QRadioButton(Texts::easyLevel, this);
    radioEasy->setStyleSheet(Styles::radioButtonStyle);
    StyledLabel *easyHintLabel = new StyledLabel(Texts::easyLevelDescription);
    easyHintLabel->setAlignment(Qt::AlignLeft);
    radioHard = new QRadioButton(Texts::hardLevel, this);
    radioHard->setStyleSheet(Styles::radioButtonStyle);
    StyledLabel *hardHintLabel = new StyledLabel(Texts::hardLevelDescription);
    hardHintLabel->setAlignment(Qt::AlignLeft);

    okButton = new QPushButton(Texts::ok, this);
    okButton->setStyleSheet(Styles::dialogButtonStyle);
    cancelButton = new QPushButton(Texts::cancel, this);
    cancelButton->setStyleSheet(Styles::dialogButtonStyle);

    radioEasy->setChecked(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label);
    mainLayout->addWidget(radioEasy);
    mainLayout->addWidget(easyHintLabel);
    mainLayout->addWidget(radioHard);
    mainLayout->addWidget(hardHintLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &ComplexityDialog::onAccept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

Complexity ComplexityDialog::getSelectedComplexity() const {
    if (radioEasy->isChecked()) {
        return Complexity::Easy;
    } else if (radioHard->isChecked()) {
        return Complexity::Hard;
    }
}

void ComplexityDialog::onAccept() {
    if (!radioEasy->isChecked() && !radioHard->isChecked()) {
        QMessageBox::warning(this, Titles::warningTitle,
                             Texts::chooseAnOption);
        return;
    } else {
        accept();
    }
}
