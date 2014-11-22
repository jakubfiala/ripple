//
//  button.cpp
//  ripple
//
//  Created by Jakub Fiala on 22/11/2014.
//
//

#include "button.h"


void Button::display() {
    ofSetColor(isOn ? 255 : 0);
    ofRect(posX, posY, width, height);
    ofFill();
}

void Button::create(float pX, float pY, float w, float h) {
    posX = pX;
    posY = pY;
    width = w;
    height = h;
    display();
    isOn = false;
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




