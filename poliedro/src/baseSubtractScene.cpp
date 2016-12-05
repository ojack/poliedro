//
//  baseSubtractScene.cpp
//  poliedro
//
//  Created by ojack on 12/5/16.
//
//

#include "baseSubtractScene.h"



void baseSubtractScene::setupBackground(){
    motion.medianFilteredResult = &IM->medianFilteredResult;
    motion.panel = panel;
    motion.setup(width, height);
}

void baseSubtractScene::processBackground(){
    motion.update();
}

void baseSubtractScene::clear(){
    motion.clear();
}
