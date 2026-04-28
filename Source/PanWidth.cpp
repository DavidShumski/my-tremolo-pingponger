#include "PanWidth.h"
#include "LookAndFeel.h"
PanWidthSlider::PanWidthSlider(const juce::String& text, juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& paramID)
	: m_WidthSlider{},
	m_SliderLabel{},
	m_Attachment{ apvts,paramID.getParamID(), m_WidthSlider }
{
	m_WidthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	m_WidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
	m_WidthSlider.setSize(200, 200);
	m_WidthSlider.setTextValueSuffix(" %");
	addAndMakeVisible(m_WidthSlider);

	m_SliderLabel.setText("Width", juce::dontSendNotification);
	m_SliderLabel.setJustificationType(juce::Justification::topRight);
	m_SliderLabel.setBorderSize(juce::BorderSize<int>{0, 0, 2, 0});
	m_SliderLabel.attachToComponent(&m_WidthSlider, false);
	addAndMakeVisible(m_SliderLabel);
	m_SliderLabel.setSize(100, 200);

	setLookAndFeel(PanWidthLookAndFeel::Get());
}

void PanWidthSlider::resized()
{
	m_WidthSlider.setTopLeftPosition(275, 275);
}

