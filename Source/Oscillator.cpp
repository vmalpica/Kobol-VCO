/*
  ==============================================================================

    OsciDemo.cpp

  ==============================================================================
*/

#include "Oscillator.h"
#include <iostream>

Oscillator::Oscillator() {
    
    phase = 0.0f;
    rectThreshold = 0.5f;
    rectGain = 1.0f;
    compThreshold = 0.0f;
    compGain = 0.0f;
    
}
void Oscillator::reset() {
    
    phase = 0.0f;
    rectThreshold = 0.5f;
    rectGain = 1.0f;
    compThreshold = 0.0f;
    compGain = 0.0f;
}



/* ==============================================================================
  Set Waveform Parameters
  ============================================================================== */
    
void Oscillator::setWaveformParameters(float value) {
    
    
    if (value < splitPointA) { //0-0.4: rectifier
        
        float currentSplitPosition= value / splitPointA;
        rectThreshold = currentSplitPosition;
        rectGain = 1.0f;
        compGain = 0.0f;
        compThreshold = 0.0f;
        
        
    } else if (value < splitPointB) { //0.4-0.8: rectifier+comparator
        
        float currentSplitPosition = (value - splitPointA) / (splitPointB - splitPointA);
        rectThreshold = 1.0f;
        rectGain = 1.0f - currentSplitPosition;
        
        compThreshold = 0.0f;
        compGain = currentSplitPosition;
      
        
    } else { //0.8-1.2: comparator
        
        float currentSplitPosition = (value - splitPointB) / (1.0f - splitPointB);
        rectThreshold = 1.0f;
        rectGain = 0.0f;
        compThreshold = currentSplitPosition;
        compGain = 1.0f;
    }
}


/* ==============================================================================
  NEXT SAMPLE
  ============================================================================== */

float Oscillator::nextSample(float position) {
 
    setWaveformParameters(position); //Potenciometer value
    
    phase += inc;
    
    if (phase >= 1.0f) {
        phase -= 1.0f;
    }
    
    float sawtoothSginal = (2.0f * phase - 1.0f);  // Sawtooth signal
   
    
    float rectSignal = rectifier(sawtoothSginal, rectThreshold); // Apply Rectifier
    rectSignal *= rectGain;
    float compSignal = comparator(sawtoothSginal, compThreshold, position); // Apply Comparator
    compSignal *= compGain;

    return amplitude* (rectSignal + compSignal)/2;
}


/* ==============================================================================
  RECTIFIER
  ============================================================================== */

float Oscillator::rectifier(float inputSample, float threshold) {
   
    float outputSample;
    
    if (inputSample <= threshold) {
        outputSample = inputSample;
    } else {
        outputSample = threshold - (threshold+1)* inputSample;
        
    }
    
    return outputSample + (1.0f - threshold) / 2.0f;
  
}


/* ==============================================================================
  COMPARATOR
  ============================================================================== */

float Oscillator::comparator(float inputSample, float threshold, float position) {
    
    threshold = (threshold + 0.2f) * 0.4f;  // Adjust threshold range from 0.5 to 0.9
    float outputSample;

    
    if (position < splitPointB) {
        outputSample = (inputSample > threshold) ? -1.0f : 1.0f;
        
        
    } else {
        outputSample = (inputSample > threshold) ? 1.0f : -1.0f;
        
    }
    

    return outputSample;
}
