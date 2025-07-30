#include "MainPage.h"

MainPage::MainPage(const QString& coursesDataBasePath,
                   QWidget *parent): QWidget(parent) {
    QWidget* innerWidget = new QWidget();
    QVBoxLayout *innerLayout = new QVBoxLayout(innerWidget);

    QLabel *welcomingHeader = new QLabel("Welcome in Duolingo!", innerWidget);
    welcomingHeader->setAlignment(Qt::AlignCenter);
    welcomingHeader->setStyleSheet(Styles::mainHeaderStyle);
    innerLayout->addWidget(welcomingHeader);

    ImageLabel *welcomingImageLabel = new ImageLabel(":images/welcoming_duo.png",
                                                     Proportions::enlargedImageSize,
                                                     innerWidget);
    innerLayout->addWidget(welcomingImageLabel, 0, Qt::AlignCenter);

    QString connectionName = QString("MainPage_%1").arg(quintptr(this));
    courses_db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    courses_db.setDatabaseName(coursesDataBasePath);
    courses_db.open();
    setupCourseSections(innerWidget);
    for (const auto& course_section : std::as_const(course_sections)) {
        innerLayout->addWidget(course_section);
        connect(course_section, &CourseSection::startCourseRequested, this, &MainPage::startCourse);
    }

    innerWidget->setLayout(innerLayout);

    //Scroll area
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(innerWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QVBoxLayout *mainPageLayout = new QVBoxLayout(this);
    mainPageLayout->addWidget(scrollArea);

    setLayout(mainPageLayout);
}

void MainPage::setupCourseSections(QWidget* parent) {
    QSqlQuery coursesQuery(courses_db);
    coursesQuery.prepare(QString("SELECT course_name, course_db_path FROM courses"));
    coursesQuery.exec();
    while (coursesQuery.next()) {
        QString course_name = coursesQuery.value("course_name").toString();
        QString relative_course_db_path = coursesQuery.value("course_db_path").toString();
        QString abs_course_db_path = QString(PROJECT_PATH) + relative_course_db_path;
        CourseSection *section = new CourseSection(course_name, abs_course_db_path, parent);
        section->setStyleSheet(Styles::courseSectionStyle);
        course_sections.append(section);
    }
}

void MainPage::startCourse(Course *course) {
    emit courseStarted(course);
}

MainPage::~MainPage() {
    qDeleteAll(course_sections);
    course_sections.clear();

    QString connectionName = courses_db.connectionName();
    courses_db.close();
    courses_db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connectionName);
}
