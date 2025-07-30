#include "GrammarBlock.h"

GrammarBlock::GrammarBlock(const QString& blockDataBasePath,
                           const Complexity& complexity,
                           QWidget* parent):
    Block(blockDataBasePath, parent) {
    if (complexity == Complexity::Hard) {
        if (helpButton) {
            helpButton->hide();
        }
    }
}
