#pragma once
#include <JuceHeader.h>
namespace Colors
{
	namespace RotaryKnob
	{
		static const juce::Colour KnobLineFillColor{ 185,125,175 };
		static const juce::Colour KnobLineOutlineColor{ 40,40,40 };
	}
}
//Fonts
class FontsTremolo {
public:
	FontsTremolo() = delete;
	static juce::Font GetFont(float height = 16.f);

private:
	static const juce::Typeface::Ptr m_Typeface;

};
//call this class in TremoloMixSlider.cpp
class TremoloMixLookAndFeel : public juce::LookAndFeel_V4 
{

public:
	TremoloMixLookAndFeel();
	static TremoloMixLookAndFeel* Get()
	{
		static TremoloMixLookAndFeel instance{};
		return &instance;
	}

	void drawRotarySlider(juce::Graphics& graphics, int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle,
		float rotaryEndAngle, juce::Slider& slider) override;

	juce::Font getLabelFont(juce::Label& label) override;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TremoloMixLookAndFeel)
};
