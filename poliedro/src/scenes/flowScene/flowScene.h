#pragma once

#include "ofMain.h"
#include "baseFlowScene.h"

class flowScene : public baseFlowScene{
    
public:
    
    void setup();
    void update();
    void draw();
    void clear();
    
    vector<ofImage> images;
    ofShader shader;
    ofFbo maskFbo;
    ofFbo renderFbo;
    ofFbo srcFbo;
};