#include "Parameters.h"

template<typename T> //template
void CastParameter(const juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& paramID, T& destination)
{
	destination = dynamic_cast<T>(apvts.getParameter(paramID.getParamID()));
}




Parameters::Parameters(juce::AudioProcessor& processor) :
	m_APVTS{ processor, nullptr,"APVTS", createParameterLayout() },
	m_TremoloParam{},
	m_TremoloSmoother{},
	m_Tremolo{},
	m_TremoloMixParam{},
	m_TremoloMixSmoother{},
	m_TremoloMix{},
	m_PanFreqParam{},
	m_PanFreqSmoother{},
	m_PanFreq{},
	m_PanWidthParam{},
	m_PanWidthSmoother{},
	m_PanWidth{},
	m_BypassParam{},
	m_BypassSmoother{},
	m_Bypass{}

{
	//tremoloCast
	CastParameter(m_APVTS, TremoloTimeParamID, m_TremoloParam);
	//tremolomixCast
	CastParameter(m_APVTS, TremoloMixParamID, m_TremoloMixParam);
	//PanFreqCast
	CastParameter(m_APVTS, PanFreqParamID, m_PanFreqParam);
	//PanWidthCast
	CastParameter(m_APVTS, PanWidthParamID, m_PanWidthParam);
	//BypassCast
	CastParameter(m_APVTS, BypassParamID, m_BypassParam);
}

void Parameters::PrepareToPlay(double sampleRate)
{
	//zipper noise
	const double smoothDuration = 0.2;
	m_TremoloSmoother.reset(sampleRate, smoothDuration);
	m_TremoloMixSmoother.reset(sampleRate, smoothDuration);
	m_PanFreqSmoother.reset(sampleRate, smoothDuration);
	m_PanWidthSmoother.reset(sampleRate, smoothDuration);
	m_BypassSmoother.reset(sampleRate, smoothDuration);

}
void Parameters::Reset()
{
	m_Tremolo = 0.f;
	m_TremoloMix = 0.f;
	m_PanFreq = 0.f;
	m_PanWidth = 0.f;
	m_Bypass = false;
	m_TremoloSmoother.setCurrentAndTargetValue(m_TremoloParam->get());
	m_TremoloMixSmoother.setCurrentAndTargetValue(m_TremoloMixParam->get());
	m_PanFreqSmoother.setCurrentAndTargetValue(m_PanFreqParam->get());
	m_PanWidthSmoother.setCurrentAndTargetValue(m_PanWidthParam->get());
	m_BypassSmoother.setCurrentAndTargetValue(m_BypassParam->get());

}
void Parameters::Update()
{
	m_TremoloSmoother.setTargetValue(m_TremoloParam->get());
	m_TremoloMixSmoother.setTargetValue(m_TremoloMixParam->get());
	m_PanFreqSmoother.setTargetValue(m_PanFreqParam->get());
	m_PanWidthSmoother.setTargetValue(m_PanWidthParam->get());
	m_BypassSmoother.setTargetValue(m_BypassParam->get());
}

void Parameters::Smoothen()
{
	m_Tremolo = m_TremoloSmoother.getNextValue();
	m_TremoloMix = m_TremoloMixSmoother.getNextValue();
	m_PanFreq = m_PanFreqSmoother.getNextValue();
	m_PanWidth = m_PanWidthSmoother.getNextValue();
	m_Bypass = m_BypassSmoother.getNextValue();
}

//properties creation
juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout()
{
	juce::AudioProcessorValueTreeState::ParameterLayout parameters{}; //parameters

	juce::NormalisableRange<float> tremoloRange { 0.01f, 4.f, 0.01f, 0.5f };
	parameters.add(std::make_unique<juce::AudioParameterFloat>(TremoloTimeParamID.getParamID(), "TremoloTime", tremoloRange, 1.f));
	juce::NormalisableRange<float> tremoloMixRange{ 0, 100, 1, 1 };
	parameters.add(std::make_unique<juce::AudioParameterFloat>(TremoloMixParamID.getParamID(), "TremoloMix", tremoloMixRange, 50));
	juce::NormalisableRange<float> PanFreqRange{ 0.01f, 4.f, 0.01f, 0.5f };
	parameters.add(std::make_unique<juce::AudioParameterFloat>(PanFreqParamID.getParamID(), "PanFreq", PanFreqRange, 1.f));
	juce::NormalisableRange<float> PanWidthRange{ 0, 100, 1, 1 };
	parameters.add(std::make_unique<juce::AudioParameterFloat>(PanWidthParamID.getParamID(), "PanWidth", PanWidthRange, 50));
	//bypass button
	parameters.add(std::make_unique<juce::AudioParameterBool>(BypassParamID.getParamID(), "MyBypass", false));



	return parameters;
}

//tremolo
float Parameters::GetTremolo() const
{
	return m_Tremolo;
}
//mix 
float Parameters::GetTremoloMix() const
{
	return m_TremoloMix;
}
//panFreq
float Parameters::GetPanFreq() const
{
	return m_PanFreq;
}
//PanWidth
float Parameters::GetPanWidth() const
{
	return m_PanWidth;
}

bool Parameters::GetBypass() const
{
	return m_Bypass;
}


juce::AudioProcessorValueTreeState& Parameters::GetAPVTS()
{
	return m_APVTS;
}
