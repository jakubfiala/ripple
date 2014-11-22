//
//  button.cpp
//  ripple
//
//  Created by Jakub Fiala on 22/11/2014.
//
//

#include "button.h"


void Button::display() {
    if (type == "tri") {
        ofColor green(0,255,0);
        ofSetColor(isOn ? green : 0);
        ofTriangle(posX, posY, posX, posY+height, posX+(width*0.85), posY+height/2);
    }
    else {
        //default type is rect
        if (isOn) {
            ofSetColor(255);
            ofRect(posX, posY, width, height);
        }
        else if (litUp) {
            ofSetColor(0);
            ofRect(posX, posY, width, height);
            ofSetColor(0, 255, 0, alpha);
            ofRect(posX, posY, width, height);
            alpha -= 5;
            if (alpha <= 20) {
                litUp = false;
            }
        }
        else {
            ofSetColor(0);
            ofRect(posX, posY, width, height);
        }
        
    }
    ofFill();
}

void Button::create(float pX, float pY, float w, float h, string t) {
    posX = pX;
    posY = pY;
    width = w;
    height = h;
    display();
    isOn = false;
    litUp = false;
    type = t;
}

void Button::lightUp() {
    litUp = true;
    alpha = 255;
}

Boolean Button::checkIfPressed(float pX, float pY) {
    if (pX > posX && pX < (posX+width) && pY > posY && pY < (posY+height)) {
        return true;
    }
    else {
        return false;
    };
}

void Button::toggleButton() {
    isOn = !isOn;
}

Boolean Button::checkIfOn() {
    return isOn;
}




