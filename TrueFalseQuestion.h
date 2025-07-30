#ifndef TRUEFALSEQUESTION_H
#define TRUEFALSEQUESTION_H
#include <QRadioButton>
#include <QVBoxLayout>
#include <QButtonGroup>
#include "Question.h"

class TrueFalseQuestion final: public Question {
    Q_OBJECT
public:
    explicit TrueFalseQuestion(QWidget* questionWidget, int id, bool answer,
                               int value, QWidget* parent = nullptr);
protected:
    bool checkAnswer() const override;
private:
    QButtonGroup *buttonGroup;
    bool answer;
};

#endif // TRUEFALSEQUESTION_H
