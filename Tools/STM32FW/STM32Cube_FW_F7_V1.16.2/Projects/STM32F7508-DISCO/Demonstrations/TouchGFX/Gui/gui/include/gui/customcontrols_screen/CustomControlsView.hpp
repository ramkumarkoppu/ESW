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
  #ifndef CUSTOMCONTROLS_VIEW_HPP
#define CUSTOMCONTROLS_VIEW_HPP

#include <gui_generated/customcontrols_screen/CustomControlsViewBase.hpp>
#include <gui/customcontrols_screen/CustomControlsPresenter.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <gui/customcontrols_screen/ThreeWayProgressBar.hpp>
#include <gui/customcontrols_screen/CircularProgress.hpp>
#include <gui/customcontrols_screen/DatePicker.hpp>
#include <gui/customcontrols_screen/Gauge.hpp>
#include <gui/customcontrols_screen/VerticalSlideMenu.hpp>

class CustomControlsView : public CustomControlsViewBase
{
public:
    CustomControlsView();
    virtual ~CustomControlsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void updateProcessorLoad(uint8_t mcuLoadValue);

    virtual void handleTickEvent();

    virtual void screenSaverMinorTick();

    virtual void menuUpClickedHandler();
    virtual void menuDownClickedHandler();

protected:
    VerticalSlideMenu slideMenu;
    Callback<CustomControlsView, const VerticalSlideMenu& > slideMenuElementSelectedCallback;
    void slideMenuElementSelectedHandler(const VerticalSlideMenu& menu);

    FadeAnimator<TextArea> statusMessage;

    ThreeWayProgressBar threeWayProgressBar;
    Callback<CustomControlsView, const ThreeWayProgressBar& > threeWayButtonPressedCallback;
    void threeWayButtonPressedHandler(const ThreeWayProgressBar& button);

    CircularProgress percentageBar;
    DatePicker datePicker;
    Gauge gauge;

    // Animation members
    enum AnimationState
    {
        ANIMATION_THREE_WAY_RUNNING,
        ANIMATION_GAUGE,
        NO_ANIMATION
    };

    AnimationState currentAnimationState;

    int animationCounter;
    int tickCounter;

    // ThreeWayProgressBar animation
    static const int NUMBER_OF_BARS = 3;
    AnimationState barAnimationState[NUMBER_OF_BARS];
    int animationDuration[NUMBER_OF_BARS];
    EasingEquation animationEquation[NUMBER_OF_BARS];

    AnimationState getAnimationState();
    EasingEquation getRandomEasingEquation();
    void startThreeWayProgressBarAnimation();
    void stopThreeWayProgressBarAnimation();

};

#endif // CUSTOMCONTROLS_VIEW_HPP
