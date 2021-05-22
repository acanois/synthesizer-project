/*
  ==============================================================================

    OpOscillator.cpp
    Created: 22 May 2021 10:27:01am
    Author:  David Richter

  ==============================================================================
*/

#include "OpOscillator.h"

void OpOscillator::prepareOscillator (juce::dsp::ProcessSpec& spec)
{
    initAdsr (spec.sampleRate);
    mOscillator.prepare(spec);
}

void OpOscillator::initAdsr (double sampleRate)
{
    mAdsr.setSampleRate(sampleRate);
    mAdsrParameters.attack = 0.1f;
    mAdsrParameters.decay = 0.1f;
    mAdsrParameters.sustain = 0.5f;
    mAdsrParameters.release = 0.1f;
    
    mAdsrPrepared = true;
}

void OpOscillator::setAdsr (float attack, float decay, float sustain, float release)
{
    // Currently unimplemented
    
    mAdsrParameters.attack = attack;
    mAdsrParameters.decay = decay;
    mAdsrParameters.sustain = sustain;
    mAdsrParameters.release = release;
}

void OpOscillator::startNote()
{
    mAdsr.noteOn();
}

void OpOscillator::stopNote()
{
    mAdsr.noteOff();
}

void OpOscillator::processOpOscillator (
                          juce::dsp::AudioBlock<float>& audioBlock,
                          juce::AudioBuffer<float>& outputBuffer,
                          int startSample,
                          int blockSize
                          )
{
    mOscillator.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    mAdsr.applyEnvelopeToBuffer(outputBuffer, startSample, blockSize);
}
