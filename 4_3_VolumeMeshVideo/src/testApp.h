#pragma once
#define WIDTH 640
#define HEIGHT 480
#define NUM_PARTICLES WIDTH * HEIGHT

#include "ofMain.h"

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	void keyPressed  (int key);

	
	ofEasyCam cam; // camera
	ofLight light; // light
	ofVbo myVbo; // VBO
	ofVec3f myVerts[NUM_PARTICLES]; // Verts points
	ofFloatColor myColor[NUM_PARTICLES]; // verts colors
	ofVideoGrabber myVideo;	// webcam
    
    
    float SoundHeight;

    
    void audioIn(float * input, int bufferSize, int nChannels);
	
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int 	bufferCounter;
    int 	drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    ofSoundStream soundStream;



    
};
