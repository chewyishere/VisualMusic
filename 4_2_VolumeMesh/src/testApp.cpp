#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetVerticalSync(true);
    
    // load an image from disk
	img.loadImage("01.jpg");
	
    width = img.getWidth();
    height = img.getHeight();
    
    
	// loop through the image in the x and y axes
	skip = 4; // load a subset of the points
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
        
            mesh.addVertex(ofPoint(x,y,0));
            mesh.addColor(ofFloatColor(0,0,0));
        }
    }
    
	for (int y = 0; y<height-1; y++){
		for (int x=0; x<width-1; x++){
			mesh.addIndex(x+y*width);				// 0
			mesh.addIndex((x+1)+y*width);			// 1
			mesh.addIndex(x+(y+1)*width);			// 10
			
			mesh.addIndex((x+1)+y*width);			// 1
			mesh.addIndex((x+1)+(y+1)*width);		// 11
			mesh.addIndex(x+(y+1)*width);			// 10
		}
	}
    
    // we're going to load a ton of points into an ofMesh
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    glPointSize (6);
	pSize = 6.0;
    
    glEnable(GL_POINT_SMOOTH); // use circular points instead of square points
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
    temZ = 100.0;

}

//--------------------------------------------------------------
void testApp::update() {
    
    //lets scale the vol up to a 0-1 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
	//lets record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}

    for (int i=0; i<width*height; i++){
        
        if(i % skip == 0){
           
            ofFloatColor sampleColor (img.getPixels()[i*3]/255.f,		// r
                                      img.getPixels()[i*3+1]/255.f,		// g
                                      img.getPixels()[i*3+2]/255.f);
            
            ofVec3f temVec = mesh.getVertex(i);
            temZ = ofMap (sampleColor.getBrightness(), 0, 255, 0, 50000);
            
            temVec.z = temZ * scaledVol*10;
            
            mesh.setVertex(i, temVec);
            mesh.setColor(i, sampleColor);
            
            ofEnableDepthTest();
          
            
        } else {
            
            mesh.setColor(i, ofColor(0,0,0,0));
        }
        

    }
}

//

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



//--------------------------------------------------------------
void testApp::draw() {
	ofBackgroundGradient(ofColor::gray, ofColor::black, OF_GRADIENT_CIRCULAR);
	
	// even points can overlap with each other, let's avoid that
	cam.begin();
	ofScale(2, -2, 2); // flip the y axis and zoom in a bit
	ofRotateY(90);
	ofTranslate(-img.getWidth() / 2, -img.getHeight() / 2);
	mesh.draw();
	cam.end();
    
    string reportString = "scaledVol = " + ofToString(scaledVol)+ "\n" + "temZ = " + ofToString(temZ);
	ofDrawBitmapString(reportString, 20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}