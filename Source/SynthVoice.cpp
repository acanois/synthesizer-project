/*
  ==============================================================================

    SynthVoice.cpp
    Created: 17 May 2021 8:14:38pm
    Author:  David Richter

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice()
{
    
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound* synthSound)
{
    return dynamic_cast<SynthSound*>(synthSound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber,
                float velocity,
                juce::SynthesiserSound *sound,
                int currentPitchWheelPosition)
{
    
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer,
                      int startSample,
                      int numSamples)
{
    
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
    
}
