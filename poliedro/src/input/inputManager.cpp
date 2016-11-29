

#include "inputManager.h"

//---------------------------------------------------------------
void inputManager::setup(){
    bIsFrameNew = false;
    
    group.setName("settings");
    group.add(threshold.set("threshold", 100, 0, 255));
    group.add(speed.set("speed", 1, 0,2));
    group.add(minArea.set("minArea", 1000, 0, 10000));
    group.add(medianFilterAmount.set("medianFilterAmount", 5, 0, 30));
    group.add(bMirror.set("mirror", true));
    
    
   // panel.setup();
   panel->add(group);
    
#ifdef USE_VIDEO
    player.load("videos/atwood.mov");
    player.play();
    player.setLoopState(OF_LOOP_NORMAL);
    
    graypixels = new unsigned char[512*424];
    medianFiltered = new unsigned char[512*424];
    medianFilteredResult.allocate(512, 424, OF_IMAGE_GRAYSCALE);
#else
   /* ofxKinectV2 tmp;
    vector <ofxKinectV2::KinectDeviceInfo> deviceList = tmp.getDeviceList();
    kinect = shared_ptr <ofxKinectV2> (new ofxKinectV2());
    kinect->open(deviceList[0].serial);
    panel.add(kinect->params);*/
    
    kinect.init();
    kinect.open();
    kinect.setRegistration(false);
    
    graypixels = new unsigned char[kinect.width*kinect.height];
    medianFiltered = new unsigned char[kinect.width*kinect.height];
    medianFilteredResult.allocate(kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);
#endif
    
    
    
   
    
    
    
}

void inputManager::changeMovie( string fileName){
#ifdef USE_VIDEO
    player.stop();
    player.load(fileName);
    player.play();
    player.setLoopState(OF_LOOP_NORMAL);
#endif
}


//---------------------------------------------------------------
void inputManager::update(){
    
    //cout << player.getWidth() << " " << player.getHeight() << endl;
#ifdef USE_VIDEO
    player.update();
    player.setVolume(0);
    player.setSpeed(speed);
    
    
    if (player.isFrameNew() == true){
        bIsFrameNew = true;
        
        unsigned char * data  = player.getPixels().getData();
        for (int i = 0; i < 512*424; i++){
            graypixels[i] = data[i*3];
        }
        
        
        ctmf(graypixels, medianFiltered,
             512, 424, 512, 512,medianFilterAmount, 1);
        
        medianFilteredResult.setFromPixels(medianFiltered, 512, 424, OF_IMAGE_GRAYSCALE);
        
       /* finder.setSortBySize(true);
        finder.setThreshold(threshold);
        finder.setMinArea(minArea);
        finder.findContours(medianFilteredResult);*/
    } else {
        bIsFrameNew = false;
    }
#else
   /* kinect->update();
    if( kinect->isFrameNew() ){
        texDepth.loadData( kinect->getDepthPixels() );
        //texRGB.loadData( kinect->getRgbPixels() );
        
        unsigned char * data  = kinect->getDepthPixels().getData();
        
        
        // todo is this OK ???
        for (int i = 0; i < 512*424; i++){
            graypixels[i] = data[i];
        }
        
        // todo move this to kinect.
        ctmf(graypixels, medianFiltered,
             512, 424, 512, 512,medianFilterAmount, 1);
        
        medianFilteredResult.setFromPixels(medianFiltered, 512, 424, OF_IMAGE_GRAYSCALE);
        
        finder.setSortBySize(true);
        finder.setThreshold(threshold);
        
        finder.findContours(medianFilteredResult);
        
    }*/
    kinect.update();
    if(kinect.isFrameNew()) {
        bIsFrameNew = true;
        texDepth.loadData( kinect.getDepthPixels() );
        unsigned char * data  = kinect.getDepthPixels().getData();
        
        
        // todo is this OK ???
        for (int i = 0; i < kinect.width*kinect.height; i++){
            graypixels[i] = data[i];
        }
        
        
        ctmf(graypixels, medianFiltered,
             kinect.width, kinect.height, kinect.width, kinect.width,medianFilterAmount, 1);
        
        medianFilteredResult.setFromPixels(medianFiltered, kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);
        
     /*   finder.setSortBySize(true);
        finder.setThreshold(threshold);
        finder.setMinArea(minArea);
        finder.findContours(medianFilteredResult);*/
    } else {
        bIsFrameNew = false;
    }
#endif
    
    if(bMirror){
        medianFilteredResult.mirror(false, true);
    }
}

void inputManager::setAngle(int angle){
    #ifndef USE_VIDEO
   
    kinect.setCameraTiltAngle(angle);
    
    #endif

}

void inputManager::getContours(){
    finder.setSortBySize(true);
    finder.setThreshold(threshold);
    finder.setMinArea(minArea);
    finder.findContours(medianFilteredResult);
}
//---------------------------------------------------------------
void inputManager::draw(){
    
#ifdef USE_VIDEO
    player.draw(0,0);
    medianFilteredResult.draw(512,0);
    if (finder.size() > 0){
        ofPushMatrix();
        ofTranslate(0,424);
        finder.getPolyline(0).draw();
        
        ofPopMatrix();
        
    }
    //finder.draw();
#else
    //kinect.draw(0, 0);
   texDepth.draw(0,0);
    medianFilteredResult.draw(512,0);
    if (finder.size() > 0){
        ofPushMatrix();
        ofTranslate(0,424);
        finder.getPolyline(0).draw();
        ofPopMatrix();
        
    }
#endif
    
    
    
}