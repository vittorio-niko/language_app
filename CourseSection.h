#ifndef COURSESECTION_H
#define COURSESECTION_H

#include "Course.h"
#include "ComplexityDialog.h"

#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QProgressBar>
#include <QPointer>

class CourseSection : public QFrame {
    Q_OBJECT
public:
    explicit CourseSection(const QString& courseName, const QString& courseDataBasePath,
                           QWidget* parent = nullptr);
    void closeCourse();
    void updateProgress(int percent);

private slots:
    void onStartButtonClicked();

signals:
    void startCourseRequested(Course* course);

private:
    QString courseDataBasePath;
    QPointer<Course> course;
    StyledLabel* titleLabel;
    QPushButton* startButton;
    QProgressBar* progressBar;
};

#endif // COURSESECTION_H
