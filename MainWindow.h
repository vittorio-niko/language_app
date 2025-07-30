#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QStackedWidget>
#include "ProjectConstants.h"
#include "Course.h"
#include "CourseSection.h"
#include "MainPage.h"
#include "ResultPage.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(const QString& coursesDataBasePath,
               QWidget *parent = nullptr);
public slots:
    void openCourse(Course* course);
    void showResultPage(int coursePercent);
private:
    void closeCurrentCourse();
    void closeResultPage();
    void returnToTheMainPage();

private:
    QStackedWidget *mainStackedWidget;
    Course *currentCourse;
    MainPage *mainPage;
    ResultPage *resultPage;
};


#endif // MAINWINDOW_H
