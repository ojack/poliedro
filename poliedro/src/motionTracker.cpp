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
    motionFbo.begin();
    ofClear(0,0,0,0);
    motionFbo.end();
    
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
}

void motionTracker::clear(){
    motionFbo.begin();
    ofClear(0,0,0,0);
    motionFbo.end();
}

//---------------------------------------------------------------
void motionTracker::draw(){
   
    motionFbo.draw(0, 0);

    
}