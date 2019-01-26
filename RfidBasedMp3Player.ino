/*
 * -----------------------------------------------------------
 * <vvolkanunal@gmail.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff.
 * -----------------------------------------------------------
 * DFPlayer_Mini_Mp3 library -> https://github.com/DFRobot/DFPlayer-Mini-mp3
 * RFID library -> https://github.com/nlamprian/RFID
 * 
 * -----------------------------------------------------------
 */

#include <DFPlayer_Mini_Mp3.h>
#include <SPI.h>
#include <RFID.h>
#define SS_PIN 10 //SDA_PIN also
#define RST_PIN 9



RFID rfid(SS_PIN, RST_PIN); 


 typedef struct _RFID_TABLE
{
  uint8_t serNum0;
  uint8_t serNum1;
  uint8_t serNum2;
  uint8_t serNum3;
  uint8_t serNum4;
  uint16_t musicid;
} RFID_TABLE;

//Add id of Rfid cards inside table. "Debug 1", You can see from the serial screen.
static const RFID_TABLE PROGMEM table[] = 
{
  //serNum0  serNum1   serNum2    serNum3    serNum4  musicid
  { 86,     154,        38,        254,      20,        1 , },
  { 147,    85,        106,        30,       178,       2,  },
  { 150,    131,        52,        254,       223,      3,  },
  
};

void  setup()
{ 
  
  Serial.begin(9600);
  while(!Serial);
  SPI.begin(); 
  rfid.init();
  mp3_set_serial (Serial);  
  delay(10);  
  mp3_set_volume (15);
  pinMode(SS_PIN,OUTPUT);
 
}
void loop()
{
    if (rfid.isCard()) {
       if (rfid.readCardSerial()) {
               /*
                Serial.print("Cardnumber:");
                Serial.print(rfid.serNum[0],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[1],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[2],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[3],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[4],DEC);
                Serial.println(" ");       */
                
           }     
     for (unsigned i=0; i<sizeof(table)/sizeof(table[0]); ++i)
  {
    
    uint8_t _serNum0=pgm_read_dword(&table[i].serNum0);
    uint8_t _serNum1=pgm_read_dword(&table[i].serNum1);
    uint8_t _serNum2=pgm_read_dword(&table[i].serNum2);
    uint8_t _serNum3=pgm_read_dword(&table[i].serNum3);
    uint8_t _serNum4=pgm_read_dword(&table[i].serNum4);
    if(_serNum0==rfid.serNum[0] 
    && _serNum1==rfid.serNum[1] && 
    _serNum2==rfid.serNum[2] && 
    _serNum3==rfid.serNum[3] && 
    _serNum4==rfid.serNum[4])
    {
    uint16_t _musicid=pgm_read_dword(&table[i].musicid);
    
    mp3_play(_musicid);
  }    
  }
           
 }
    rfid.halt(); 
  }

   
 
