#include "FreqSlider.h"
#include "LookAndFeel_Tremolo.h"
FreqSlider::FreqSlider(const juce::String& text, juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& paramID)
	: m_TremoloFrequencySlider{},
	  m_SliderLabel{},
	  m_TremoloAttachment{ apvts,paramID.getParamID(), m_TremoloFrequencySlider }
{
	m_TremoloFrequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	m_TremoloFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
	m_TremoloFrequencySlider.setSize(250, 100); //size
	m_TremoloFrequencySlider.setTextValueSuffix(" s");
	addAndMakeVisible(m_TremoloFrequencySlider);

	m_SliderLabel.setText("", juce::dontSendNotification);
	m_SliderLabel.setJustificationType(juce::Justification::horizontallyCentred);
	m_SliderLabel.setBorderSize(juce::BorderSize<int>{0, 0, 2, 0});
	m_SliderLabel.attachToComponent(&m_TremoloFrequencySlider, false);
	addAndMakeVisible(m_SliderLabel);
	m_SliderLabel.setSize(250, 15);

	setLookAndFeel(TremoloMixLookAndFeel::Get());

}

void FreqSlider::resized()
{
	m_TremoloFrequencySlider.setTopLeftPosition(0, 0); //pos
	m_SliderLabel.setTopLeftPosition(0, 10);
}