//
//  motionTracker.cpp
//  poliedro
//
//  Created by ojack on 11/21/16.
//
//

#include "motionTracker.h"

//---------------------------------------------------------------



void motionTracker::setup(int width, int height){
    //todo: scale to kinect? less channels?
    motionFbo.allocate(ofGetWidth(), ofGetHeight());
    pixelFbo.allocate(100, 60, GL_RGB);
    
    motionFbo.begin();
    ofClear(0,0,0,0);
    motionFbo.end();
    
    pixelFbo.begin();
    ofClear(0,0,0,255);
    pixelFbo.end();
    
    params.setName("motion tracking");
    params.add(op.set("op", 255, 0, 255));
    params.add(cutoff.set("cutoff", 0.3, 0, 1));
    params.add(radius.set("radius", 30, 0, 200));

    panel->add(params);
    
}

void motionTracker::update(){
    motionFbo.begin();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(255, 255, 255, op);
    for(int j = 0; j < CTVector->size(); j++){
        contourTracker * CT = &CTVector->at(j);
        if(CT->prevSmoothed.size() == 100){
            for (int i = 0; i < CT->resampleSmoothed.size(); i++){
                ofVec3f vel = CT->resampleSmoothed[i] - CT->prevSmoothed[i];
                //float velSmoothed =
                // printf(...)                  // run dmc
                //cout << velocities[i].length() << endl;  // asap
                
                float scale = ofMap(vel.length(), 0, radius, 1, 30, true);
                if(vel.length() > cutoff*radius){
                    ofDrawCircle(CT->resampleSmoothed[i], scale);
                }
                //ofLine(CT->resampleSmoothed[i],
                //       CT->resampleSmoothed[i] + velocities[i] * 4);
            }
        }
        
    }
    
    motionFbo.end();
    
    pixelFbo.begin();
    ofClear(0, 0, 0, 255);
    ofSetColor(255, 255, 255, 255);
    motionFbo.draw(0, 0, pixelFbo.getWidth(), pixelFbo.getHeight());
    pixelFbo.end();
    
    ofPixels pix;
    pixelFbo.readToPixels(pix, 0);

    float total = 0;
    
    ofPixels rpix = pix.getChannel(0);
    float maxC = 0.0;
    float minC = 0.0;
    for(int i = 0; i < rpix.size(); i++){
        char c = rpix[i];
        if(c > 0){
            total ++;
        }
        
        if(c > maxC) maxC = c;
    }
    float percent = (total)/rpix.size();
    ofLog() << "total " << total << "size " << rpix.size() << "percent " << percent << " max " <<maxC;
}

void motionTracker::clear(){
    motionFbo.begin();
    ofClear(0,0,0,0);
    motionFbo.end();
}

//---------------------------------------------------------------
void motionTracker::draw(){
   
    motionFbo.draw(200, 0);

    pixelFbo.draw(600, 300, 600, 400);
}