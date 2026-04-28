#pragma once
#include <JuceHeader.h>

class PanWidthSlider : public juce::Component
{
public:
	PanWidthSlider(const juce::String& text, juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& paramID);
	void resized() override;
private:
	juce::Slider m_WidthSlider;
	juce::Label m_SliderLabel;
	juce::AudioProcessorValueTreeState::SliderAttachment m_Attachment;

};