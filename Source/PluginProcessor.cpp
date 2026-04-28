#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ProtectYourEars.h" //include

//==============================================================================
JuceTestAudioProcessor::JuceTestAudioProcessor()
	: AudioProcessor(BusesProperties()
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)),
	m_Params{ *this }, waveViewer(2)
{
	waveViewer.setRepaintRate(30);
	waveViewer.setBufferSize(256);
}

JuceTestAudioProcessor::~JuceTestAudioProcessor()
{
}

//==============================================================================
const juce::String JuceTestAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool JuceTestAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool JuceTestAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool JuceTestAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double JuceTestAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int JuceTestAudioProcessor::getNumPrograms()
{
	return 1;

}

int JuceTestAudioProcessor::getCurrentProgram()
{
	return 0;
}

void JuceTestAudioProcessor::setCurrentProgram([[maybe_unused]] int index)
{
}

const juce::String JuceTestAudioProcessor::getProgramName(int index)
{
	return {};
}

void JuceTestAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}



//PREPARE TO PLAY


//PREPARE TO PLAY
void JuceTestAudioProcessor::prepareToPlay([[maybe_unused]] double sampleRate, [[maybe_unused]] int samplesPerBlock)
{
	m_Params.PrepareToPlay(sampleRate);
	m_Params.Reset();//new sample rate, new reset
	this->mysampleRate = sampleRate;

}




void JuceTestAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceTestAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else

	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif



//PROCESS BLOCK
void JuceTestAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples()); //safety defensive programming

	//PARAMETERS UPDATE
	m_Params.Update();
	auto* channelDataL = buffer.getWritePointer(0);
	auto* channelDataR = buffer.getWritePointer(1); //updating input both channels same time both channels

	if (m_Params.GetBypass() == false) {
		for (int sample = 0; sample < buffer.getNumSamples(); sample++)
		{
			//SMOOTHEN
			m_Params.Smoothen();
			float dryL = channelDataL[sample];
			float dryR = channelDataR[sample];

			// ==== TremoloLogic ====
			float TremoloLFO = (std::sin(twoPi * tremoloPhase) + 1.0f) * 0.5f; // Sinewave manipulation
			tremoloPhase += 1 / m_Params.GetTremolo() / mysampleRate;
			if (tremoloPhase >= 1.0f) tremoloPhase -= 1.0f; // TremPhase go back to "0"
			float wetL = dryL * TremoloLFO;
			float wetR = dryR * TremoloLFO;
			//TremoloEffect apply
			float mixedL = (1.0f - m_Params.GetTremoloMix() / 100) * dryL + wetL * m_Params.GetTremoloMix() / 100;
			float mixedR = (1.0f - m_Params.GetTremoloMix() / 100) * dryR + wetR * m_Params.GetTremoloMix() / 100;

			// ==== PingPongLogic ====
			float PanLFO = (std::sin(twoPi * PanPhase) + 1.0f) * 0.5f; //from 0 to 1
			PanPhase += 1 / m_Params.GetPanFreq() / mysampleRate;
			if (PanPhase >= 1.0f) PanPhase -= 1.0f; // PanPhase go back to "0"

			float offset = (PanLFO - 0.5f) * m_Params.GetPanWidth() / 100;
			float panLeft = 0.5f - offset;
			float panRight = 0.5f + offset;
			//PingPongEffect apply
			channelDataL[sample] = mixedL * panLeft;
			channelDataR[sample] = mixedR * panRight;

		}
	} else if(m_Params.GetBypass() == true)
	{
		for (int sample = 0; sample < buffer.getNumSamples(); sample++)
		{
			m_Params.Smoothen();
			channelDataL[sample];
			channelDataR[sample];
		}
	}
			waveViewer.pushBuffer(buffer);
	protectYourEars(buffer); //safety
}

bool JuceTestAudioProcessor::hasEditor() const
{
	return true;
}

juce::AudioProcessorEditor* JuceTestAudioProcessor::createEditor()
{
	return new JuceTestAudioProcessorEditor(*this);
}
//GET

//GET

void JuceTestAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	//saving
	copyXmlToBinary(*m_Params.GetAPVTS().copyState().createXml(), destData);
	DBG(m_Params.GetAPVTS().copyState().toXmlString());
}


//SET

//SET
void JuceTestAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	std::unique_ptr<juce::XmlElement> xml{ getXmlFromBinary(data, sizeInBytes) };
	if (xml != nullptr && xml->hasTagName(m_Params.GetAPVTS().state.getType()))
	{
		m_Params.GetAPVTS().replaceState(juce::ValueTree::fromXml(*xml));
	}
}


juce::AudioProcessorValueTreeState& JuceTestAudioProcessor::GetAPVTS()
{
	return m_Params.GetAPVTS();
}


// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new JuceTestAudioProcessor();
}
//====================================================

