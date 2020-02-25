#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"

//#include "Particle.hpp"
#include "ParticleSystem.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void drawPointCloud();
    
    ofxKinect kinect;
    
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
    ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    
    bool bDrawPointCloud;
    
    int nearThreshold;
    int farThreshold;
    
//    int angle;
    
    // used for viewing the point cloud
    ofEasyCam easyCam;
    
    
    ofxPanel gui;
    ofxFloatSlider pointMinSlider;
    ofxFloatSlider pointMaxSlider;
    ofxFloatSlider shadervar1Slider;
    ofxFloatSlider shadervar2Slider;
    ofxFloatSlider shadervar3Slider;
    ofxFloatSlider shadervar4Slider;

    float guiWidth;
    
    float minBlobSize , maxBlobSize ;
    float pointCloudMinZ = 0;
    float pointCloudMaxZ = 1500;
    
    ofVboMesh mesh;
    
    bool bKinectOpen;
    
    bool bDrawShader;
    ofShader shader ;
    float shaderVar1 , shaderVar2 , shaderVar3 , shaderVar4;
    
    
//    particle system cpu
//    Particle particle;
    ParticleSystem particleSystem;
    glm::vec2 gravity;
    glm::vec2 particleStartPos;
    
    vector<ParticleSystem>particleSystems;
};
