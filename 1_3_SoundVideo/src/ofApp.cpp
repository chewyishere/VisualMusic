#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate (60); // speed drawing frame
    ofSetBackgroundAuto (false); // turn off background erase
    
    sound.loadSound("withthesun.mp3");
    sound.setVolume(0.75f);
    sound.setMultiPlay(false);
    sound.play();
    sound.setLoop(true);
    sound.setSpeed(1.0);
    sound.setPosition(0.0);
    
    
   // video1.loadMovie( "fisheye.mov" );
    video.loadMovie( "video1.mov" );
    video.setLoopState(OF_LOOP_NORMAL);
    video.play();
    video.setSpeed(0.4);
    video.setPosition(0.0);


}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    ofSoundUpdate();

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    video.draw(0,0);
    
    ofEnableAlphaBlending();
    
    ofDrawBitmapString("frame: " + ofToString(video.getCurrentFrame()) + "/"+ofToString(video.getTotalNumFrames()),20,380);
    ofDrawBitmapString("duration: " + ofToString(video.getPosition()*video.getDuration(),2) + "/"+ofToString(video.getDuration(),2),20,400);
    ofDrawBitmapString("speed: " + ofToString(video.getSpeed(),2),20,420);
    
    ofDisableAlphaBlending ();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    float h = ofGetHeight(); // screen height
    float w = ofGetWidth(); // screen height
    float pct = (float)x / (float)w; //percentage of w
    
    
    float musicSpeed = ofMap(mouseX,0,w,-3,3);
    
    sound.setPosition(pct); // play the pct
    video.setPosition(pct); // play the pct
    
    //float videoSpeed = ofMap(mouseX,0,w,-10,10);
    float videoSpeed = (2*pct -1)*5.0f; //smoothed val
    
    //sound.setSpeed(musicSpeed); // Set the playback speed;
    //video.setSpeed(videoSpeed);


}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
