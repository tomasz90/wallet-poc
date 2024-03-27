#include "SeedViewer.h"

SeedViewer::SeedViewer() : AbstractSeedSetter() {}

string SeedViewer::getCurrentWord() const {
    return tempMnemonic.getWordAt(currentIndex);
}
