#include "Block.h"

Block::Block(const QString& blockDataBasePath, QWidget* parent):
    QWidget(parent), helpButton(nullptr) {
    //при сборке на базеле подумать, что делать с путями
    QString connectionName = QString("Block_%1").arg(quintptr(this));
    db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(blockDataBasePath);
    db.open();

    blockInfo = getMainBlockInfo(db);
    blockTasks = generateBlockTasks(db);
    QWidget* innerWidget = new QWidget();
    QVBoxLayout *innerLayout = new QVBoxLayout(innerWidget);

    QLabel *blockHeader = new QLabel(blockInfo.name, innerWidget);
    blockHeader->setAlignment(Qt::AlignCenter);
    blockHeader->setStyleSheet(Styles::blockHeaderStyle);

    StyledLabel *introLabel = new StyledLabel(blockInfo.intro, innerWidget);

    innerLayout->addWidget(blockHeader);
    innerLayout->addWidget(introLabel);

    if (QFile::exists(blockInfo.image_path)) {
        ImageLabel *imageLabel = new ImageLabel(blockInfo.image_path,
                                                Proportions::enlargedImageSize,
                                                innerWidget);
        innerLayout->addWidget(imageLabel, 0, Qt::AlignCenter);
    }

    QWidget *placeholder = new QWidget(innerWidget);
    mainBlockWidget = placeholder;
    innerLayout->addWidget(mainBlockWidget);

    if (!blockInfo.help.isEmpty()) {
        helpButton = new HelpButton(blockInfo.help, innerWidget);
        innerLayout->addWidget(helpButton, 0, Qt::AlignCenter);
    }

    blockValue = 0;
    for (const auto& task : std::as_const(blockTasks)) {
        blockValue += task->getTaskValue();
        innerLayout->addWidget(task);
    }

    innerWidget->setLayout(innerLayout);

    //Scroll area
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(innerWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    //Main block layout
    QVBoxLayout *blockLayout = new QVBoxLayout(this);
    blockLayout->addWidget(scrollArea);

    setLayout(blockLayout);
}

const QString& Block::getBlockName() const {
    return this->blockInfo.name;
}

int Block::getBlockValue() const {
    return this->blockValue;
}

int Block::getBlockScore() const {
    int blockScore = 0;
    for (const auto& task : this->blockTasks) {
        blockScore += task->getTaskScore();
    }
    return blockScore;
}

QStringList Block::findColumnsInTableByKeyword(const QSqlDatabase& db,
                                                   const QString& tableName,
                                                   const QString& keyWord) {
    QSqlQuery metaQuery(db);
    metaQuery.prepare(QString("PRAGMA table_info(%1)").arg(tableName));
    metaQuery.exec();
    QStringList columnsFound;
    while (metaQuery.next()) {
        QString columnName = metaQuery.value("name").toString();
        if (columnName.contains(keyWord, Qt::CaseInsensitive)) {
            columnsFound.append(columnName);
        }
    }
    return columnsFound;
}

Task* Block::generateTask(const QSqlDatabase& db, const QString& taskName,
                          QWidget *taskIntroWidget, const QString& taskTableName) {
    QSqlQuery data_query(db);
    data_query.prepare(QString("SELECT * FROM %1").arg(taskTableName));
    data_query.exec();
    QVector<Question*> task_questions;
    while (data_query.next()) {
        int question_id = data_query.value("question_id").toInt();
        int question_number = data_query.value("question_number").toInt();
        auto question_type = static_cast<QuestionType>(data_query.value("question_type").toInt());
        QString question_text = data_query.value("question_text").toString();
        int question_value = data_query.value("question_value").toInt();
        QLabel *questionLabel = new QLabel(QString::number(question_number) + ") " +
                                           question_text);
        questionLabel->setWordWrap(true);
        questionLabel->setStyleSheet(Styles::labelStyle);
        switch (question_type) {
        case QuestionType::TrueFalseQuestion: {
            bool correct_answer = data_query.value("correct_answer").toBool();
            TrueFalseQuestion *new_question = new TrueFalseQuestion(questionLabel, question_id,
                                                                    correct_answer, question_value);
            task_questions.append(new_question);
            break;
        }
        case QuestionType::OpenQuestion: {
            QString correct_answer = data_query.value("correct_answer").toString();
            OpenQuestion *new_question = new OpenQuestion(questionLabel, question_id,
                                                          correct_answer, question_value);
            task_questions.append(new_question);
            break;
        }
        case QuestionType::OptionQuestion: {
            int correct_answer_index = data_query.value("correct_answer_index").toInt();
            QVector<QString> options_columns = findColumnsInTableByKeyword(db, taskTableName, "option");
            QStringList options;
            for (const QString& option_column : std::as_const(options_columns)) {
                QString option = data_query.value(option_column).toString();
                options.append(option);
            }
            OptionQuestion *new_question = new OptionQuestion(questionLabel, question_id, options,
                                                              correct_answer_index, question_value);
            task_questions.append(new_question);
            break;
        }
        case QuestionType::MultiOptionQuestion: {}
        }
    }
    Task *new_task = new Task(taskIntroWidget, taskName, task_questions);
    return new_task;
}

QVector<Task*> Block::generateBlockTasks(const QSqlDatabase& db) {
    QVector<Task*> blockTasks;
    QSqlQuery tasksQuery(db);
    tasksQuery.prepare(QString("SELECT task_name, task_table_name, task_intro FROM %1").arg("tasks"));
    tasksQuery.exec();
    while (tasksQuery.next()) {
        QString taskName = tasksQuery.value("task_name").toString();
        QString taskTableName = tasksQuery.value("task_table_name").toString();
        QString taskIntro = tasksQuery.value("task_intro").toString();
        StyledLabel *introLabel = new StyledLabel(taskIntro);
        Task *newTask = generateTask(db, taskName, introLabel, taskTableName);
        blockTasks.append(newTask);
    }
    return blockTasks;
}

QString Block::getMainBlockTableName(const QSqlDatabase& db) {
    QSqlQuery query("SELECT name FROM sqlite_master "
                    "WHERE type = 'table' AND name LIKE '%block%' "
                    "LIMIT 1", db);
    query.exec();
    query.next();
    QString mainTableName = query.value(0).toString();
    return mainTableName;
}

MainBlockInfo Block::getMainBlockInfo(const QSqlDatabase& db) {
    QString mainTableName = getMainBlockTableName(db);

    QSqlQuery dataQuery(db);
    dataQuery.prepare(QString("SELECT block_name, block_intro, image_path, block_help "
                              "FROM %1 LIMIT 1").arg(mainTableName));
    dataQuery.exec();
    dataQuery.next();
    QString block_header = dataQuery.value("block_name").toString();
    QString block_intro = dataQuery.value("block_intro").toString();
    QString block_image_path = QString(PROJECT_PATH) + dataQuery.value("image_path").toString();
    QString block_help = dataQuery.value("block_help").toString();
    MainBlockInfo block_info = {block_header, block_intro, block_image_path, block_help};
    return block_info;
}

void Block::setMainBlockWidget(QWidget *newMainBlockWidget) {
    QWidget* parent = qobject_cast<QWidget*>(mainBlockWidget->parent());
    QVBoxLayout* vbox = qobject_cast<QVBoxLayout*>(parent->layout());
    int index = vbox->indexOf(mainBlockWidget);
    vbox->removeWidget(mainBlockWidget);
    delete mainBlockWidget;

    mainBlockWidget = newMainBlockWidget;
    mainBlockWidget->setParent(parent);

    vbox->insertWidget(index, mainBlockWidget);
    vbox->update();
}

Block::~Block() {
    qDeleteAll(blockTasks);
    blockTasks.clear();

    QString connectionName = db.connectionName();
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connectionName);
}
