#include "OptionQuestion.h"

OptionQuestion::OptionQuestion(QWidget *questionWidget, int id, const QStringList& optionList,
                               int correctOptionNumber, int value, QWidget *parent):
    Question(questionWidget, id, value, parent), correctOptionNumber(correctOptionNumber) {
    QVBoxLayout *questionLayout = new QVBoxLayout(this);
    questionLayout->addWidget(questionWidget);
    buttonGroup = new QButtonGroup(this);
    for (int i = 0; i < optionList.count(); ++i) {
        QRadioButton *radio = new QRadioButton(optionList[i]);
        radio->setStyleSheet(Styles::radioButtonStyle);
        questionLayout->addWidget(radio);
        buttonGroup->addButton(radio, i);  //Each button Id
    }

    this->setLayout(questionLayout);
}

bool OptionQuestion::checkAnswer() const {
    int chosenOptionId = buttonGroup->checkedId();
    return correctOptionNumber == chosenOptionId;
}
