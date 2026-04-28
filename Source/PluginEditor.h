#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FreqSlider.h"
#include "TremoloMixSlider.h"
#include "PanFreq.h"
#include "PanWidth.h"
#include "BypassButton.h"

class JuceTestAudioProcessorEditor : public juce::AudioProcessorEditor,
                                     public juce::Slider::Listener
{
public:
    JuceTestAudioProcessorEditor (JuceTestAudioProcessor&);
    ~JuceTestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider * slider_ptr) override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceTestAudioProcessor& audioProcessor;

    FreqSlider m_FreqSlider;    //TremoloFreq
    TremoloMixSlider m_TremMixSlider;    //TremoloMix
    PanFreqSlider m_PanFreqSlider;    //PanFreq
    PanWidthSlider m_PanWidthSlider;    //PanWidth
    BypassButton m_BypassButton;     //Bypass

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceTestAudioProcessorEditor)
};
