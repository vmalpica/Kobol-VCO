/*
  ==============================================================================

    comparator.h
    Created: 8 Jun 2024 9:04:30pm
    Author:  valen

  ==============================================================================
*/

#pragma once

class Comparator {
public:
    float threshold;

    Comparator() : threshold(0.5f) {}  // Constructor para inicializar el threshold

    void reset() {
        threshold = 0.5f;
    }

    void setThreshold(float newThreshold) {
        threshold = newThreshold;
    }

    float processSample(float inputSample, float threshold) {
        float outputSample;
        if (inputSample > threshold) {
            outputSample = 1.0f;
        } else {
            outputSample = -1.0f;
        }
        return outputSample;
    }
};


