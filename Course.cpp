#include "Course.h"

Course::Course(const QString& courseDataBasePath, const Complexity& complexity,
               QWidget *parent): QWidget(parent), countdownTimer(nullptr),
                                 timerLabel(nullptr), complexity(complexity) {
    QWidget* mainWidget = new QWidget();
    setLayout(new QVBoxLayout());
    layout()->addWidget(mainWidget);

    //Setup db
    QString connectionName = QString("Course_%1").arg(quintptr(this));
    db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(courseDataBasePath);
    db.open();
    courseInfo = getMainCourseInfo(db);
    remainingTime = courseInfo.limit;

    //Blocks list
    sectionList = new QListWidget(mainWidget);
    sectionList->setStyleSheet(Styles::listWidgetStyle);
    sectionList->setFixedWidth(Proportions::sectionListWidth);

    stackedWidget = new QStackedWidget(mainWidget);
    QWidget* introPage = getIntroPage(courseInfo);
    stackedWidget->addWidget(introPage);
    sectionList->addItem("Introduction");
    sectionList->setCurrentRow(0);

    generateBlocks();

    //Course value calculation
    courseValue = 0;
    for (const auto& block : std::as_const(blocks)) {
        courseValue += block->getBlockValue();
    }

    //Switchers
    leftArrow = new Switcher(Paths::leftArrowIconPath, Proportions::switcherSize,
                             Proportions::switcherIconSize, "", Styles::switcherStyle, mainWidget);
    rightArrow = new Switcher(Paths::rightArrowIconPath, Proportions::switcherSize,
                              Proportions::switcherIconSize, "", Styles::switcherStyle, mainWidget);

    submitButton = new QPushButton(Texts::sendResults, mainWidget);
    submitButton->setStyleSheet(Styles::submitButtonStyle);

    setupTimer(mainWidget);

    //Layouts
    QHBoxLayout* mainLayout = new QHBoxLayout();
    QVBoxLayout* leftLayout = new QVBoxLayout();
    QVBoxLayout* rightLayout = new QVBoxLayout();
    QHBoxLayout* switchersLayout = new QHBoxLayout();

    //Left section
    leftLayout->addWidget(sectionList);
    leftLayout->addWidget(submitButton);
    leftLayout->addStretch();

    //Right section
    rightLayout->addWidget(stackedWidget);
    if (timerLabel) {
        leftLayout->addWidget(timerLabel);
    }

    //Switchers layout
    switchersLayout->addStretch();
    switchersLayout->addWidget(leftArrow);
    switchersLayout->addWidget(rightArrow);
    switchersLayout->addStretch();
    leftLayout->addLayout(switchersLayout);

    //Columns to the main layout
    mainLayout->addLayout(leftLayout, 1); //ratio 1:3
    mainLayout->addLayout(rightLayout, 3);

    mainWidget->setLayout(mainLayout);

    connect(sectionList, &QListWidget::currentRowChanged, stackedWidget, &QStackedWidget::setCurrentIndex);
    connect(sectionList, &QListWidget::currentRowChanged, this, [=](int currentIndex) {
        leftArrow->setEnabled(currentIndex > 0);
        rightArrow->setEnabled(currentIndex < stackedWidget->count() - 1);
    });

    connect(leftArrow, &Switcher::clicked, this, [=]() {
        int newIndex = stackedWidget->currentIndex() - 1;
        stackedWidget->setCurrentIndex(newIndex);
        sectionList->setCurrentRow(newIndex);
    });

    connect(rightArrow, &Switcher::clicked, this, [=]() {
        int newIndex = stackedWidget->currentIndex() + 1;
        stackedWidget->setCurrentIndex(newIndex);
        sectionList->setCurrentRow(newIndex);
    });

    connect(submitButton, &QPushButton::clicked, this, &Course::initSubmissionDialog);
}

const QString& Course::getCourseName() const {
    return this->courseInfo.name;
}

int Course::getCourseValue() const {
    return this->courseValue;
}

int Course::getCourseScore() const {
    int courseScore = 0;
    for (const auto& block : this->blocks) {
        courseScore += block->getBlockScore();
    }
    return courseScore;
}

int Course::getCoursePercent() const {
    double courseScore = this->getCourseScore();
    double coursePercent = (courseScore / courseValue) * 100;
    return static_cast<int>(coursePercent);
}

void Course::changeVisibleBlock(int newVisibleBlockNumber) {
    stackedWidget->setCurrentIndex(newVisibleBlockNumber);
}

void Course::setupTimer(QWidget* parent) {
    timerLabel = new QLabel(parent);
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setStyleSheet(Styles::timerStyle);
    if (remainingTime == QTime()) {
        timerLabel->hide();
    } else {
        timerLabel->setText("Time left: " + remainingTime.toString(Formats::timeFormat));

        countdownTimer = new QTimer(this);
        countdownTimer->setInterval(Time::countdownTimerInterval);
        countdownTimer->start();

        //Timer signal
        connect(countdownTimer, &QTimer::timeout, this, [=]() mutable {
            remainingTime = remainingTime.addSecs(-1);
            timerLabel->setText("Time left: " + remainingTime.toString("hh:mm:ss"));

            if (remainingTime == QTime(0, 0, 0)) {
                countdownTimer->stop();
                QMessageBox::warning(this, "Time is up", "The course time has ended!");
                emit courseSubmited(getCoursePercent());
            }
        });
    }
}

void Course::generateBlocks() {
    QSqlQuery blocksQuery(db);
    blocksQuery.prepare(QString("SELECT * FROM blocks"));
    blocksQuery.exec();
    while (blocksQuery.next()) {
        QString blockName = blocksQuery.value("block_name").toString();
        auto blockType = static_cast<BlockType>(blocksQuery.value("block_type").toInt());
        QString blockDbPath = QString(PROJECT_PATH) + blocksQuery.value("block_db_path").toString();
        sectionList->addItem(blockName);
        switch (blockType) {
            case BlockType::Grammar: {
                GrammarBlock *newBlock = new GrammarBlock(blockDbPath, complexity);
                blocks.append(newBlock);
                stackedWidget->addWidget(newBlock);
                break;
            }
            case BlockType::Listening: {
                ListeningBlock *newBlock = new ListeningBlock(blockDbPath, complexity, stackedWidget);
                blocks.append(newBlock);
                stackedWidget->addWidget(newBlock);
                break;
            }
            case BlockType::Reading: {
                ReadingBlock *newBlock = new ReadingBlock(blockDbPath, complexity, stackedWidget);
                blocks.append(newBlock);
                stackedWidget->addWidget(newBlock);
                break;
            }
        }
    }

}

QWidget* Course::getIntroPage(const MainCourseInfo& courseInfo) {
    QWidget* contentWidget = new QWidget();
    QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);

    QLabel* header = new QLabel(courseInfo.name);
    header->setAlignment(Qt::AlignCenter);
    header->setStyleSheet(Styles::blockHeaderStyle);

    ImageLabel* imageLabel = new ImageLabel(Paths::courseIntroDuoPath,
                                            Proportions::enlargedImageSize);
    imageLabel->setStyleSheet(Styles::imageFrameStyle);

    StyledLabel* textLabel = new StyledLabel(courseInfo.intro);

    contentLayout->addWidget(header);
    contentLayout->addWidget(imageLabel, 0, Qt::AlignCenter);
    contentLayout->addWidget(textLabel);

    //Scroll area
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QWidget* mainPageWidget = new QWidget();
    QVBoxLayout* mainPageLayout = new QVBoxLayout(mainPageWidget);
    mainPageLayout->addWidget(scrollArea);

    return mainPageWidget;
}

MainCourseInfo Course::getMainCourseInfo(const QSqlDatabase& db) {
    QSqlQuery mainInfoQuery(db);
    mainInfoQuery.prepare(QString("SELECT * FROM %1").arg("course_info"));
    mainInfoQuery.exec();
    mainInfoQuery.next();
    QString name = mainInfoQuery.value("course_name").toString();
    QString intro = mainInfoQuery.value("course_intro").toString();
    QString limitString = mainInfoQuery.value("course_time_limit").toString();
    QTime limit;
    if (limitString.isEmpty()) {
        limit = QTime();
    } else {
        limit = QTime::fromString(limitString, Formats::timeFormat);
    }
    MainCourseInfo courseInfo = {name, intro, limit};
    return courseInfo;
}

void Course::initSubmissionDialog() {
    SubmitCourseDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        emit courseSubmited(getCoursePercent());
    }
}

Course::~Course() {
    qDeleteAll(blocks);
    blocks.clear();

    QString connectionName = db.connectionName();
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connectionName);
}
