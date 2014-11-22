//
//  button.h
//  ripple
//
//  Created by Jakub Fiala on 22/11/2014.
//
//

#include "ofMain.h"

class Button {
    public:
        Boolean checkIfPressed(float pX, float pY);
        void toggleButton();
        void lightUp();
        void create(float pX, float pY, float w, float h);
        void display();
    
    protected:
        float posX, posY, width, height;
        Boolean isOn;
    
};
