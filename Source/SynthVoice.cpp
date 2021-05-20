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
    mOscillator.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    mAdsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    mAdsr.noteOff();
}

void SynthVoice::prepareVoice (double sampleRate, int samplesPerBlock, int numOutputChannels)
{

    juce::dsp::ProcessSpec spec = prepareSpec(sampleRate, samplesPerBlock, numOutputChannels);
    prepareAdsr (sampleRate);
    
    mOscillator.prepare(spec);
//    mGain.prepare(spec);
//
//    mGain.setGainLinear(0.1f);
    
    jassert (mSpecPrepared);
    jassert (mAdsrPrepared);
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

void SynthVoice::prepareAdsr (double sampleRate)
{
    mAdsr.setSampleRate(sampleRate);
    mAdsrParameters.attack = 0.1f;
    mAdsrParameters.decay = 0.1f;
    mAdsrParameters.sustain = 0.5f;
    mAdsrParameters.release = 0.1f;
    
    mAdsrPrepared = true;
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer,
                      int startSample,
                      int numSamples)
{
    jassert (mIsPrepared);
    
    juce::dsp::AudioBlock<float> audioBlock { outputBuffer };
    mOscillator.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
//    mGain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    mAdsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}
