#pragma once

#include "ofMain.h"
#include "baseContourScene.h"

class trailsScene : public baseContourScene{
    
public:
    
    void setup();
    void update();
    void draw();
    
    ofShader shader;
    ofFbo maskFbo;
    ofFbo contourFbo;
    ofPolyline  trails [2][100];
};