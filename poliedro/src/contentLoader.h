//
//  contentLoader.h
//  poliedro
//
//  Created by ojack on 11/21/16.
//
//

#ifndef __poliedro__contentLoader__
#define __poliedro__contentLoader__

#include "ofMain.h" #include "ofxThreadedImageLoader.h"

class contentLoader {
    
    public:
    
    void setup(int _width, int _height);
    void update();
    void draw();
    
    void loadImages(string path, vector<ofImage> *images);
    
    vector<ofImage> goodImages;
    vector<ofImage> badImages;
    vector<ofImage> textImages;
    
    int imageIndex;
    int width;
    int height;
    
    ofImage * image0;
    ofImage * image1;
    ofImage * image2;
};

#endif /* defined(__poliedro__contentLoader__) */
