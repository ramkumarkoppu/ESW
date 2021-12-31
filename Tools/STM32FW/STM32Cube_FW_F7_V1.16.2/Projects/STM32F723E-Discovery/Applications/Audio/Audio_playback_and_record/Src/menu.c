/**
  ******************************************************************************
  * @file    Audio/Audio_playback_and_record/Src/menu.c 
  * @author  MCD Application Team
  * @brief   This file implements Menu Functions
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "waveplayer.h"
#include "waverecorder.h" 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TOUCH_RECORD_XMIN       140
#define TOUCH_RECORD_XMAX       170
#define TOUCH_RECORD_YMIN       200
#define TOUCH_RECORD_YMAX       230

#define TOUCH_PLAYBACK_XMIN     60
#define TOUCH_PLAYBACK_XMAX     90
#define TOUCH_PLAYBACK_YMIN     200
#define TOUCH_PLAYBACK_YMAX     230

/* Private macro -------------------------------------------------------------*/
/* Global extern variables ---------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
AUDIO_DEMO_StateMachine     AudioDemo;
AUDIO_PLAYBACK_StateTypeDef AudioState;

TS_StateTypeDef  TS_State = {0};
/* Private function prototypes -----------------------------------------------*/
static void AUDIO_ChangeSelectMode(AUDIO_DEMO_SelectMode select_mode);
static void LCD_ClearTextZone(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Manages AUDIO Menu Process.
  * @param  None
  * @retval None
  */
void AUDIO_MenuProcess(void)
{
  AUDIO_ErrorTypeDef  status;
  TS_StateTypeDef  TS_State;
  uint8_t x,y;
  Point PlaybackLogoPoints[] = {{TOUCH_PLAYBACK_XMIN, TOUCH_PLAYBACK_YMIN},
                                {TOUCH_PLAYBACK_XMAX, (TOUCH_PLAYBACK_YMIN+TOUCH_PLAYBACK_YMAX)/2},
                                {TOUCH_PLAYBACK_XMIN, TOUCH_PLAYBACK_YMAX}};
  
  if(appli_state == APPLICATION_READY)
  { 
    switch(AudioDemo.state)
    {
    case AUDIO_DEMO_IDLE:
      
      AudioDemo.state = AUDIO_DEMO_WAIT;
      
      BSP_LCD_SetFont(&LCD_LOG_HEADER_FONT);
      BSP_LCD_ClearStringLine(9); /* Clear touch screen buttons dedicated zone */
      BSP_LCD_ClearStringLine(10);
      BSP_LCD_ClearStringLine(11);
      BSP_LCD_ClearStringLine(12);     
      BSP_LCD_ClearStringLine(13);
      BSP_LCD_ClearStringLine(14);
      BSP_LCD_ClearStringLine(15);
      BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
      BSP_LCD_FillPolygon(PlaybackLogoPoints, 3);                 /* Playback sign */
      BSP_LCD_FillCircle((TOUCH_RECORD_XMAX+TOUCH_RECORD_XMIN)/2, /* Record circle */
                         (TOUCH_RECORD_YMAX+TOUCH_RECORD_YMIN)/2,
                         (TOUCH_RECORD_XMAX-TOUCH_RECORD_XMIN)/2);
      BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
      BSP_LCD_SetFont(&LCD_LOG_TEXT_FONT);
      BSP_LCD_DisplayStringAtLine(14, (uint8_t *)"Use touch screen to enter playback");
      BSP_LCD_DisplayStringAtLine(15, (uint8_t *)"or record menu");
      break;    
      
    case AUDIO_DEMO_WAIT:
      
      BSP_TS_GetState(&TS_State);
      x=TouchScreen_Get_Calibrated_X(TS_State.touchX[0]);
      y=TouchScreen_Get_Calibrated_Y(TS_State.touchY[0]);
      if(TS_State.touchDetected == 1)
      {
        if ((x > (TOUCH_RECORD_XMIN-10)) && (x < (TOUCH_RECORD_XMAX+10)) &&
            (y > (TOUCH_RECORD_YMIN-10)) && (y < (TOUCH_RECORD_YMAX+10)))
        {
          AudioDemo.state = AUDIO_DEMO_IN;
        }
        else if ((x > (TOUCH_PLAYBACK_XMIN-10)) && (x < (TOUCH_PLAYBACK_XMAX+10)) &&
                 (y > (TOUCH_PLAYBACK_YMIN-10)) && (y < (TOUCH_PLAYBACK_YMAX+10)))
        {
          AudioDemo.state = AUDIO_DEMO_PLAYBACK;
        }
        else
        {
          AudioDemo.state = AUDIO_DEMO_EXPLORE;
        }
        
        /* Wait for touch released */
        do
        {
          BSP_TS_GetState(&TS_State);
        }while(TS_State.touchDetected > 0);
      }
      break;
      
    case AUDIO_DEMO_EXPLORE: 
      if(appli_state == APPLICATION_READY)
      {
        if(AUDIO_ShowWavFiles() > 0)
        {
          LCD_ErrLog("There is no WAV file on the USB Key.\n");         
          AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU); 
          AudioDemo.state = AUDIO_DEMO_IDLE;
        }
        else
        {
          AudioDemo.state = AUDIO_DEMO_WAIT;
        }
      }
      else
      {
        AudioDemo.state = AUDIO_DEMO_WAIT;
      }
      break;
      
    case AUDIO_DEMO_PLAYBACK:
      if(appli_state == APPLICATION_READY)
      {
        if(AudioState == AUDIO_STATE_IDLE)
        {
          if(AUDIO_ShowWavFiles() > 0)
          {
            LCD_ErrLog("There is no WAV file on the USB Key.\n");         
            AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU); 
            AudioDemo.state = AUDIO_DEMO_IDLE;
          }
          else
          {
            /* Start Playing */
            AudioState = AUDIO_STATE_INIT;
          }
          /* Clear the LCD */
          LCD_ClearTextZone();
          
          if(AUDIO_PLAYER_Start(0) == AUDIO_ERROR_IO)
          {
            AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU); 
            AudioDemo.state = AUDIO_DEMO_IDLE;
          }
        }
        else /* Not idle */
        {
          if(AUDIO_PLAYER_Process() == AUDIO_ERROR_IO)
          {
            /* Clear the LCD */
            LCD_ClearTextZone();
            
            AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU);  
            AudioDemo.state = AUDIO_DEMO_IDLE;
          }
        }
      }
      else
      {
        AudioDemo.state = AUDIO_DEMO_WAIT;
      }
      break; 
      
    case AUDIO_DEMO_IN:
      if(appli_state == APPLICATION_READY)
      {
        if(AudioState == AUDIO_STATE_IDLE)
        {
          /* Start Playing */
          AudioState = AUDIO_STATE_INIT;
          
          /* Clear the LCD */
          LCD_ClearTextZone();

          /* Init storage */
          AUDIO_StorageInit();
          
          /* Configure the audio recorder: sampling frequency, bits-depth, number of channels */
          if(AUDIO_REC_Start() == AUDIO_ERROR_IO)
          {
            AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU); 
            AudioDemo.state = AUDIO_DEMO_IDLE;
          }
        }
        else /* Not idle */
        {
          status = AUDIO_REC_Process();
          if((status == AUDIO_ERROR_IO) || (status == AUDIO_ERROR_EOF))
          {
            /* Clear the LCD */
            LCD_ClearTextZone();
            
            AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU);  
            AudioDemo.state = AUDIO_DEMO_IDLE;
          }
        }
      }
      else
      {
        AudioDemo.state = AUDIO_DEMO_WAIT;
      }
      break;
      
    default:
      break;
    }
  }
  
  if(appli_state == APPLICATION_DISCONNECT)
  {
    appli_state = APPLICATION_IDLE;     
    AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU); 
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);    
  }
}

/*******************************************************************************
                            Static Functions
*******************************************************************************/

/**
  * @brief  Changes the selection mode.
  * @param  select_mode: Selection mode
  * @retval None
  */
static void AUDIO_ChangeSelectMode(AUDIO_DEMO_SelectMode select_mode)
{
  if(select_mode == AUDIO_SELECT_MENU)
  {
    LCD_LOG_UpdateDisplay(); 
    AudioDemo.state = AUDIO_DEMO_IDLE; 
  }
  else if(select_mode == AUDIO_PLAYBACK_CONTROL)
  {
    LCD_ClearTextZone();   
  }
}

/**
  * @brief  Clears the text zone.
  * @param  None
  * @retval None
  */
static void LCD_ClearTextZone(void)
{
  uint8_t i = 0;
  
  for(i= 0; i < 13; i++)
  {
    BSP_LCD_ClearStringLine(i + 3);
  }
}

