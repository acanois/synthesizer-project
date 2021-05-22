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
    /// mOscillator.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    mOpOscillator->setOpFrequency (midiNoteNumber);
    /// mAdsr.noteOn();
    mOpOscillator->startNote();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    // mAdsr.noteOff();
    mOpOscillator->stopNote();
}

void SynthVoice::prepareVoice (double sampleRate, int samplesPerBlock, int numOutputChannels)
{
    juce::dsp::ProcessSpec spec = prepareSpec(sampleRate, samplesPerBlock, numOutputChannels);
    /// prepareAdsr (sampleRate);
    /// mOscillator.prepare(spec);
    mOpOscillator->prepareOscillator (spec);
    
    // jassert only functions when building in debug
    jassert (mSpecPrepared);
    /// jassert (mAdsrPrepared);
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
    /// mOscillator.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    mOpOscillator->processOpOscillator (audioBlock, outputBuffer, 0, numSamples);
    /// mAdsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}
