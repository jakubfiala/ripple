/*
 *  maxiBark.cpp
 *  Bark scale loudness
 *
 *  Created by Jakub on 01/12/2014.
 *  Copyright 2014 Goldsmiths Creative Computing. All rights reserved.
 *
 */

#pragma once
#pragma pack(16)

#include "maxiFFT.h"
#include <math.h>
#include <iostream>
//#include <algorithm>
#include <cstdlib>
#ifdef __APPLE_CC__
#include <Accelerate/Accelerate.h>
#endif

using namespace std;

//convert to Bark scale (Zwicker, 1961)
inline double hzToBark(double hz) {
    return 13.0*atan(hz/1315.8) + 3.5*atan(pow((hz/7518.0),2));
}

inline double binToHz(unsigned int bin, unsigned int sR, unsigned int bS) {
    return bin*sR/bS;
}

template <class T>

class maxiBarkScaleAnalyser {
public:
    int NUM_BARK_BANDS;
    
    void setup(unsigned int sR, unsigned int bS) {
        this->sampleRate = sR;
        this->bufferSize = bS;
        specSize = bS/2;
        NUM_BARK_BANDS = 24;
        for (int i=0; i<specSize; i++) {
            barkScale[i] = hzToBark(binToHz(i, sR, bS));
        }
    }
    
    double* loudness(float* normalisedSpectrum, std::string type) {
        bbLimits[0] = 0;
        int currentBandEnd = barkScale[specSize-1]/NUM_BARK_BANDS;
        int currentBand = 1;
        
        for(int i = 0; i<specSize; i++){
            while(barkScale[i] > currentBandEnd) {
                bbLimits[currentBand] = i;
                currentBand++;
                currentBandEnd = currentBand*barkScale[specSize-1]/NUM_BARK_BANDS;
            }
        }
        
        bbLimits[NUM_BARK_BANDS] = specSize-1;
        
        if (type == "specific") {
            for (int i = 0; i < NUM_BARK_BANDS; i++){
                double sum = 0;
                for (int j = bbLimits[i] ; j < bbLimits[i+1] ; j++) {
                    
                    sum += normalisedSpectrum[j];
                }
                specificLoudness[i] = pow(sum,0.23);
            }
            
            return specificLoudness;
        }
        else if (type == "relative") {
            for (int i = 0; i < NUM_BARK_BANDS; i++){
                double sum = 0;
                for (int j = bbLimits[i] ; j < bbLimits[i+1] ; j++) {
                    
                    sum += normalisedSpectrum[j];
                }
                specificLoudness[i] = pow(sum,0.23);
            }
            
            double max = 0;
            for (int i = 0; i < NUM_BARK_BANDS; i++){
                if (specificLoudness[i] > max) max = specificLoudness[i];
            }
            
            for (int i = 0; i < NUM_BARK_BANDS; i++){
                relativeLoudness[i] = specificLoudness[i]/max;
            }
            
            return relativeLoudness;
        }
        else { //default is total
            for (int i = 0; i < NUM_BARK_BANDS; i++){
                double sum = 0;
                for (int j = bbLimits[i] ; j < bbLimits[i+1] ; j++) {
                    
                    sum += normalisedSpectrum[j];
                }
                specificLoudness[i] = pow(sum,0.23);
            }
            
            totalLoudness[0] = 0;
            
            for (int i = 0; i < 24; i++){
                totalLoudness[0] += specificLoudness[i];
            }
            
            return totalLoudness;
        }
        
        
        
    }
private:
    int bbLimits[24];
    unsigned int sampleRate, bufferSize, specSize;
    double barkScale[2048];
    double specificLoudness[24];
    double relativeLoudness[24];
    double totalLoudness[1];
    
};

typedef maxiBarkScaleAnalyser<double> maxiBark;






