#include "testApp.h"

void testApp::setup(){
    SoundHeight = 200;
    //Set up sound sample
    soundStream.listDevices();
	
	//if you want to set a different device id
	//soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	int bufferSize = 256;
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
	// Set canvas
	ofBackgroundHex(0x000000);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	glEnable(GL_DEPTH_TEST);
	cam.setDistance(400);
	
	// get videos
	myVideo.initGrabber(640, 480); // change this to kinect
	
	// initial verts
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			myVerts[j * WIDTH + i].set(i - WIDTH/2, j - HEIGHT/2, 0);
			myColor[j * WIDTH + i].set(1.0, 1.0, 1.0, 1.0);
		}
	}
	
	// initial vert's colors
	myVbo.setVertexData(myVerts, NUM_PARTICLES, GL_DYNAMIC_DRAW);
	myVbo.setColorData(myColor, NUM_PARTICLES, GL_DYNAMIC_DRAW);
}

void testApp::update(){
    
    //lets scale the vol up to a 0-1 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
	//lets record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}


	// update camera
	myVideo.update();
	
	// once camera is updated
	if (myVideo.isFrameNew()) {
		
		// get pixels
		unsigned char * pixels = myVideo.getPixels();
		
		// pixel process
        
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				
				// r g b value
				float r = (float)pixels[j * myVideo.width * 3 + i * 3] / 256.0;
				float g = (float)pixels[j * myVideo.width * 3 + i * 3 + 1] / 256.0;
				float b = (float)pixels[j * myVideo.width * 3 + i * 3 + 2] / 256.0;
				
				// calculate brightness
				float brightness = (r + g + b) / 3.0f;
				
				// Heights
                
				myVerts[j * WIDTH + i] = ofVec3f(i - WIDTH/2, j - HEIGHT/2, brightness * SoundHeight);
				SoundHeight = 20000 * scaledVol;

				myColor[j * WIDTH + i] = ofFloatColor(r, g, b, 0.8);
			}
		}
		
		// VBO location and color update
		myVbo.updateVertexData(myVerts, NUM_PARTICLES);
		myVbo.updateColorData(myColor, NUM_PARTICLES);
	}
}

void testApp::draw(){
	
	// draw vbo
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	cam.begin();
	ofScale(1, -1, 1);
	glPointSize(3);
	myVbo.draw(GL_POINTS, 0, NUM_PARTICLES);
	cam.end();
	ofPopMatrix();
	
	// strings
	string info;
	info = "Vertex num = " + ofToString(NUM_PARTICLES, 0) + "\n";
	info += "FPS = " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(info, 30, 30);
}

void testApp::keyPressed(int key){
	
	// fullscreen
	if(key == 'f') {
		ofToggleFullscreen();
	}
}


//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
	
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
	
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.75;
	smoothedVol += 0.25 * curVol;
	
	bufferCounter++;
	
}

