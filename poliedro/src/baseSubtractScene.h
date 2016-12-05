#pragma once
#include "baseScene.h"
#include "backgroundSubtract.h"


class baseSubtractScene : public baseScene{
public:
   
    void clear();
    void setupBackground();
    void processBackground();
    backgroundSubtract motion;
};