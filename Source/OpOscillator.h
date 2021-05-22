/*
  ==============================================================================

    OpOscillator.h
    Created: 22 May 2021 10:27:01am
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OpOscillator
{
public:
    void prepareVoice (double sampleRate, int samplesPerBlock, int numOutputChannels);
    void initAdsr();
    void setAdsr (float attack, float decay, float sustain, float release);
    void startNote();
    void stopNote();
    
private:
    juce::dsp::Oscillator<float> mOscillator { [](float x) { return std::sin(x); } };
    juce::ADSR mAdsr;
    juce::ADSR::Parameters mAdsrParameters;
    
    bool mOscillatorPrepared { false };
    bool mAdsrPrepared { false };
};
