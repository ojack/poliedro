#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ctmf.h"
#include "ofxGui.h"
//#include "ofxKinectV2.h"
#include "ofxKinect.h"

using namespace milton;

#define USE_VIDEO

class inputManager {
    
public:
    
    void setup(int minDist, int maxDist);
    void update();
    void draw();
    
    void changeMovie( string fileName);
    void setAngle(int angle);
    void getContours();
    
#ifdef USE_VIDEO
    ofVideoPlayer player;
#else
  /*  shared_ptr<ofxKinectV2>  kinect;
    ofTexture texDepth;
    ofTexture texRGB;*/
    
    ofTexture texDepth;
    
    ofxKinect kinect;
#endif
    
    
    
    // I basically have a contour that represents the blob on this frame.
    
    bool bFoundABlobThisFrame;
    unsigned char * thresholdedImage;
    
    unsigned char * graypixels;
    unsigned char * medianFiltered;
    
    ofImage medianFilteredResult;
    
    ofxCv::ContourFinder finder;
    
    ofParameterGroup group;
    ofParameter < int > threshold;
     ofParameter < int > farThreshold;
    ofParameter < int > nearThreshold;
    ofParameter < int > medianFilterAmount;
    ofParameter < float > minArea;
    ofParameter < float > speed;
    ofParameter < bool > bMirror;
    ofxPanel * panel;
        
   
    bool bIsFrameNew;
};