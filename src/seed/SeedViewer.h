#ifndef SEEDVIEWER_H
#define SEEDVIEWER_H

#include "AbstractSeedSetter.h"

class SeedViewer : public AbstractSeedSetter {
public:
    explicit SeedViewer(DataHolder *dataHolder);
    string getCurrentWord() const;
};

#endif //SEEDVIEWER_H
