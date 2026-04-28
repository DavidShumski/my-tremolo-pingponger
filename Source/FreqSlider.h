#pragma once
#include <JuceHeader.h>
class FreqSlider : public juce::Component
{
public:
	FreqSlider(const juce::String& text, juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& paramID);
	void resized() override;
private:
	juce::Slider m_TremoloFrequencySlider;
	juce::Label m_SliderLabel;
	juce::AudioProcessorValueTreeState::SliderAttachment m_TremoloAttachment;
};
