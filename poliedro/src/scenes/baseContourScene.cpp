//
//  baseContourScene.cpp
//  poliedro
//
//  Created by ojack on 11/24/16.
//
//

#include "baseContourScene.h"

void baseContourScene::setupContour(int numContours){
    ofLog()<< "setting up contour";
    // share a pointer to the CT object
    motion.CTVector = &CTVector;
    motion.panel = IM->panel;
    motion.setup(width, height);
  
    for (int i = 0; i < numContours; i++){
        CTVector.push_back(contourTracker());
    }
}

void baseContourScene::processContour(){
    IM->getContours();
    ofLog()<< "called processing contour";
    ofRectangle input(0,0,IM->medianFilteredResult.getWidth(), IM->medianFilteredResult.getHeight());
    ofRectangle output(0,0, ofGetWidth(), ofGetHeight());
    
    ofRectangle inputScaled = input;
    inputScaled.scaleTo(output);

    for(int j = 0; j < CTVector.size(); j++){
        if (IM->finder.size() > j){
            ofPolyline tempLine = IM->finder.getPolyline(j);
            /*scale kinect input to size of output*/
            for (int i = 0; i < tempLine.size(); i++){
                float x = tempLine[i].x;
                float y = tempLine[i].y;
                float newX = ofMap(x, input.x, input.x + input.width,
                                   inputScaled.x, inputScaled.x + inputScaled.width);
                float newY = ofMap(y, input.y, input.y + input.height,
                                   inputScaled.y, inputScaled.y + inputScaled.height);
                tempLine[i].set(newX, newY);
                
            }
            CTVector.at(j).analyze(tempLine);
        } else {
            CTVector.at(j).reset();
        }
    }
    motion.update();

}