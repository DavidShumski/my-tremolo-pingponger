#include "BypassButton.h"

BypassButton::BypassButton(const juce::String& text,
    juce::AudioProcessorValueTreeState& apvts,
    const juce::ParameterID& paramID)
    : m_Attachment(apvts, paramID.getParamID(), m_Button)
{
    m_Button.setButtonText("Bypass");
    addAndMakeVisible(m_Button);

    m_Label.setText(text, juce::dontSendNotification);
    m_Label.setJustificationType(juce::Justification::centred);
    m_Label.attachToComponent(&m_Button, false);
    addAndMakeVisible(m_Label);
    setSize(100, 40);
}

void BypassButton::resized()
{
    m_Button.setBounds(0, 0, getWidth(), getHeight());
}