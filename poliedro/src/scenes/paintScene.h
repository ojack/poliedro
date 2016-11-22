#pragma once

#include "ofMain.h"
#include "baseScene.h"

class paintScene : public baseScene{
    
public:
    
    void setup();
    void update();
    void draw();
    
    ofShader shader;
    ofFbo maskFbo;
    
};