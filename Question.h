#ifndef QUESTION_H
#define QUESTION_H
#include <QWidget>

#include "QuestionType.h"
#include "ProjectConstants.h"

class Question: public QWidget {
    Q_OBJECT
public:
    explicit Question(QWidget* questionWidget, int id, int value,
                      QWidget* parent = nullptr);

    int getQuestionValue() const;
    virtual int getQuestionScore() const;
protected:
    virtual bool checkAnswer() const = 0;
    //virtual void highlightQuestion() = 0;

protected:
    QWidget *questionWidget;
    int id;
    int value;
};

#endif // QUESTION_H
