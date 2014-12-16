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
        Boolean checkIfOn();
        int getNote();
        void toggleButton();
        void lightUp();
        void create(float pX, float pY, float w, float h, string t, int n);
        void display();
    
    protected:
        float posX, posY, width, height, alpha;
        Boolean isOn, litUp;
        string type;
        int note;
    
};
