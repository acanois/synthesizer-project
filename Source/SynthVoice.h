/*
  ==============================================================================

    SynthVoice.h
    Created: 17 May 2021 8:14:38pm
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    SynthVoice();
    
    bool canPlaySound(juce::SynthesiserSound* synthSound) override;
    
    void startNote(int midiNoteNumber,
                    float velocity,
                    juce::SynthesiserSound *sound,
                    int currentPitchWheelPosition) override;
    
    void stopNote(float velocity, bool allowTailOff) override;
    
    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer,
                          int startSample,
                          int numSamples) override;
    
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
};
