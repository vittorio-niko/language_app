#include "SubmitCourseDialog.h"

SubmitCourseDialog::SubmitCourseDialog(QWidget *parent): QDialog(parent) {
    setWindowTitle(Titles::submissionDialogTitle);
    setWindowIcon(QIcon(Paths::mainWindowIconPath));
    setFixedSize(Proportions::submitCourseDialogSize);

    QVBoxLayout *layout = new QVBoxLayout(this);
    StyledLabel *label = new StyledLabel(Texts::confirmSubmission, this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    okButton = new QPushButton(Texts::ok, this);
    okButton->setStyleSheet(Styles::dialogButtonStyle);
    cancelButton = new QPushButton(Texts::cancel, this);
    cancelButton->setStyleSheet(Styles::dialogButtonStyle);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}
