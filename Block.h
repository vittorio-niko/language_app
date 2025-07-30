#ifndef BLOCK_H
#define BLOCK_H
#include <QString>
#include <QToolButton>
#include <QLabel>
#include <QScrollArea>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSize>
#include <QDebug>
#include <QScrollArea>
#include <QPixmap>

#include "QuestionType.h"
#include "TrueFalseQuestion.h"
#include "OpenQuestion.h"
#include "OptionQuestion.h"
#include "AudioPlayerWidget.h"
#include "HelpButton.h"
#include "BlockType.h"
#include "Task.h"
#include "HelpButton.h"
#include "MainBlockInfo.h"
#include "Complexity.h"
#include "StyledLabel.h"
#include "ImageLabel.h"

class Block: public QWidget {
    Q_OBJECT
public:
    explicit Block(const QString& blockDataBasePath, QWidget* parent = nullptr);
    const QString& getBlockName() const;
    int getBlockValue() const;
    int getBlockScore() const;

    void setMainBlockWidget(QWidget *newMainBlockWidget);
    static MainBlockInfo getMainBlockInfo(const QSqlDatabase& db);
    static QString getMainBlockTableName(const QSqlDatabase& db);

    ~Block();
private:
    static QStringList findColumnsInTableByKeyword(const QSqlDatabase& db,
                                                   const QString& tableName,
                                                   const QString& keyWord);
    static Task* generateTask(const QSqlDatabase& db, const QString& taskName,
                              QWidget *taskIntroWidget, const QString& taskTableName);
    static QVector<Task*> generateBlockTasks(const QSqlDatabase& db);

protected:
    QSqlDatabase db;
    MainBlockInfo blockInfo;
    QLabel *blockHeader;
    StyledLabel *introLabel;
    QWidget *mainBlockWidget;
    HelpButton *helpButton;
    int blockValue;
    QVector<Task*> blockTasks;
};

#endif // BLOCK_H
