#ifndef LISTENINGBLOCK_H
#define LISTENINGBLOCK_H
#include "Block.h"
#include "AudioPlayerWidget.h"
#include "Complexity.h"

class ListeningBlock: public Block {
    Q_OBJECT
public:
    explicit ListeningBlock(const QString& blockDataBasePath,
                            const Complexity& complexity,
                            QWidget* parent = nullptr);
};

#endif // LISTENINGBLOCK_H
