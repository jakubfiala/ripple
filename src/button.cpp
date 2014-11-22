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
        ofSetColor(isOn ? 255 : 0);
        ofRect(posX, posY, width, height);
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
    type = t;
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




