
#include "backgroundSubtract.h"

//---------------------------------------------------------------



void backgroundSubtract::setup(int width, int height){
    //todo: scale to kinect? less channels?
    motionFbo.allocate(ofGetWidth(), ofGetHeight());
   
    
    motionFbo.begin();
    ofClear(0,0,0,0);
    motionFbo.end();
    
    params.add(resetBackground.set("Reset Background", false));
    params.add(learningTime.set("Learning Time", 3, 0, 30));
    params.add(thresholdValue.set("Threshold Value", 100, 0, 255));
    params.add(eraseAmount.set("eraseAmount", 10, 0, 100));
    panel->add(params);
    
}

void backgroundSubtract::update(){
    if(resetBackground){
        clear();
    }
    
    background.setLearningTime(learningTime);
    background.setThresholdValue(thresholdValue);
    background.update(*medianFilteredResult, motionImage);
    motionImage.update();

    motionFbo.begin();
    ofSetColor(255, 255, 255, eraseAmount);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    if(motionImage.isAllocated()) {
        motionImage.draw(0, 0, motionFbo.getWidth(), motionFbo.getHeight());
    }
    motionFbo.end();

    motionFbo.end();
    
}

void backgroundSubtract::clear(){
    background.reset();
    motionFbo.begin();
    ofClear(0,0,0,0);
    motionFbo.end();
    resetBackground = false;
}

//---------------------------------------------------------------
void backgroundSubtract::draw(){
    
    motionFbo.draw(200, 0);
    
}