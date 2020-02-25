#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    gui.setup();
    gui.add(pointMinSlider.setup("pointcloudMin", pointCloudMinZ, 0.0, 200.0));
    gui.add(pointMaxSlider.setup("pointcloudMax", pointCloudMaxZ, 0.0, 1500.0));
    
    gui.add(shadervar1Slider.setup("shader val 1", shaderVar1, 0.0f, 200.0f));
    gui.add(shadervar2Slider.setup("shader val 2", shaderVar2, 0.0f, 200.0f));
    gui.add(shadervar3Slider.setup("shader val 3", shaderVar3, 0.0f, 200.0f));
    gui.add(shadervar4Slider.setup("shader val 4", shaderVar4, 0.0f, 200.0f));
    
    // enable depth->video image calibration
    kinect.setRegistration(true);
    
    kinect.init();
    
    kinect.open();        // opens first available kinect
 
ofSetFrameRate(60);

    shader.load("shader/twist.vert" , "shader/twist.frag" );
    shaderVar1 , shaderVar2 , shaderVar3 , shaderVar4 ;
    
    particleSystem = ParticleSystem(particleStartPos);
    particleSystems.push_back(particleSystem);
    gravity = glm::vec2(0,.15);


}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0);

    kinect.update();

//    ofVec2f nMouse = ofVec2f( ((float) mouseX / (float)ofGetWidth()) - 0.5 , ((float) mouseY / (float)ofGetHeight() ) - 0.5 ) ;
    /// cout << "nMouse :" << nMouse << endl ;
    
    
    shader.load("shader/twist.vert" , "shader/twist.frag" );
    
    for (int i=0; i<particleSystems.size(); i++){
        particleSystems[i].applyForce(gravity);
        particleSystems[i].update();
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    ofSetColor(255, 255, 255);
    ofPushMatrix();
    shader.begin();
    
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform1f("var1", shadervar1Slider );
    shader.setUniform1f("var2", shadervar2Slider );
    shader.setUniform1f("var3", shadervar3Slider );
    shader.setUniform1f("var4", shadervar4Slider );

    
    easyCam.begin();
    drawPointCloud();
    easyCam.end();
    shader.end();
    ofPopMatrix();
    for (int i=0; i<particleSystems.size(); i++){
        particleSystems[i].draw();
    }
}


//---------------------

void ofApp::drawPointCloud()
{
    int w = 640;
    int h = 480;
    ofPushMatrix();
    glEnable(GL_DEPTH_TEST);
    ofScale(1, -1, -1);
    ofTranslate(0, 0, -1000); // center the points a bit
    ofEnableBlendMode( OF_BLENDMODE_ALPHA ) ;
    
    ofColor offset = ofColor::fromHsb((ofGetFrameNum()/2  )%255, 255, 255 ) ;
    // ofEnableBlendMode( OF_BLENDMODE_ADD ) ;
    int step = 5 ;
    float boxSize = step;
    for(int y = 0; y < h; y += step) {
        for(int x = 0; x < w; x += step) {
            if(kinect.getDistanceAt(x, y) > 0) {
                
                ofVec3f vertex = kinect.getWorldCoordinateAt(x, y);
                if ( vertex.z > pointMinSlider && vertex.z < pointMaxSlider )
                {
                    float normalizedZ = ofMap(vertex.z, pointMinSlider, pointMaxSlider, -360.0f , 360.0f );
                    mesh.addVertex(vertex);
                    
                    //Offset the color here
                    ofColor col = kinect.getColorAt(x,y) + offset; // + offset ;
                    
                    //mesh.addColor( col );
                    ofSetColor( col );
                    ofPushMatrix();
                    ofQuaternion rot;
                    ofQuaternion rotX = ofQuaternion(sin(ofGetElapsedTimef() + y + x * 2.5f) * 360.0f, ofVec3f( 0.0f , 1.0f , 0.0f ));
                    ofQuaternion rotY = ofQuaternion(normalizedZ, ofVec3f( 1.0f , 0.0f , 0.0f ) ) ;
                    rot = rotX * rotY ;
                    ofVec3f axis ;
                    float angle ;
                    rot.getRotate(angle, axis);
                    
                    ofTranslate(vertex);
                    
                    ///spawn particles at vertices --- need to figure out
//                    for(int i = 0; i < vertex.length(); i+=10){
//                    particleSystems.push_back(ParticleSystem(glm::vec2(0,0)));
//                    }
                    
                    
                    ofRotateDeg(angle , axis.x , axis.y , axis.z);
                    ofBox(ofVec3f(0,0,0), boxSize);
                    
                    ofPopMatrix();
                }
                
            }
        }
    }
    glDisable(GL_DEPTH_TEST);
    ofPopMatrix();
    ofEnableBlendMode( OF_BLENDMODE_ADD ) ;
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
