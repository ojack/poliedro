#pragma once

#include "ofMain.h"
#include "baseContourScene.h"

class paintScene : public baseContourScene{
    
public:
    
    void setup();
    void update();
    void draw();
    
    ofShader shader;
    ofFbo maskFbo;
    
};