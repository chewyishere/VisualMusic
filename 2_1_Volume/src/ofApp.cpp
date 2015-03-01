#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableAlphaBlending();
	ofBackground(0);
	

	
	soundStream.listDevices();
	
	//if you want to set a different device id
	//soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	int bufferSize = 256;
	
	volHistory.assign(400, 0.0);
    
    left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);
    
	bufferCounter	= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    drawCounter		= 0;
	
    soundStream.setup(this, 0, 2, 44100, bufferSize, 2);
    //soundStream.setup(app, OutputChannels,InputChannels, sampleRate, bufferSize, nBuffers);
    
    // 0 output channels,
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 2 num buffers (latency)


}

//--------------------------------------------------------------
void ofApp::update(){
    
    //lets scale the vol up to a 0-1 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
	//Record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger then the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
    


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(ofGetWindowSize()/2);
    
    ofSetColor(100,100,200);
    ofFill();
    ofSetRectMode(OF_RECTMODE_CENTER); //set rectangle mode to the center
    ofRect(0,0, scaledVol * 2000.0f, scaledVol * 2000.0f);
    
    ofTranslate(-200,-200);
    
    //volume history graph
    ofBeginShape();
    
    for (unsigned int i = 0; i < volHistory.size(); i++){
        if( i == 0 ) ofVertex(i, 400);
        
        ofVertex(i, 400-volHistory[i] * 150); //height is upside down
        
        if( i == volHistory.size() -1 ) ofVertex(i, 400);
        
    }
    ofEndShape(false);
    ofPopMatrix();
    
    ofPopStyle();
    
    drawCounter++;
    
    ofSetColor(0);
	string reportString = "Audio Volume (0-100): " + ofToString(scaledVol*100.0,0) +
    "\nbuffers received: "+ofToString(bufferCounter)+
    "\nticks: " + ofToString(soundStream.getTickCount());
    
	ofDrawBitmapString(reportString, 50, 550);

}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
    
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
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
