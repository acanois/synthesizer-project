/*
  ==============================================================================

    OperatorManager.cpp
    Created: 22 May 2021 11:48:04am
    Author:  David Richter

  ==============================================================================
*/

#include "OperatorManager.h"

OperatorManager::OperatorManager()
{
    
}

void OperatorManager::initOperators()
{
    for (int i = 0; i < NUM_OPERATORS; ++i)
        mOperators.add (new OpOscillator());
}

OpOscillator& OperatorManager::getOperator (int index)
{
    jassert (index < NUM_OPERATORS);
    return *mOperators[index];
}

void OperatorManager::processOperators (juce::dsp::AudioBlock<float>& audioBlock,
                                       juce::AudioBuffer<float>& outputBuffer,
                                       int startSample,
                                       int blockSize)
{
    for (auto op : mOperators)
        op->processOpOscillator (audioBlock, outputBuffer, 0, blockSize);
}

void OperatorManager::prepareOperators (juce::dsp::ProcessSpec& spec)
{
    for (auto op : mOperators)
        op->prepareOscillator (spec);
}

void OperatorManager::startOpNotes()
{
    for (auto op : mOperators)
        op->startNote();
}

void OperatorManager::stopOpNotes()
{
    for (auto op : mOperators)
        op->stopNote();
}

void OperatorManager::setFreqs (int midiNoteNumber)
{
    for (auto op : mOperators)
        op->setOpFrequency (midiNoteNumber);
}
