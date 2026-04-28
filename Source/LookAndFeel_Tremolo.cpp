#include "LookAndFeel_Tremolo.h"

const juce::Typeface::Ptr FontsTremolo::m_Typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::ArchiveUkr_ttf, BinaryData::ArchiveUkr_ttfSize);


TremoloMixLookAndFeel::TremoloMixLookAndFeel()
{
    //color id
    setColour(juce::Slider::rotarySliderFillColourId, Colors::RotaryKnob::KnobLineFillColor);
    setColour(juce::Slider::rotarySliderOutlineColourId, Colors::RotaryKnob::KnobLineOutlineColor);
}




void TremoloMixLookAndFeel::drawRotarySlider(juce::Graphics& graphics, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    auto outline = slider.findColour(juce::Slider::rotarySliderOutlineColourId);
    auto fill = slider.findColour(juce::Slider::rotarySliderFillColourId);

    auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10);

    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = juce::jmin(8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;

    juce::Path backgroundArc;
    backgroundArc.addCentredArc(bounds.getCentreX(),
        bounds.getCentreY(),
        arcRadius,
        arcRadius,
        0.0f,
        rotaryStartAngle,
        rotaryEndAngle,
        true);

    graphics.setColour(outline);
    graphics.strokePath(backgroundArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    if (slider.isEnabled())
    {
        juce::Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            toAngle,
            true);

        graphics.setColour(fill);
        graphics.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }

    auto thumbWidth = lineW * 2.0f;
    juce::Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
        bounds.getCentreY() + arcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));

    graphics.setColour(slider.findColour(juce::Slider::thumbColourId));
    graphics.fillEllipse(juce::Rectangle<float>(thumbWidth, thumbWidth).withCentre(thumbPoint));
}

juce::Font TremoloMixLookAndFeel::getLabelFont(juce::Label& label)
{
    return FontsTremolo::GetFont(20.f);  //font size
}

juce::Font FontsTremolo::GetFont(float height)
{
    return juce::FontOptions(m_Typeface).withMetricsKind(juce::TypefaceMetricsKind::legacy).withHeight(height);
}