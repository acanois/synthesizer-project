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
    mOpManager->initOperators();
}

bool SynthVoice::canPlaySound (juce::SynthesiserSound* synthSound)
{
    return dynamic_cast<SynthSound*> (synthSound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber,
                float velocity,
                juce::SynthesiserSound *sound,
                int currentPitchWheelPosition)
{
    DBG (juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    
    mOpManager->setFreqs(midiNoteNumber);
    mOpManager->startOpNotes();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    mOpManager->stopOpNotes();
}

void SynthVoice::prepareVoice (double sampleRate, int samplesPerBlock, int numOutputChannels)
{
    juce::dsp::ProcessSpec spec = prepareSpec (sampleRate, samplesPerBlock, numOutputChannels);

    mOpManager->prepareOperators(spec);
    
    // jassert only functions when building in debug
    jassert (mSpecPrepared);
    mIsPrepared = true;
}

juce::dsp::ProcessSpec SynthVoice::prepareSpec(double sampleRate, int samplesPerBlock, int numOutputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numOutputChannels;
    
    mSpecPrepared = true;
    
    return spec;
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer,
                      int startSample,
                      int numSamples)
{
    jassert (mIsPrepared);
    
    juce::dsp::AudioBlock<float> audioBlock { outputBuffer };
    mOpManager->processOperators(audioBlock, outputBuffer, 0, numSamples);
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}
