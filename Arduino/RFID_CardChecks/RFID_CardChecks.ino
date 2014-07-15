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

/*
== SPI Pinouts ==
 MISO - pin D12
 MOSI - pin D11
 SCK  - pin D13
*/

// Module 1 pins
#define SS_PIN1  8
#define RST_PIN1  7

// Module 2 pins
#define SS_PIN2  9
#define RST_PIN2  10

MFRC522 reader_1(SS_PIN1, RST_PIN1);	// Create MFRC522 instance.
MFRC522 reader_2(SS_PIN2, RST_PIN2);	// Create MFRC522 instance.

void setup()
{
  pinMode(SS_PIN1, OUTPUT);
  pinMode(RST_PIN1, OUTPUT);
  
  digitalWrite(SS_PIN1, HIGH);
  digitalWrite(RST_PIN1, HIGH);
  
  pinMode(SS_PIN1, OUTPUT);
  pinMode(RST_PIN1, OUTPUT);
  
  digitalWrite(SS_PIN1, HIGH);
  digitalWrite(RST_PIN1, HIGH);
  
  // Init serial
  Serial.begin(9600);

  // Init SPI
  SPI.begin();

  // Init RFID module
  reader_1.PCD_Init();
  reader_2.PCD_Init();
}

void loop()
{

  if(newUID(reader_1))
  {
    displayUIDSerial(reader_1, '1');
  }
  
   if(newUID(reader_2))
  {
    displayUIDSerial(reader_2, '2');
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
void displayUIDSerial(MFRC522 &mfrc522, char reader_num)
{
  Serial.print("Reader: ");
  Serial.println(reader_num);
  
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














