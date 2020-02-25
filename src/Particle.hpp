//
//  Particle.hpp
//  kinect_pointCloudTests
//
//  Created by Noah Edelstein on 2/24/20.
//
#pragma once
#include "ofMain.h"

class Particle{
    
public:
    Particle();
    Particle(glm::vec2 _pos, glm::vec2 _vel, float mass);
    
    void applyForce(glm::vec2 force);
    
    void update();
    void draw();
    
    glm::vec2 pos, vel, acc;
    float mass;
    float bornTime;

};
