/*
  ==============================================================================

    OperatorManager.h
    Created: 22 May 2021 11:48:04am
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "OpOscillator.h"

class OperatorManager
{
public:
    OperatorManager();
    
    void initOperators();
    OpOscillator& getOperator (int index);
    void processOperators(juce::dsp::AudioBlock<float>& audioBlock,
                          juce::AudioBuffer<float>& outputBuffer,
                          int startSample,
                          int blockSize);
    void prepareOperators(juce::dsp::ProcessSpec& spec);
    void startOpNotes();
    void stopOpNotes();
    void setFreqs (int midiNoteNumber);
    
private:
    const int NUM_OPERATORS { 4 };
    juce::OwnedArray<OpOscillator> mOperators;
};
