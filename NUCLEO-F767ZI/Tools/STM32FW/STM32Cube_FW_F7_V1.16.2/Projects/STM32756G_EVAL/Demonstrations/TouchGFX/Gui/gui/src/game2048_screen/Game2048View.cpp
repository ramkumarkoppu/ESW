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
  


#include <gui/game2048_screen/Game2048View.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>

Game2048View::Game2048View() :
    DemoView(),
    moveCompletedCallback(this, &Game2048View::moveCompletedHandler),
    gameWonCallback(this, &Game2048View::gameWonHandler),
    gameLostCallback(this, &Game2048View::gameLostHandler),
    buttonPressedCallback(this, &Game2048View::buttonPressedHandler)
{
    background.setBitmap(Bitmap(BITMAP_GAME_2048_BACKGROUND_ID));
    background.setXY(0, 0);
    add(background);

    gotoMenuButton.setBitmaps(Bitmap(BITMAP_GAME_2048_MENU_BUTTON_ID), Bitmap(BITMAP_GAME_2048_MENU_BUTTON_PRESSED_ID));
    gotoMenuButton.setXY(569, 405);
    add(gotoMenuButton);

    gameBoard.setXY(0, 0);
    gameBoard.setMoveCompletedCallback(moveCompletedCallback);
    gameBoard.setGameWonCallback(gameWonCallback);
    gameBoard.setGameLostCallback(gameLostCallback);
    add(gameBoard);

    currentScore = 0;

    scoreTxt.setWildcard(scoreTxtbuf);
    scoreTxt.setTypedText(TypedText(T_2048_SCORE));
    scoreTxt.setPosition(480, 64 - scoreTxt.getTypedText().getFont()->getFontHeight(), 100, 25); //134, 25);
    scoreTxt.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    updateScoreText();
    add(scoreTxt);

    deltaScoreTxt.setWildcard(deltaScoreTxtbuf);
    deltaScoreTxt.setTypedText(TypedText(T_2048_SCORE_DELTA));
    deltaScoreTxt.setWidth(scoreTxt.getWidth());
    deltaScoreTxt.setHeight(scoreTxt.getHeight());
    deltaScoreTxt.setColor(Color::getColorFrom24BitRGB(0x28, 0x28, 0x28));
    deltaScoreTxt.setAlpha(0);
    add(deltaScoreTxt);

    newGameButton.setBitmaps(Bitmap(BITMAP_NEW_GAME_BUTTON_ID), Bitmap(BITMAP_NEW_GAME_BUTTON_PRESSED_ID));
    newGameButton.setXY(473, 86);
    newGameButton.setAction(buttonPressedCallback);
    add(newGameButton);

    autoPlayButton.setBitmaps(Bitmap(BITMAP_AUTO_PLAY_BUTTON_ID), Bitmap(BITMAP_AUTO_PLAY_BUTTON_PRESSED_ID));
    autoPlayButton.setXY(473, 160);
    autoPlayButton.setAction(buttonPressedCallback);
    add(autoPlayButton);

    howToPlayButton.setBitmaps(Bitmap(BITMAP_HOW_TO_PLAY_BUTTON_ID), Bitmap(BITMAP_HOW_TO_PLAY_BUTTON_PRESSED_ID));
    howToPlayButton.setXY(473, 234);
    howToPlayButton.setAction(buttonPressedCallback);
    add(howToPlayButton);

    mcuLoadTxt.setTypedText(TypedText(T_2048_MCU_LOAD_TEXT));
    mcuLoadTxt.setXY(480, 448 - mcuLoadTxt.getTypedText().getFont()->getFontHeight());
    mcuLoadTxt.resizeToCurrentText();
    mcuLoadValueTxt.setTypedText(TypedText(T_2048_MCU_LOAD_VALUE));
    mcuLoadValueTxt.setPosition(mcuLoadTxt.getRect().right(), mcuLoadTxt.getY(), 30, 14);
    add(mcuLoadTxt);
    add(mcuLoadValueTxt);

    endGameStatus.setBitmap(Bitmap(BITMAP_GAME_2048_YOU_WIN_ID));
    endGameStatus.setXY((gameBoard.getWidth() - endGameStatus.getWidth()) / 2, (gameBoard.getHeight() - endGameStatus.getHeight()) / 2);
    endGameStatus.setVisible(false);
    add(endGameStatus);

    overlay.setPosition(0, 0, getActiveDisplayWidth(), getActiveDisplayHeight());
    overlay.setColor(Color::getColorFrom24BitRGB(0x0, 0x0, 0x0));
    overlay.setAlpha(160);
    overlay.setTouchable(true);
    overlay.setVisible(false);
    add(overlay);

    popUp.setBitmap(Bitmap(BITMAP_HOW_TO_PLAY_BACKGROUND_ID));
    popUp.setVisible(false);
    add(popUp);

    howToPlayInstruction[0].setBitmap(Bitmap(BITMAP_HOW_TO_PLAY_00_ID));
    howToPlayInstruction[1].setBitmap(Bitmap(BITMAP_HOW_TO_PLAY_01_ID));
    howToPlayInstruction[2].setBitmap(Bitmap(BITMAP_HOW_TO_PLAY_02_ID));

    for (int i = 0; i < NUMBER_OF_INSTRUCTIONS; i++)
    {
        // Enlarge the instruction swipe area by placing it in the howToPlayInstructionExtraSpaceContainer
        howToPlayInstruction[i].setXY(60, 0);
        howToPlayInstructionExtraSpaceContainer[i].add(howToPlayInstruction[i]);
        howToPlayInstructionExtraSpaceContainer[i].setPosition(0, 0, 60 + howToPlayInstruction[i].getWidth() + 60, 340);
        howToPlayInstructionContainer.add(howToPlayInstructionExtraSpaceContainer[i]);
    }
    howToPlayInstructionContainer.setXY((getActiveDisplayWidth() - howToPlayInstructionContainer.getWidth()) / 2, (getActiveDisplayHeight() - howToPlayInstructionContainer.getHeight()) / 2);
    howToPlayInstructionContainer.setDotIndicatorBitmaps(Bitmap(BITMAP_GAME_2048_DOT_OFF_ID), Bitmap(BITMAP_GAME_2048_DOT_ON_ID));
    howToPlayInstructionContainer.setDotIndicatorXYWithCenteredX(howToPlayInstructionContainer.getWidth() / 2, howToPlayInstructionContainer.getHeight() - 16);
    howToPlayInstructionContainer.setSwipeCutoff(80);
    howToPlayInstructionContainer.setEndSwipeElasticWidth(30);
    howToPlayInstructionContainer.setVisible(false);
    add(howToPlayInstructionContainer);

    popUp.setXY((getActiveDisplayWidth() - popUp.getWidth()) / 2, (getActiveDisplayHeight() - popUp.getHeight()) / 2);

    closeHowToPlayButton.setBitmaps(Bitmap(BITMAP_HOW_TO_PLAY_CLOSE_BUTTON_ID), Bitmap(BITMAP_HOW_TO_PLAY_CLOSE_BUTTON_ID));
    closeHowToPlayButton.setXY(popUp.getAbsoluteRect().right() - closeHowToPlayButton.getWidth() - 20, popUp.getY() + 20);
    closeHowToPlayButton.setAction(buttonPressedCallback);
    closeHowToPlayButton.setVisible(false);
    add(closeHowToPlayButton);
}

Game2048View::~Game2048View()
{
}

void Game2048View::setupScreen()
{

}

void Game2048View::tearDownScreen()
{
}

void Game2048View::moveCompletedHandler(const GameBoard& gb)
{
    int scoreDifference = gb.getScore() - currentScore;
    currentScore = gb.getScore();
    updateScoreText();
    showDeltaScoreText(scoreDifference);
}


void Game2048View::gameWonHandler(const GameBoard& gb)
{
    endGameStatus.setBitmap(Bitmap(BITMAP_GAME_2048_YOU_WIN_ID));
    endGameStatus.setVisible(true);
    endGameStatus.invalidate();

    gameBoard.setTouchable(false);
    autoPlayButton.setTouchable(false);
    howToPlayButton.setTouchable(false);
}

void Game2048View::gameLostHandler(const GameBoard& gb)
{
    endGameStatus.setBitmap(Bitmap(BITMAP_GAME_2048_GAME_OVER_ID));
    endGameStatus.setVisible(true);
    endGameStatus.invalidate();

    gameBoard.setTouchable(false);
    autoPlayButton.setTouchable(false);
    howToPlayButton.setTouchable(false);
}

void Game2048View::updateScoreText()
{
    Unicode::snprintf(scoreTxtbuf, 10, "%d", currentScore);
    scoreTxt.invalidate();
}

void Game2048View::showDeltaScoreText(int deltaScore)
{
    if (deltaScore == 0)
    {
        return;
    }
    Unicode::snprintf(deltaScoreTxtbuf, 10, "%d", deltaScore);

    deltaScoreTxt.setAlpha(255);
    deltaScoreTxt.setXY(scoreTxt.getX() - 8, scoreTxt.getY() - 4);

    int duration = 26;
    deltaScoreTxt.startMoveAnimation(deltaScoreTxt.getX(), deltaScoreTxt.getY() - 24, duration);
    deltaScoreTxt.startFadeAnimation(0, duration, EasingEquations::cubicEaseIn);
    deltaScoreTxt.invalidate();
}

void Game2048View::buttonPressedHandler(const AbstractButton& button)
{
    if (!gameBoard.isTouchable())
    {
        // Game has either been lost or won
        if (&button == &newGameButton)
        {
            endGameStatus.setVisible(false);
            endGameStatus.invalidate();
            gameBoard.setTouchable(true);
            autoPlayButton.setTouchable(true);
            howToPlayButton.setTouchable(true);
            startNewGame();
        }
        else
        {
            return;
        }
    }

    if (&button == &newGameButton)
    {
        startNewGame();
    }
    else if (&button == &autoPlayButton)
    {
        gameBoard.setAutoPlay(autoPlayButton.getState());
    }
    else if (&button == &howToPlayButton)
    {
        howToPlayInstructionContainer.setSelectedScreen(0);
        showHowToPlayPopUp(true);
    }
    else if (&button == &closeHowToPlayButton)
    {
        showHowToPlayPopUp(false);
    }
}

void Game2048View::showHowToPlayPopUp(bool visible)
{
    overlay.setVisible(visible);
    popUp.setVisible(visible);
    howToPlayInstructionContainer.setVisible(visible);
    closeHowToPlayButton.setVisible(visible);
    overlay.invalidate();
}

void Game2048View::startNewGame()
{
    gameBoard.initiateNewGame();
    currentScore = 0;
    updateScoreText();
}

void Game2048View::screenSaverMinorTick()
{
    if (popUp.isVisible())
    {
        showHowToPlayPopUp(false);
    }

    if (endGameStatus.isVisible())
    {
        buttonPressedHandler(newGameButton);
    }

    if (!gameBoard.getAutoPlay())
    {
        gameBoard.setAutoPlay(true);
    }
}
