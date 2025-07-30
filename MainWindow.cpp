#include "MainWindow.h"

MainWindow::MainWindow(const QString& coursesDataBasePath, QWidget *parent):
    QMainWindow(parent), currentCourse(nullptr), resultPage(nullptr) {
    setWindowTitle(Titles::mainWindowTitle);
    setWindowIcon(QIcon(Paths::mainWindowIconPath));
    setMinimumSize(Proportions::mainWindowMinSize);
    resize(Proportions::mainWindowSize);

    mainStackedWidget = new QStackedWidget(this);
    mainPage = new MainPage(coursesDataBasePath, mainStackedWidget);
    mainStackedWidget->addWidget(mainPage);
    mainStackedWidget->setCurrentWidget(mainPage);

    connect(mainPage, &MainPage::courseStarted, this, &MainWindow::openCourse);
    setCentralWidget(mainStackedWidget);
}

void MainWindow::openCourse(Course* course) {
    currentCourse = course;
    currentCourse->setParent(mainStackedWidget);
    mainStackedWidget->addWidget(currentCourse);
    mainStackedWidget->setCurrentWidget(currentCourse);
    connect(currentCourse, &Course::courseSubmited, this, &MainWindow::showResultPage);
}

void MainWindow::showResultPage(int coursePercent) {
    resultPage = new ResultPage(currentCourse->getCourseName(), coursePercent, mainStackedWidget);
    connect(resultPage, &ResultPage::returnRequired, this, [=](){
        closeCurrentCourse();
        closeResultPage();
        returnToTheMainPage();
    });
    mainStackedWidget->addWidget(resultPage);
    mainStackedWidget->setCurrentWidget(resultPage);
}

void MainWindow::closeCurrentCourse() {
    mainStackedWidget->removeWidget(currentCourse);
    disconnect(currentCourse, nullptr, nullptr, nullptr);
    delete currentCourse;
    currentCourse = nullptr;
}

void MainWindow::closeResultPage() {
    mainStackedWidget->removeWidget(resultPage);
    disconnect(resultPage, nullptr, nullptr, nullptr);
    delete resultPage;
    resultPage = nullptr;
}

void MainWindow::returnToTheMainPage() {
    mainStackedWidget->setCurrentWidget(mainPage);
}
