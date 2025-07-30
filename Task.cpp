#include "Task.h"

Task::Task(QWidget* taskDescriptionWidget, const QString& taskName,
           const QVector<Question*>& questions, QWidget* parent):
    QGroupBox(taskName, parent), taskName(taskName),
    taskDescriptionWidget(taskDescriptionWidget), questions(questions) {
    setStyleSheet(Styles::groupStyle);

    QVBoxLayout *taskLayout = new QVBoxLayout(this);
    taskLayout->setContentsMargins(Proportions::taskContentMargins);

    if (taskDescriptionWidget) {
        taskDescriptionWidget->setParent(this);
        taskLayout->addWidget(taskDescriptionWidget);
    }

    taskValue = 0;
    for (const auto& question : questions) {
        taskValue += question->getQuestionValue();
        question->setParent(this);
        taskLayout->addWidget(question);
    }

    setLayout(taskLayout);
}

const QString& Task::getTaskName() const {
    return this->taskName;
}

int Task::getTaskValue() const {
    return this->taskValue;
}

int Task::getTaskScore() const {
    int taskScore = 0;
    for (const auto& question : this->questions) {
        taskScore += question->getQuestionScore();
    }
    return taskScore;
}
