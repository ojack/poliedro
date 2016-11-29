#include "baseScene.h"

void baseScene::loadImages(string path, vector<ofImage> *images){
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

