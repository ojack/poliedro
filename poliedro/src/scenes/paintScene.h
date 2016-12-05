#pragma once

#include "ofMain.h"
#include "baseSubtractScene.h"

class paintScene : public baseSubtractScene{
    
public:
    
    void setup();
    void update();
    void draw();
    
    ofShader shader;
    ofFbo maskFbo;
    
};