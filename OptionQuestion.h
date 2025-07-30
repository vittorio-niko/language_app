#ifndef OPTIONQUESTION_H
#define OPTIONQUESTION_H
#include <QRadioButton>
#include <QVBoxLayout>
#include <QStringList>
#include <QButtonGroup>

#include "Question.h"
#include "ProjectConstants.h"

class OptionQuestion final: public Question {
    Q_OBJECT
public:
    explicit OptionQuestion(QWidget* questionWidget, int id, const QStringList& optionList,
                            int correctOptionNumber, int value, QWidget* parent = nullptr);
protected:
    bool checkAnswer() const override;
private:
    QButtonGroup *buttonGroup;
    int correctOptionNumber;
};

#endif // OPTIONQUESTION_H
