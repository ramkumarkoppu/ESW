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
  

#include <string.h>
#include <touchgfx/hal/HAL.hpp>

#include <gui/video_player_screen/VideoPlayerView.hpp>

#ifdef _MSC_VER
#define strcat strcat_s
#define strncpy strncpy_s
#endif

#ifndef SIMULATOR
#include <stm32f7xx_hal.h>
#include <stm32f7xx_hal_jpeg.h>

#include "hwjpeg_decode.h"

#include <cmsis_os.h>

extern char USBDISK_Drive[4];

struct HwJPEG_Context_s HwJPEG_Context;
#endif

VideoPlayerView::VideoPlayerView()
    : actionCallback(this, &VideoPlayerView::onAction),
      playlistCallback(this, &VideoPlayerView::onPlaylistClicked),
      playlistBackCallback(this, &VideoPlayerView::onPlaylistBack),
      movieCallback(this, &VideoPlayerView::onMovieClicked),
      progressCallback(this, &VideoPlayerView::onProgressBarDragged),
      animationCallback(this, &VideoPlayerView::onAnimationEnded),
      movieEndedCallback(this, &VideoPlayerView::onMovieEnded),
      largeButtonPressedCallback(this, &VideoPlayerView::largeButtonPressedHandler),
      folderWidget(*this),
      progressBar(), loopPlaylistIndex(PLAYLIST_LENGTH),
      playlistWidget(playlist, playlistCallback, playlistBackCallback),
      load(0), fps(0),
      state(INITIAL)
{
    fpsInfoBuf[0] = 0;

#ifdef SIMULATOR
    strncpy(currentFolder, "..\\..\\..\\", sizeof(currentFolder));
#else
    strncpy(currentFolder, USBDISK_Drive, sizeof(currentFolder));
#endif

    for (int i = 0; i < PLAYLIST_LENGTH; i++)
    {
        playlist[i].used = false;
    }

#ifdef SIMULATOR
    uint8_t* const tempBuffer = (uint8_t*)malloc(800 * 480 * 3);
    uint8_t* const movieBuffer = (uint8_t*)malloc(800 * 480 * 3);
#else
    movieBufferBitmapId = Bitmap::dynamicBitmapCreate(800, 480, Bitmap::RGB888);
    Bitmap movieBufferBmp = Bitmap(movieBufferBitmapId);
    uint8_t* const movieBuffer = const_cast<uint8_t*>(movieBufferBmp.getData());

    temporaryBufferBitmapId = Bitmap::dynamicBitmapCreate(800, 480, Bitmap::RGB888);
    Bitmap tempBufferBmp = Bitmap(temporaryBufferBitmapId);
    uint8_t* const tempBuffer = const_cast<uint8_t*>(tempBufferBmp.getData());
#endif
    //setup movie output
    moviePixelWidget.setPixelData(movieBuffer);
    moviePixelWidget.setBitmapFormat(Bitmap::RGB888);

    //movie touch
    moviePixelWidget.setClickAction(movieCallback);

    //setup movie readers
    mJPEGReaderMovie.setFrameBuffer(movieBuffer);
    mJPEGReaderMovie.setTemporaryFrameBuffer(tempBuffer);
    mJPEGReaderMovie.setLineBuffer(lineBuffer);
    mJPEGReaderMovie.setFileBuffer(fileBuffer, sizeof(fileBuffer));
    mJPEGReaderMovie.setOutputWidget(moviePixelWidget);
    mJPEGReaderMovie.setTimeBetweenTicks(16);
    mJPEGReaderMovie.setMovieEndedAction(movieEndedCallback);

    mJPEGReaderThumb.setTemporaryFrameBuffer(tempBuffer);
    mJPEGReaderThumb.setLineBuffer(lineBuffer);
    mJPEGReaderThumb.setFileBuffer(fileBuffer, sizeof(fileBuffer));

    progressBar.setCallback(progressCallback);
    progressBar.setProgress(0);
}

void VideoPlayerView::onProgressBarDragged(const uint32_t percent)
{
    mJPEGReaderMovie.pause();
    mJPEGReaderMovie.gotoFrame(percent * mJPEGReaderMovie.getNumberOfFrames() / 100);
}

void VideoPlayerView::setupScreen()
{
#ifndef SIMULATOR
    JPEG_InitDecode_HW(&HwJPEG_Context);
#endif

    //allocate dynamic bitmaps for playlist
    for (int i = 0; i < PLAYLIST_LENGTH; i++)
    {
        playlist[i].bmpId = Bitmap::dynamicBitmapCreate(190, 114, Bitmap::RGB888);
    }
    playlistWidget.refreshPlaylist();

    //Background for no video selected
    noMovieBackground.setBitmap(Bitmap(BITMAP_DEFAULT_BACKGROUND_ID));
    add(noMovieBackground);

    playlistLargeButton.setBitmaps(Bitmap(BITMAP_GRID_LARGE_ID), Bitmap(BITMAP_GRID_LARGE_PRESSED_ID));
    playlistLargeButton.setXY(290, 200);
    playlistLargeButton.setAction(largeButtonPressedCallback);
    add(playlistLargeButton);

    folderLargeButton.setBitmaps(Bitmap(BITMAP_FOLDER_LARGE_ID), Bitmap(BITMAP_FOLDER_LARGE_PRESSED_ID));
    folderLargeButton.setXY(playlistLargeButton.getRect().right() + 40, playlistLargeButton.getY() + 4);
    folderLargeButton.setAction(largeButtonPressedCallback);
    add(folderLargeButton);

    //PixelDataWidget for movie, fullscreen by default
    moviePixelWidget.setPosition(0, 0, 800, 480);
    moviePixelWidget.setVisible(false);
    add(moviePixelWidget);

    moviePlayButton.setBitmap(Bitmap(BITMAP_PLAY_OVERLAY_GRID_ID));
    moviePlayButton.setXY(400 - 38, 240 - 35);
    moviePlayButton.setVisible(false);
    add(moviePlayButton);

    //playlist is above movie
    playlistWidget.setVisible(false);
    playlistWidget.setPosition(0, 70, 800, 480 - topBar.getHeight());
    add(playlistWidget);

    folderWidget.setPlaylist(playlist, PLAYLIST_LENGTH);
    folderWidget.setXY(-430, 70);
    add(folderWidget);

    //TopBar
    topBar.setXY(0, 0 - topBar.getHeight());
    topBar.setText("Video Player");
    add(topBar);

    //BottomBar
    bottomBar.setXY(0, 480);
    bottomBar.setActionCallback(actionCallback);
    bottomBar.setMoveAnimationEndedAction(animationCallback);
    add(bottomBar);

    //progressBar
    progressBar.setXY(0, 480);
    progressBar.setVisible(false);
    add(progressBar);

    //add menu button to TopBar
    gotoMenuButton.setBitmaps(Bitmap(BITMAP_MENU_ICON_WHITE_ID), Bitmap(BITMAP_MENU_ICON_WHITE_ID));
    gotoMenuButton.setXY(0, 0);
    topBar.add(gotoMenuButton);

    //fps info on top
    fpsInfo.setPosition(800 - 100, 20, 100, 70 - 20);
    fpsInfo.setWildcard(fpsInfoBuf);
    fpsInfo.setTypedText(TypedText(T_MOVIE_LOAD_HEADLINE));
    fpsInfo.setColor(Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xFF));
    fpsInfo.setVisible(false);
    
    add(fpsInfo);

    loadRootFiles();

    HAL::getInstance()->setFrameRateCompensation(true);
}

void VideoPlayerView::tearDownScreen()
{
    HAL::getInstance()->lockFrameBuffer();
    HAL::getInstance()->unlockFrameBuffer();
    //HAL::getInstance()->setTouchSampleRate(2);

    mJPEGReaderMovie.closeFile();
    fileinput::deInit();

    //destroy dynamic bitmaps for playlist
    for (int i = 0; i < PLAYLIST_LENGTH; i++)
    {
        Bitmap::dynamicBitmapDelete(playlist[i].bmpId);
    }

    Bitmap::dynamicBitmapDelete(movieBufferBitmapId);
    Bitmap::dynamicBitmapDelete(temporaryBufferBitmapId);

    HAL::getInstance()->setFrameRateCompensation(false);

#ifndef SIMULATOR
    JPEG_StopDecode_HW(&HwJPEG_Context);
#endif
}

bool VideoPlayerView::addFile(uint32_t index)
{
    uint32_t pl_index = PLAYLIST_LENGTH;
    for (int i = 0; i < PLAYLIST_LENGTH; i++)
    {
        if (playlist[i].used == false)
        {
            pl_index = i;
            break;
        }
    }
    if (pl_index == PLAYLIST_LENGTH)
    {
        return false; //no space
    }

    //set to first free place in play list
    playlist[pl_index].filename[0] = 0; //cleared
    strncat(playlist[pl_index].filename, currentFolder, sizeof(playlist[pl_index].filename) - 1);
    strcat(playlist[pl_index].filename, fileinput::DirectorySeparator);
    strcat(playlist[pl_index].filename, dirlist[index].name);

    //load thumbnail from file
    fileinput::FileHdl f = fileinput::openFile(playlist[pl_index].filename);
    if (mJPEGReaderThumb.setAVIFile(f))
    {
        mJPEGReaderThumb.decodeThumbNail(Bitmap(playlist[pl_index].bmpId), 0);
        playlist[pl_index].used = true;
    }
    mJPEGReaderThumb.closeFile();

    playlistWidget.refreshPlaylist();

    return true;
}

void VideoPlayerView::selectNextPlaylistMovie()
{
    for (int i = 0; i<PLAYLIST_LENGTH; i++)
    {
        loopPlaylistIndex++;
        if (loopPlaylistIndex >= PLAYLIST_LENGTH)
        {
            loopPlaylistIndex = 0;
        }
        if (playlist[loopPlaylistIndex].used)
        {
            onPlaylistClicked(loopPlaylistIndex);
            break;
        }
    }
}

void VideoPlayerView::removeFile(uint32_t index)
{
    char fullname[FOLDERNAME_LENGTH + FILENAME_LENGTH];
    strncpy(fullname, currentFolder, FOLDERNAME_LENGTH);
    strcat(fullname, fileinput::DirectorySeparator);
    strcat(fullname, dirlist[index].name);

    //find index
    uint32_t pl_index = PLAYLIST_LENGTH;
    for (int i = 0; i < PLAYLIST_LENGTH; i++)
    {
        if (playlist[i].used && strcmp(playlist[i].filename, fullname) == 0)
        {
            pl_index = i;
        }
    }

    for (int i = pl_index; i < PLAYLIST_LENGTH - 1; i++)
    {
        playlist[i] = playlist[i + 1];
    }
    //clear last
    playlist[PLAYLIST_LENGTH - 1].used = false;

    playlistWidget.refreshPlaylist();
}

void VideoPlayerView::folderSelected(uint32_t index)
{
    if (dirlist[index].isDirectory)
    {
        strcat(currentFolder, fileinput::DirectorySeparator);
        strcat(currentFolder, dirlist[index].name);
#ifdef SIMULATOR
        uint32_t n = fileinput::getDirectoryList(currentFolder, ".avi", dirlist, DIRLIST_LENGTH);
#else
        uint32_t n = fileinput::getDirectoryList(currentFolder, ".AVI", dirlist, DIRLIST_LENGTH);
#endif
        folderWidget.setupDirlist(currentFolder, dirlist, n);
    }
}

void VideoPlayerView::upPressed()
{
    char* pch = strrchr(currentFolder, fileinput::DirectorySeparator[0]);
    if (pch && (pch != currentFolder+2))
    {
        *pch = 0; //end string at delimiter
#ifdef SIMULATOR
        uint32_t n = fileinput::getDirectoryList(currentFolder, ".avi", dirlist, DIRLIST_LENGTH);
#else
        uint32_t n = fileinput::getDirectoryList(currentFolder, ".AVI", dirlist, DIRLIST_LENGTH);
#endif
        folderWidget.setupDirlist(currentFolder, dirlist, n);
    }
}

void VideoPlayerView::donePressed()
{
    showBars(BAR_FADEIN);
    folderWidget.moveTo(-400, 70);
    moviePixelWidget.setTouchable(true);
}

void VideoPlayerView::onMovieClicked(const PixelDataWidget&, const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::RELEASED)
    {
        if (state == PAUSED && !playlistWidget.isVisible())
        {
            showBars(BAR_FADEOUT);
            onAction(PLAY);
        }
    }
}

void VideoPlayerView::onAnimationEnded(const MoveAnimator<VideoBottomBar>& src)
{
    if (state == PLAYING)
    {
        topBar.setText(currentAviFileName);
        /* Both the software and h/w JPEG decoders render to the framebuffer directly */
        moviePixelWidget.setVisible(false/*!mJPEGReaderMovie.isHWDecodingEnabled()*/);
        moviePixelWidget.invalidate();
        noMovieBackground.setVisible(false);     
        playlistLargeButton.setVisible(false);
        folderLargeButton.setVisible(false);
        mJPEGReaderMovie.play();
    }
}

void VideoPlayerView::onAction(Action action)
{
    switch (action)
    {
    case HW_ON:
        mJPEGReaderMovie.setHWDecodingEnabled(true);
        break;
    case HW_OFF:
        mJPEGReaderMovie.setHWDecodingEnabled(false);        
        break;
    case REPEAT_ON:
        mJPEGReaderMovie.setRepeat(true);
        break;
    case REPEAT_OFF:
        mJPEGReaderMovie.setRepeat(false);
        break;
    case PLAY:
        state = PLAYING;
        moviePlayButton.invalidate();
        moviePlayButton.setVisible(false);
        fpsInfo.setVisible(true);
        showBars(BAR_FADEOUT);
        break;
    case PAUSE:
      {
        mJPEGReaderMovie.pause();
        moviePlayButton.setVisible(true);
        moviePlayButton.invalidate();
        moviePixelWidget.setVisible(true);
        moviePixelWidget.invalidate();
        Rect r(0, 0, 800, 480);
        HAL::lcd().copyFrameBufferRegionToMemory(r);
        state = PAUSED;
        showBars(BAR_FADEIN);
        break;
      }
    case REPEAT:
        break;
    case PLAYLIST:
        playlistWidget.setVisible(true);
        playlistWidget.invalidate();
        topBar.setText("PLAYLIST");
        showBars(BAR_TOP_ONLY);
        break;
    case PLAYLIST_BACK:
        break;
    case FOLDER:
        {
            moviePixelWidget.setTouchable(false);
#ifdef SIMULATOR
            uint32_t n = fileinput::getDirectoryList(currentFolder, ".avi", dirlist, DIRLIST_LENGTH);
#else
            uint32_t n = fileinput::getDirectoryList(currentFolder, ".AVI", dirlist, DIRLIST_LENGTH);
#endif
            folderWidget.setupDirlist(currentFolder, dirlist, n);
            folderWidget.moveTo(0, 70);
            showBars(BAR_TOP_ONLY);
            break;
        }
    default:
        assert(!"Unknown action!");
    }
}

void VideoPlayerView::onPlaylistClicked(const uint32_t index)
{
    mJPEGReaderMovie.closeFile();

    fileinput::FileHdl f = fileinput::openFile(playlist[index].filename);
    if (mJPEGReaderMovie.setAVIFile(f))
    {
        mJPEGReaderMovie.showFirstFrame();

        currentAviFileName = strrchr(playlist[index].filename, fileinput::DirectorySeparator[0])+1;    
        //configure progress
        progressBar.setMovieData(mJPEGReaderMovie.getNumberOfFrames(), mJPEGReaderMovie.getMsPerFrame());

        //remove playlist
        playlistWidget.invalidate();
        playlistWidget.setVisible(false);

        //show bottom bar
        progressBar.setVisible(true);
        showBars(BAR_SHOW_IMMEDIATE);
        onAction(PLAY);

        loopPlaylistIndex = index;
    }
}

void VideoPlayerView::onPlaylistBack(const AbstractButton&)
{
    //remove playlist
    playlistWidget.invalidate();
    playlistWidget.setVisible(false);
    topBar.setText(currentAviFileName);
    showBars(BAR_FADEIN);
    state = PAUSED;
}

void VideoPlayerView::handleTickEvent()
{
    Unicode::snprintf(fpsInfoBuf, FPS_TITLE_LENGTH, "%d", mJPEGReaderMovie.getFPS());
    fpsInfo.invalidate();
   
    switch (state)
    {
    case INITIAL:
        //move bars in
        topBar.startMoveAnimation(0, 0, 16, &EasingEquations::cubicEaseInOut);
        bottomBar.startMoveAnimation(0, 480 - bottomBar.getHeight(), 16, &EasingEquations::cubicEaseInOut);
        state = WAIT_PLAYLIST;
        break;
    case WAIT_PLAYLIST:
        playlistWidget.updateUI(); //animate back button
        break;
    case PAUSED:
        playlistWidget.updateUI(); //animate back button
        break;
    case PLAYING:
        progressBar.setProgress(mJPEGReaderMovie.getFrameNumber());
        break;
    }
    mJPEGReaderMovie.tick();
}

void VideoPlayerView::onMovieEnded()
{
    onAction(PAUSE);
    selectNextPlaylistMovie();
}

void VideoPlayerView::showBars(BAR_STATE show)
{
    switch (show)
    {
    case BAR_FADEIN:
        topBar.startMoveAnimation(0, 0, 16, &EasingEquations::cubicEaseInOut);
        progressBar.startMoveAnimation(0, 480 - bottomBar.getHeight() - progressBar.getHeight(), 16, &EasingEquations::cubicEaseInOut);
        bottomBar.startMoveAnimation(0, 480 - bottomBar.getHeight(), 16, &EasingEquations::cubicEaseInOut);
        break;
    case BAR_FADEOUT:
        topBar.startMoveAnimation(0, 0 - topBar.getHeight(), 16, &EasingEquations::cubicEaseInOut);
        progressBar.startMoveAnimation(0, 480, 16, &EasingEquations::cubicEaseInOut);
        bottomBar.startMoveAnimation(0, 480 + progressBar.getHeight(), 16, &EasingEquations::cubicEaseInOut);
        break;
    case BAR_SHOW_IMMEDIATE:
        topBar.moveTo(0, 0);
        progressBar.moveTo(0, 480 - bottomBar.getHeight() - progressBar.getHeight());
        bottomBar.moveTo(0, 480 - bottomBar.getHeight());
        break;
    case BAR_HIDE:
        topBar.moveTo(0, 0 - topBar.getHeight());
        progressBar.moveTo(0, 480);
        bottomBar.moveTo(0, 480);
        break;
    case BAR_TOP_ONLY:
        topBar.moveTo(0, 0);
        progressBar.moveTo(0, 480);
        bottomBar.moveTo(0, 480);
        break;
    }
}

void VideoPlayerView::loadRootFiles()
{
#ifdef SIMULATOR
    uint32_t n = fileinput::getDirectoryList(currentFolder, ".avi", dirlist, DIRLIST_LENGTH);
#else
    uint32_t n = fileinput::getDirectoryList(currentFolder, ".AVI", dirlist, DIRLIST_LENGTH);
#endif

    for (unsigned int i = 0; i < n; i++)
    {
        //load thumbnail from file
        if (dirlist[i].isDirectory == false)
        {
            addFile(i);
        }
    }
}

void VideoPlayerView::largeButtonPressedHandler(const AbstractButton& src)
{
    if (&src == &playlistLargeButton) 
    {
        onAction(PLAYLIST);
    }
    else if (&src == &folderLargeButton)
    {
        onAction(FOLDER);
    }

}

void VideoPlayerView::handleClickEvent(const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::RELEASED)
    {
        if (state == PLAYING)
        {
            showBars(BAR_FADEIN);
            onAction(PAUSE);
            focus = 0;
            return;
        }
    }
    Screen::handleClickEvent(evt);
}
