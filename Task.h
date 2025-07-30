#ifndef TASK_H
#define TASK_H
#include <QVector>
#include <QVBoxLayout>
#include <QGroupBox>
#include "Question.h"
#include "ProjectConstants.h"

class Task : public QGroupBox {
    Q_OBJECT
public:
    explicit Task(QWidget* taskDescriptionWidget, const QString& taskName,
                  const QVector<Question*>& questions, QWidget* parent = nullptr);

    const QString& getTaskName() const;
    int getTaskValue() const;
    int getTaskScore() const;

private:
    QString taskName;
    QWidget* taskDescriptionWidget;
    int taskValue;
    QVector<Question*> questions;
};


#endif // TASK_H
