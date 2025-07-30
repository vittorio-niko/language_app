#include "OpenQuestion.h"

OpenQuestion::OpenQuestion(QWidget* questionWidget, int id, const QString& answer,
    int value, QWidget* parent): Question(questionWidget, id, value, parent), answer(answer) {
    QVBoxLayout *questionLayout = new QVBoxLayout(this);
    answerField = new QLineEdit(this);
    answerField->setStyleSheet(Styles::lineEditStyle);
    questionLayout->addWidget(questionWidget);
    questionLayout->addWidget(answerField);
    this->setLayout(questionLayout);
}

bool OpenQuestion::checkAnswer() const {
    if (QString::compare(answerField->text(), answer,
                         Qt::CaseInsensitive) == 0) {
        return true;
    } else {
        return false;
    }
}
