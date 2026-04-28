#pragma once
#include <JuceHeader.h>

class BypassButton : public juce::Component
{
public:
    BypassButton(const juce::String& text,
        juce::AudioProcessorValueTreeState& apvts,
        const juce::ParameterID& paramID);

    void resized() override;

private:
    juce::ToggleButton m_Button;
    juce::Label m_Label;

    juce::AudioProcessorValueTreeState::ButtonAttachment m_Attachment;
};
