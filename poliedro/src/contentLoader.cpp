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
    
    imageIndex = 0;
    
    image0 = &badImages.at(imageIndex);
    image1 = &goodImages.at(imageIndex);
    
}

void contentLoader::update(){
    
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

void contentLoader::draw(){
    
}