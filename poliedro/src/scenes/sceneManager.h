#pragma once

#include "ofMain.h"
#include "baseScene.h"


class sceneManager {
    
public:
    
    void setup();
    void update();
    void draw();
    void nextScene();
    void clear();
    void randomScene();
    
    vector < baseScene * > scenes;
    int currentScene;
    
};
