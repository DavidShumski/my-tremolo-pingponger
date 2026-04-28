#pragma once
#include <JuceHeader.h>
namespace Colors
{
	namespace RotaryKnob
	{
		static const juce::Colour KnobLineFillColor{ 60,120, 160 };
		static const juce::Colour KnobLineOutlineColor{ 40,40,40 }; 
	}
}
//Fonts
class Fonts {
public:
	Fonts() = delete;
	static juce::Font GetFont(float height = 16.f); 

private:
	static const juce::Typeface::Ptr m_Typeface;

};
//call this class in PanWidth.cpp
class PanWidthLookAndFeel : public juce::LookAndFeel_V4 //F12 to find and override func
{

public:
	PanWidthLookAndFeel(); //constructor
	//проверяет -если нет - создает, если существует- возвращает существующий SINGLETON
	static PanWidthLookAndFeel* Get()
	{
		static PanWidthLookAndFeel instance{};
		return &instance;
	}

	void drawRotarySlider(juce::Graphics& graphics, int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle,
		float rotaryEndAngle, juce::Slider& slider) override;

	juce::Font getLabelFont(juce::Label& label) override;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PanWidthLookAndFeel)
};
