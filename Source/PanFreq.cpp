#include "PanFreq.h"
#include "LookAndFeel.h"
PanFreqSlider::PanFreqSlider(const juce::String& text, juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& paramID)
	: m_FrequencySlider{},
	m_SliderLabel{},
	m_Attachment{ apvts,paramID.getParamID(), m_FrequencySlider }
{
	m_FrequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	m_FrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
	m_FrequencySlider.setSize(250, 100); //size
	m_FrequencySlider.setTextValueSuffix(" s");
	addAndMakeVisible(m_FrequencySlider);

	m_SliderLabel.setText("Duration:", juce::dontSendNotification);
	m_SliderLabel.setJustificationType(juce::Justification::horizontallyCentred);
	m_SliderLabel.setBorderSize(juce::BorderSize<int>{0, 0, 2, 0});
	m_SliderLabel.attachToComponent(&m_FrequencySlider, false);
	addAndMakeVisible(m_SliderLabel);
	m_SliderLabel.setSize(250, 10);

	setLookAndFeel(PanWidthLookAndFeel::Get());
}

void PanFreqSlider::resized()
{
	m_FrequencySlider.setTopLeftPosition(250, 0); //pos
	m_SliderLabel.setTopLeftPosition(130, 3);
}
