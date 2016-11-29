#pragma once

#include "ofMain.h"
#include "contourTracker.h"
#include "inputManager.h"
#include "ofxGui.h"

class baseScene {
    
public:
    
    virtual void setup(){};
    virtual void update(){};
    virtual void draw(){};
    
    void loadImages(string path, vector<ofImage> *images);
  
   // contourTracker * CT;
   // vector<contourTracker> * CTVector;
    
    ofImage * image0;
    ofImage * image1;
    ofImage * image2;
    int width;
    int height;
    //ofFbo * motionFbo;
    inputManager * IM;
    ofxPanel * panel;
    
};