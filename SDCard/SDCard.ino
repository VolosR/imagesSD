#include <TFT_eSPI.h> 
#include <LilyGo_AMOLED.h>
#include <Wire.h>
#include <SD.h>
#include "JpegFunc.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
LilyGo_Class amoled;

String name[150];
String tmp;
int numTabs=0;
int number=1;
File root;

static int jpegDrawCallback(JPEGDRAW *pDraw)
{
    spr.pushImage(pDraw->x, pDraw->y, pDraw->iWidth, pDraw->iHeight,pDraw->pPixels);
    return 1;
}

void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
 root = SD.open("/");
 root.rewindDirectory();
      
  while (true)
  {
    File entry =  root.openNextFile();
    if (! entry)
    {break;}
   
    tmp=entry.name();
    name[numTabs]="/"+tmp;
    Serial.println(entry.name());
    entry.close();
    numTabs++;
  }
}


void setup()
{
    Serial.begin(115200);
    amoled.begin();
    amoled.installSD();
    amoled.setBrightness(116);
    listDir(SD, "/", 0);
    spr.createSprite(600,450);
}


void loop()
{
  jpegDraw(name[number].c_str(), jpegDrawCallback, true, 0, 0, 600, 450);
  amoled.pushColors(0, 0, 600, 450, (uint16_t *)spr.getPointer());
  number++;
  if(number==numTabs) number=1;
  delay(6000);
}





















