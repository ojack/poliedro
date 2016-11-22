#pragma once

#include "ofMain.h"
#include "baseScene.h"

class greenScene : public baseScene{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void loadImages(string path, vector<ofImage> *images);
    
    ofShader shader;
    ofFbo maskFbo;
    
    vector<ofImage> images;
};