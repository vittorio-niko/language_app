#include "ReadingBlock.h"

ReadingBlock::ReadingBlock(const QString& blockDataBasePath,
                           const Complexity& complexity,
                           QWidget* parent):
    Block(blockDataBasePath, parent) {
    QString mainTableName = getMainBlockTableName(db);
    QSqlQuery textQuery(db);
    textQuery.prepare(QString("SELECT text FROM %1").arg(mainTableName));
    textQuery.exec();
    textQuery.next();
    QString text = textQuery.value("text").toString();
    StyledLabel *textLabel = new StyledLabel(text);
    if (complexity == Complexity::Hard) {
        if (helpButton) {
            helpButton->hide();
        }
    }
    setMainBlockWidget(textLabel);
}
