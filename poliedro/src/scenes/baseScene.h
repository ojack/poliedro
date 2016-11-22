#pragma once

#include "ofMain.h"
#include "contourTracker.h"


class baseScene {
    
public:
    
    virtual void setup(){};
    virtual void update(){};
    virtual void draw(){};
    
    
   // contourTracker * CT;
    vector<contourTracker> * CTVector;
    ofImage * image0;
    ofImage * image1;
    ofImage * image2;
    int width;
    int height;
    ofFbo * motionFbo;
   
    
};