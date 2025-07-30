#ifndef READINGBLOCK_H
#define READINGBLOCK_H

#include "Block.h"
#include "AudioPlayerWidget.h"
#include "Complexity.h"

class ReadingBlock: public Block {
    Q_OBJECT
public:
    explicit ReadingBlock(const QString& blockDataBasePath,
                          const Complexity& complexity,
                          QWidget* parent = nullptr);
};

#endif // READINGBLOCK_H
