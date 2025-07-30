#ifndef MAINPAGE_H
#define MAINPAGE_H
#include <QMainWindow>
#include <QMediaPlayer>
#include <QDebug>
#include "CourseSection.h"
#include "ProjectConstants.h"

class MainPage: public QWidget {
    Q_OBJECT
public:
    explicit MainPage(const QString& coursesDataBasePath,
                      QWidget* parent = nullptr);
    ~MainPage();
signals:
    void courseStarted(Course* course);
public slots:
    void startCourse(Course *course);
private:
    void setupCourseSections(QWidget* parent);
private:
    QSqlDatabase courses_db;
    QVector<CourseSection*> course_sections;
};

#endif // MAINPAGE_H
