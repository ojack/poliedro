#pragma once

#include "ofMain.h"
#include "baseScene.h"

class trailsScene : public baseScene{
    
public:
    
    void setup();
    void update();
    void draw();
    
    ofShader shader;
    ofFbo maskFbo;
    ofFbo contourFbo;
    ofPolyline  trails [2][100];
};