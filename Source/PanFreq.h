#pragma once
#include <JuceHeader.h>
class PanFreqSlider : public juce::Component
{
public:
	PanFreqSlider(const juce::String& text, juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& paramID);
	void resized() override;
private:
	juce::Slider m_FrequencySlider;
	juce::Label m_SliderLabel;
	juce::AudioProcessorValueTreeState::SliderAttachment m_Attachment;
};