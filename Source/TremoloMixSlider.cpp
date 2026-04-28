#include "TremoloMixSlider.h"
#include "LookAndFeel_Tremolo.h"
TremoloMixSlider::TremoloMixSlider(const juce::String& text, juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& paramID)
	: m_Slider{},
	  m_SliderLabel{},
	  m_Attachment{ apvts,paramID.getParamID(), m_Slider }
{
	m_Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	m_Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
	m_Slider.setSize(200, 200);
	m_Slider.setTextValueSuffix(" %");
	addAndMakeVisible(m_Slider);

	m_SliderLabel.setText("Mix", juce::dontSendNotification);
	m_SliderLabel.setJustificationType(juce::Justification::topLeft);
	m_SliderLabel.setBorderSize(juce::BorderSize<int>{0, 0, 2, 0});
	m_SliderLabel.attachToComponent(&m_Slider, false);
	addAndMakeVisible(m_SliderLabel);
	m_SliderLabel.setSize(100, 200);

	setLookAndFeel(TremoloMixLookAndFeel::Get());
}

void TremoloMixSlider::resized()
{
	m_Slider.setTopLeftPosition(25, 275);
}