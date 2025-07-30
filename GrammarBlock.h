#ifndef GRAMMARBLOCK_H
#define GRAMMARBLOCK_H

#include "Block.h"
#include "AudioPlayerWidget.h"
#include "Complexity.h"

class GrammarBlock: public Block {
    Q_OBJECT
public:
    explicit GrammarBlock(const QString& blockDataBasePath,
                          const Complexity& complexity,
                          QWidget* parent = nullptr);
};

#endif // GRAMMARBLOCK_H
