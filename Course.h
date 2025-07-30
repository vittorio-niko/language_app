#ifndef COURSE_H
#define COURSE_H
#include <QStackedWidget>
#include <QListWidget>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QPushButton>

#include "Switcher.h"
#include "Task.h"
#include "GrammarBlock.h"
#include "ListeningBlock.h"
#include "ReadingBlock.h"
#include "MainCourseInfo.h"
#include "SubmitCourseDialog.h"

class Course : public QWidget {
    Q_OBJECT
public:
    explicit Course(const QString& courseDataBasePath, const Complexity& complexity,
                    QWidget* parent = nullptr);
    const QString& getCourseName() const;
    int getCourseValue() const;
    int getCourseScore() const;
    int getCoursePercent() const;
    static MainCourseInfo getMainCourseInfo(const QSqlDatabase& db);

    ~Course();
signals:
    void courseSubmited(int coursePercent);

public slots:
    void changeVisibleBlock(int newVisibleBlockNumber);
    void initSubmissionDialog();

private:
    void generateBlocks();
    QWidget* getIntroPage(const MainCourseInfo& courseInfo);
    void setupTimer(QWidget* parent);

private:
    QListWidget *sectionList;
    QStackedWidget *stackedWidget;
    Switcher *leftArrow;
    Switcher *rightArrow;
    QPushButton *submitButton;
    QTimer *countdownTimer;
    QLabel *timerLabel;

private:
    QSqlDatabase db;
    MainCourseInfo courseInfo;
    Complexity complexity;
    QVector<Block*> blocks;
    int courseValue;
    QTime remainingTime;
};

#endif // COURSE_H
