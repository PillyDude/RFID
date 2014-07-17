/***************************************  
 *  RFID_CardChecks
 *
 *  Testing whether using two MFRC522 RFID modules is possible.
 *
 *  Using .csv formating in serial monitor so to easily sort out duplicate UID of cards
 *
 */

#include <MFRC522.h> // .h and .cpp files from https://github.com/miguelbalboa/rfid
#include <SPI.h>

//== LED PINS ==
int pRED = 10;
int pGRN = 9;
int pBLU = 3;

//== LED colour ==
int red = 0;
int grn = 0;
int blu = 0;
int cSTP = 15;
/*
== SPI Pinouts ==
 MISO - pin D12
 MOSI - pin D11
 SCK  - pin D13
*/

// Module 1 pins
#define SS_PIN1  8
#define RST_PIN1  7

MFRC522 reader_1(SS_PIN1, RST_PIN1);	// Create MFRC522 instance.

void setup()
{
  pinMode(pRED, OUTPUT);
  pinMode(pGRN, OUTPUT);
  pinMode(pBLU, OUTPUT);
  
  // Init serial
  Serial.begin(9600);

  // Init SPI
  SPI.begin();

  // Init RFID module
  reader_1.PCD_Init();
  
  analogWrite(pRED, red);
  analogWrite(pGRN, red);
  analogWrite(pBLU, red);
}

void loop()
{
  RFID_Read(reader_1, 1);
  delay(100);
  RGBLED();
}

/*
 *  RFID_Read: checks if new UID has been recieved then displays
 *    over serial
 *
 *  INPUT  : MFRC522 (reader object)
 *           int (reader number)
 *  OUTPUT : void
 */
void RFID_Read(MFRC522 &mfrc522, int num)
{
    if(newUID(mfrc522))
  {
    displayUIDSerial(mfrc522, num);
  }
}

/*
 * Checks whether a new RFID card is present and then reads card
 *    obtaining the cards UID. If successful returns true, if fails
 *    at either stage returns false
 */
boolean newUID(MFRC522 &mfrc522)
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }

  // read from card
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    //Serial.println("No read!!");
    return false;
  }

  return true;
}



/*
 *  Displays each Byte of the UID as a HEX number setparted be ','.
 *    Each instance if the UID display is betwn two balnk line.
 */
void displayUIDSerial(MFRC522 &mfrc522, int reader_num)
{
//  Serial.print("Reader: ");
//  Serial.println(reader_num);
  
  // all cards received with module have 4 Byte UIDs that have been tested
  for(int i = 0; i <= mfrc522.uid.size; i++)
  {
    // newline at end of UID
    if(i == mfrc522.uid.size)
    {
      Serial.println();
    }
    else
    {
      //
      if(mfrc522.uid.uidByte[i] < 0x10)
      {
        Serial.print("0");
      }
      Serial.print(mfrc522.uid.uidByte[i]);
      Serial.print(",");
    }
  }
  
  mfrc522.PICC_HaltA();
}

/*
 *
 */
void RGBLED()
{
  if(red < 255 && grn == 0 && blu == 0)
  {
    red += cSTP;
  }
  else if(red == 255 && grn < 255 && blu == 0)
  {
    grn += cSTP;
  }
  else if(red > 0 && grn == 255 && blu == 0)
  {
    red -= cSTP;
  }
  else if(red ==0 && grn == 255 && blu < 255)
  {
    blu += cSTP;
  }
  else if(red == 0 && grn > 0 && blu == 255)
  {
    grn -= cSTP;
  }
  else if(red < 255 && grn == 0 && blu == 255)
  {
    red += cSTP;
  }
  else if(red == 255 && grn < 255 && blu == 255)
  {
    grn += cSTP;
  }
  else
  {
    red = 0;
    grn = 0;
    blu = 0;
  }
  
  analogWrite(pRED, red);
  analogWrite(pGRN, grn);
  analogWrite(pBLU, blu);
}











