#include "Question.h"

Question::Question(QWidget *questionWidget, int id, int value, QWidget *parent):
    QWidget(parent), questionWidget(questionWidget), id(id), value(value) {
    questionWidget->setParent(this);
}

int Question::getQuestionValue() const {
    return this->value;
}

int Question::getQuestionScore() const {
    if (checkAnswer()) {
        return this->value;
    } else {
        return 0;
    }
}
