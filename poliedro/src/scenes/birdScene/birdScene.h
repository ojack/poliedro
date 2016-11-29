#pragma once

#include "ofMain.h"
#include "baseContourScene.h"

class birdScene : public baseContourScene{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void loadImages(string path, vector<ofImage> *images);
    
    ofShader shader;
    ofFbo maskFbo;
    
    vector<ofImage> images;
};