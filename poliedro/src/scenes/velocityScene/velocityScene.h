#pragma once

#include "ofMain.h"
#include "baseScene.h"

class velocityScene : public baseScene{
    
public:
    
    void setup();
    void update();
    void draw();
    
    
    vector<ofPolyline> prevFrame;
    ofPoint velocities[100];
    ofPoint velocitiesSmoothed[100];
    ofFbo motionFbo;
};