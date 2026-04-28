#pragma once
#include <JuceHeader.h>



class Parameters
{
public:
	//Consructor
	Parameters(juce::AudioProcessor& processor); //reference to processor
	void PrepareToPlay(double sampleRate);
	void Update();
	void Smoothen();
	void Reset();

public:
	//ID created here
	inline static const juce::ParameterID TremoloTimeParamID{ "TremoloTime" };
	inline static const juce::ParameterID TremoloMixParamID{ "TremoloMix" };
	inline static const juce::ParameterID PanFreqParamID{ "PanFreq" };
	inline static const juce::ParameterID PanWidthParamID{ "PanWidth" };
	inline static const juce::ParameterID BypassParamID{ "Bypass" };
public:
	//Getter
	juce::AudioProcessorValueTreeState& GetAPVTS(); //get ref
	float GetTremolo() const;
	float GetTremoloMix() const;
	float GetPanFreq() const;
	float GetPanWidth() const;
	bool GetBypass() const;
private:
	juce::AudioProcessorValueTreeState m_APVTS;
	
	//TremoloTime
	juce::AudioParameterFloat* m_TremoloParam;
	juce::LinearSmoothedValue <float> m_TremoloSmoother;
	float m_Tremolo;

	//tremoloMix
	juce::AudioParameterFloat* m_TremoloMixParam;
	juce::LinearSmoothedValue <float> m_TremoloMixSmoother;
	float m_TremoloMix;

	//panFreq
	juce::AudioParameterFloat* m_PanFreqParam;
	juce::LinearSmoothedValue <float> m_PanFreqSmoother;
	float m_PanFreq;

	//panWidth
	juce::AudioParameterFloat* m_PanWidthParam;
	juce::LinearSmoothedValue <float> m_PanWidthSmoother;
	float m_PanWidth;

	//Bypass
	juce::AudioParameterBool* m_BypassParam;
	juce::LinearSmoothedValue <float> m_BypassSmoother;
	bool m_Bypass;
private:
	juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout(); //ALT ENTER definition
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Parameters) 
};
