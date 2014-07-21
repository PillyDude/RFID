/***************************************  
 *  RFID_LED_comms
 ***************************************/

#include <MFRC522.h> // .h and .cpp files from https://github.com/miguelbalboa/rfid
#include <SPI.h>
#include <MarioComms.h>


//****************************
//== LED PINS ==
int red = 6;
int grn = 5;
int blu = 3;

//== LED colour ==
int cRED = 0;
int cGRN = 0;
int cBLU = 0;
//****************************

/*****************************
== SPI Pinouts ==
 MISO - pin D12
 MOSI - pin D11
 SCK  - pin D13
*/

// Module 1 pins
#define SS_PIN1  8
#define RST_PIN1  7

MFRC522 reader_1(SS_PIN1, RST_PIN1);	// Create MFRC522 instance.
//*****************************

//*****************************
//Serial input message string
MarioComms comms(50, red, grn, blu);

//*****************************

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(grn, OUTPUT);
  pinMode(blu, OUTPUT);
  
  // Init serial
  Serial.begin(9600);

  // Init SPI
  SPI.begin();

  // Init RFID module
  reader_1.PCD_Init();
}

void loop()
{
  RFID_Read(reader_1, 1);
}

void serialEvent()
{
  comms.collectMsg(&comms.Msg);
}


//=====================================================================
//                         user define functions
//=====================================================================
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
    //displayUIDSerial(mfrc522, num);
    //Serial.println(mfrc522.uid.size);
    comms.sendUID(mfrc522.uid.size, mfrc522.uid.uidByte);
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













