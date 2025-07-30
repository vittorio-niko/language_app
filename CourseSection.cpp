#include "CourseSection.h"

CourseSection::CourseSection(const QString& courseName, const QString& courseDataBasePath,
                             QWidget* parent): QFrame(parent),
                                               courseDataBasePath(courseDataBasePath),
                                               course(nullptr){
    setFrameStyle(QFrame::Box | QFrame::Raised);
    setLineWidth(2);

    titleLabel = new StyledLabel(courseName, this);
    titleLabel->setAlignment(Qt::AlignCenter);

    startButton = new QPushButton(Texts::startCourse, this);

    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setTextVisible(true);
    progressBar->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(startButton);
    layout->addWidget(progressBar);
    setLayout(layout);

    connect(startButton, &QPushButton::clicked, this, &CourseSection::onStartButtonClicked);
}

void CourseSection::updateProgress(int percent) {
    progressBar->setValue(percent);
}

void CourseSection::onStartButtonClicked() {
    ComplexityDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Complexity complexity = dialog.getSelectedComplexity();
        course = new Course(courseDataBasePath, complexity);
        connect(course, &Course::courseSubmited, this, &CourseSection::updateProgress);
        emit startCourseRequested(course);
    }
}

