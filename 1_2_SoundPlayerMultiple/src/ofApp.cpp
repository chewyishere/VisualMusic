#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate (60); // speed drawing frame
    ofSetBackgroundAuto (false); // turn off background erase
    ofBackground (0);
    
    guitar.loadSound("guitar.wav");
    guitar.setVolume(0.75f);
    guitar.setMultiPlay(false);
    
    synth.loadSound("synth.wav");
    synth.setVolume(0.5f);
    synth.setMultiPlay(true);
    
    beat.loadSound("beat.wav");
    beat.setVolume(0.75f);
    beat.setMultiPlay(false);
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();

}

//--------------------------------------------------------------
void ofApp::draw(){
   
    ofEnableAlphaBlending();
   
    float n = 0; //noise
    
    n += ofMap(ofNoise(p.x,p.y, ofGetFrameNum()*0.01), 0 , 1, -3,3);

    if (guitar.getIsPlaying ()) {// Blue color
        ofSetColor (ofRandom (10, 200),ofRandom (10, 200), ofRandom(150, 250), 20);
        ofCircle (p.x+n*5, p.y+n*5, rad*n);
    }
   
    if (synth.getIsPlaying ()) {// Red color
        ofSetColor (ofRandom (150, 250), ofRandom (10, 200),ofRandom (10, 200),20);
        ofCircle (p.x+n*5, p.y+n*5, rad*n);
    }

    
    if (beat.getIsPlaying ()) {// Green color
        ofSetColor (ofRandom (10, 200),ofRandom (150, 250), ofRandom (10, 200), 20);
        ofCircle (p.x+n*5, p.y+n*5, rad*n);
    }

    ofDisableAlphaBlending ();
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if ( key == '1' ) {
        guitar.play();
    }
    if ( key == '2' ) {
        synth.play();
    }
    if ( key == '3' ) {
        beat.play();
    }


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    float h = ofGetWindowHeight(); // screen height
    float w = ofGetWindowWidth(); // screen height

    float speed = ofMap(mouseY,0,h,5,0);
    
    guitar.setSpeed(speed); // Set the playback speed
    guitar.setPan(ofMap(x, 0, w, -1, 1, true));
    
    beat.setSpeed(speed); // Set the playback speed
    beat.setPan(ofMap(x, 0, w, -1, 1, true));
    
    synth.setSpeed(speed); // Set the playback speed
    synth.setPan(ofMap(x, 0, w, -1, 1, true));
    
    // Remember the point and the radius of the circle to draw
    p = ofPoint (x, y);
    rad = (5 - speed);
    rad = 10 * rad;
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
//-------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
