#include "SeedViewer.h"

SeedViewer::SeedViewer(DataHolder *dataHolder) : AbstractSeedSetter(dataHolder) {}

string SeedViewer::getCurrentWord() const {
    return mnemonic.getWordAt(currentIndex);
}
