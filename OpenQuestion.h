#ifndef OPENQUESTION_H
#define OPENQUESTION_H
#include <QLineEdit>
#include <QString>
#include <QVBoxLayout>
#include "Question.h"

class OpenQuestion final: public Question {
    Q_OBJECT
public:
    explicit OpenQuestion(QWidget* questionWidget, int id, const QString& answer,
                          int value, QWidget* parent = nullptr);

protected:
    bool checkAnswer() const override;
private:
    QLineEdit *answerField;
    QString answer;
};

#endif // OPENQUESTION_H
