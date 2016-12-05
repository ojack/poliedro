//
//  contentLoader.cpp
//  poliedro
//
//  Created by ojack on 11/21/16.
//
//

#include "contentLoader.h"

void contentLoader::setup(int _width, int _height){
    width = _width;
    height = _height;
    loadImages("content/good", &goodImages);
    loadImages("content/bad", &badImages);
   loadImages("content/background", &backgroundImages);
    
    imageIndex = 0;
    
    image0 = &badImages.at(imageIndex);
    image1 = &goodImages.at(imageIndex);
 //   image2 = &textImages.at(imageIndex);
    
    goodFbo.allocate(ofGetWidth(), ofGetHeight());
    badFbo.allocate(ofGetWidth(), ofGetHeight());
    
   goodFbo.begin();
    ofClear(0,0,0,0);
    goodFbo.end();
    
    badFbo.begin();
    ofClear(0,0,0,0);
    badFbo.end();
    updateIndex();
}

void contentLoader::updateIndex(){
    imageIndex++;
    if(imageIndex >= goodImages.size()) imageIndex = 0;
    
    goodFbo.begin();
    goodImages.at(imageIndex).draw(0, 0, goodFbo.getWidth(), goodFbo.getHeight());
    goodFbo.end();
    
    badFbo.begin();
    badImages.at(imageIndex).draw(0, 0, badFbo.getWidth(), badFbo.getHeight());
    badFbo.end();
}

void contentLoader::loadImages(string path, vector<ofImage> *images){
    ofDirectory dir;
    
    dir.listDir(path);
    dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    ofLogNotice() << "loading directory " << path << " size: " << dir.size();
    //allocate the vector to have as many ofImages as files
    if( dir.size() ){
        images->assign(dir.size(), ofImage());
        
    }
    
    // you can now iterate through the files and load them into the ofImage vector
    for(int i = 0; i < (int)dir.size(); i++){
        ofLogNotice() << "loading" << dir.getPath(i);
        (*images)[i].load(dir.getPath(i));
        (*images)[i].resize(width, height);
    }
    
    
}


    
