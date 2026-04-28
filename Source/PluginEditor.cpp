#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"
//==============================================================================GUI
JuceTestAudioProcessorEditor::JuceTestAudioProcessorEditor(JuceTestAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
    m_TremMixSlider{"TremoloMix", audioProcessor.GetAPVTS(), Parameters::TremoloMixParamID},
    m_FreqSlider{"Tremolo", audioProcessor.GetAPVTS(), Parameters::TremoloTimeParamID},
    m_PanFreqSlider{"PanFreq", audioProcessor.GetAPVTS(), Parameters::PanFreqParamID },
    m_PanWidthSlider{"PanWidth", audioProcessor.GetAPVTS(), Parameters::PanWidthParamID },
    m_BypassButton{ "Bypass", audioProcessor.GetAPVTS(), Parameters::BypassParamID }

{  
    setSize(500, 500);

    m_PanWidthSlider.setSize(500, 500); //PanWidth
    addAndMakeVisible(m_PanWidthSlider);
    m_TremMixSlider.setSize(250, 500); //TremoloMix
    addAndMakeVisible(m_TremMixSlider);
    m_PanFreqSlider.setSize(500, 100); //PanFreq
    addAndMakeVisible(m_PanFreqSlider);
    m_FreqSlider.setSize(250, 100); //FreqSlider
    addAndMakeVisible(m_FreqSlider);

    addAndMakeVisible(audioProcessor.waveViewer);
    audioProcessor.waveViewer.setColours(juce::Colours::white.withAlpha(0.7f), juce::Colours::deeppink);
    addAndMakeVisible(m_BypassButton);

}

JuceTestAudioProcessorEditor::~JuceTestAudioProcessorEditor()
{
}

//==============================================================================
void JuceTestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::cyan);
    g.drawRect(247, 50, 7, 75, 5);
    g.setColour(juce::Colours::deeppink);
    g.drawRect(247, 400, 7, 75, 5);

    g.setColour(juce::Colours::deeppink);
    g.setFont(juce::FontOptions(20.0f));
    g.drawFittedText("TREMOLO", getLocalBounds().removeFromRight(480).removeFromTop(40), juce::Justification::centredLeft, 1);
    g.setColour(juce::Colours::deepskyblue);
    g.setFont(juce::FontOptions(20.0f));
    g.drawFittedText("PINGPONGER", getLocalBounds().removeFromLeft(480).removeFromTop(40), juce::Justification::centredRight, 1);

}

void JuceTestAudioProcessorEditor::resized()
{
    audioProcessor.waveViewer.setBounds(getWidth() * 0.25, 130, getWidth() * 0.5, getHeight() * 0.25);
    m_BypassButton.setBounds(getWidth() * 0.80, 130, getWidth() * 0.5, getHeight() * 0.25);
}

void JuceTestAudioProcessorEditor::sliderValueChanged(juce::Slider* slider_ptr)
{
}
