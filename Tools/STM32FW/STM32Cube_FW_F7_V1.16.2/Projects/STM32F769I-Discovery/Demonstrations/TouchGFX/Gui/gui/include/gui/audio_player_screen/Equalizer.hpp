/**
  ******************************************************************************
  * This file is part of the TouchGFX 4.10.0 distribution.
  *
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
  

#ifndef EQUALIZER_HPP
#define EQUALIZER_HPP

#if defined(AUDIO_USE_SPIRIT_EQUALIZER)

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <gui/audio_player_screen/AudioPlayer.hpp>
#include <touchgfx/widgets/TextArea.hpp>

using namespace touchgfx;

class EqualizerSlider : public Slider
{
public:
    int16_t getIndicatorY() const
    {
        return indicator.getY();
    }
};

class LoudnessSlider : public Container
{
public:
    LoudnessSlider();
    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);
    void setValue(int16_t value);
    void setLoudnessChangedCallback(GenericCallback<const unsigned int>& callback)
    {
        this->callback = &callback;
    }
private:
    void update(int16_t x, int16_t y);
    const static int16_t maxAngle = 140;
    const static uint8_t size = 180;
    GenericCallback<const unsigned int>* callback;
    PainterRGB888 colorPainter;
    Circle dot;
};

class Equalizer : public Container
{
public:
    Equalizer();

    void setOnChangeCallback(GenericCallback<const AudioPlayer::EqualizerSetting, const int16_t>& callback)
    {
        this->callback = &callback;
    }
    //set the values - percentage
    void setSettings(int16_t _100Hz, int16_t _1kHz, int16_t _10kHz, int16_t _20kHz, int16_t loudness);

private:
    EqualizerSlider slider100Hz;
    EqualizerSlider slider1kHz;
    EqualizerSlider slider10kHz;
    EqualizerSlider slider20kHz;

    Image sliderValue;
    TextAreaWithOneWildcard sliderValueText;
    Unicode::UnicodeChar sliderValueBuffer[5];

    LoudnessSlider loudnessSlider;
    TextAreaWithOneWildcard loudnessValueText;
    Unicode::UnicodeChar loudnessValueBuffer[6];

    Image background;

    Callback<Equalizer, const Slider&, int > onDrag;
    void drag(const Slider&, int percentage);
    Callback<Equalizer, const Slider&, int > onStop;
    void stop(const Slider&, int percentage);
    Callback<Equalizer, const unsigned int> onLoudnessChanged;
    void loudnessChanged(const unsigned int percentage);

    GenericCallback<const AudioPlayer::EqualizerSetting, const int16_t>* callback;
};
#endif /* AUDIO_USE_SPIRIT_EQUALIZER */

#endif
