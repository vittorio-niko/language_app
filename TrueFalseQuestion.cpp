#include "TrueFalseQuestion.h"

TrueFalseQuestion::TrueFalseQuestion(QWidget *questionWidget, int id, bool answer,
    int value, QWidget *parent): Question(questionWidget, id, value, parent), answer(answer) {
    QVBoxLayout *questionLayout = new QVBoxLayout(this);
    questionLayout->addWidget(questionWidget);
    buttonGroup = new QButtonGroup(this);
    QRadioButton *radioTrue = new QRadioButton("True");
    radioTrue->setStyleSheet(Styles::radioButtonStyle);
    QRadioButton *radioFalse = new QRadioButton("False");
    radioFalse->setStyleSheet(Styles::radioButtonStyle);
    questionLayout->addWidget(radioTrue);
    questionLayout->addWidget(radioFalse);
    buttonGroup->addButton(radioTrue, 1);
    buttonGroup->addButton(radioFalse, 0);

    this->setLayout(questionLayout);
}

bool TrueFalseQuestion::checkAnswer() const {
    int chosenOptionId = buttonGroup->checkedId();
    if (chosenOptionId == 1) {
        return true;
    } else {
        return false;
    }
}
