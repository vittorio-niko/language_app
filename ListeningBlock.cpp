#include "ListeningBlock.h"

ListeningBlock::ListeningBlock(const QString& blockDataBasePath,
                               const Complexity& complexity,
                               QWidget* parent):
    Block(blockDataBasePath, parent) {
    QString mainTableName = getMainBlockTableName(db);
    QSqlQuery audioQuery(db);
    audioQuery.prepare(QString("SELECT audio_path FROM %1").arg(mainTableName));
    audioQuery.exec();
    audioQuery.next();
    QString audioPath = QString(PROJECT_PATH) + audioQuery.value("audio_path").toString();
    AudioPlayerWidget *player = new AudioPlayerWidget(audioPath);
    player->enablePause(false);
    player->enableSeeking(false);
    player->setStyleSheet(Styles::playerStyle);
    player->setLabelsStyle(Styles::labelStyle);
    if (complexity == Complexity::Easy) {
        player->setPlayLimit(2);
    } else if (complexity == Complexity::Hard) {
        player->setPlayLimit(1);
        if (helpButton) {
            helpButton->hide();
        }
    }
    setMainBlockWidget(player);
}
