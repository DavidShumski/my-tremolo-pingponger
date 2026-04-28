#pragma once
#include <JuceHeader.h>
class TremoloMixSlider : public juce::Component
{
    public:
    TremoloMixSlider(const juce::String& text, juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& paramID);
	void resized() override;
    private:
    juce::Slider m_Slider;
	juce::Label m_SliderLabel;
	juce::AudioProcessorValueTreeState::SliderAttachment m_Attachment;
};
    