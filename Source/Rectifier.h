/*
  ==============================================================================

    rectifier.h
    Created: 8 Jun 2024 9:04:22pm
    Author:  valen

  ==============================================================================
*/


// Rectifier.h
#pragma once

class Rectifier {
public:
    
    float threshold;
    float gain;
    
    void reset(){
        threshold=0.5;
    }
    
    void setThreshold(float newThreshold) {
        threshold = newThreshold;
    }
    
    
    float processSample(float inputSample,float threshold ) {
        float outputSample;
        if (inputSample <= threshold) {
            outputSample = inputSample;
        } else {
            outputSample = threshold - inputSample;
        }
        return outputSample + (1.0f - threshold) / 2.0f;
    }
    
    
};




