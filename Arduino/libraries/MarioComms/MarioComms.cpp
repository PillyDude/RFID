#include <MarioComms.h>
#include <Arduino.h>

///////////////////////////////////
//			Comms functions
///////////////////////////////////

// MarioComms::MarioComms(
			// int rsvLen,	// Reserve string buffer
			// int pRED,	// Red LED pin
			// int pGRN,	// Green LED pin
			// int pBLU	// Blue LED pin
			// )
// {
	// Msg.inputString.reserve(rsvLen);
	
	// msgReset(&Msg);
	
	// _pRED = pRED;
	// _pGRN = pGRN;
	// _pBLU = pBLU;
	
	// pinMode(_pRED, OUTPUT);
	// pinMode(_pGRN, OUTPUT);
	// pinMode(_pBLU, OUTPUT);
	
// }

// void MarioComms::MarioComms
// {
	// msg->len = 0;
	// msg->inputString = "";
// }

// void MarioComms::readmsg(MSG *msg)
// {
	// switch(msg->inputString->charAt(1)) {
		// case(Command(CMD_newID)):
			write to EEPROM devices serial ID
			// break;
		// case(Command(CMD_sendID)):
			read from EEPROM and send back
			// break;
		// case(Command(CMD_LEDColour)):
			[CMD,redByte,grnByte,bleByte,\n] => msg->len should == 5
			// if(msg->len == 5)
			// {
				// setLED(msg);
			// }else
			// {
				// Serial.Println("failed");
			// }
			// break;
		// default
	// }
	// msgReset(msg);
// }

// void MarioComms::collectMsg(MSG *msg)
// {
	// while(Serial.available())
	// {
		// char inChar = (char)Serial.read();
		
		// msg->inputString += inChar;
		// msg->len += 1;
		
		// if(inChar == '\n')
		// {
			// readmsg(msg)
		// }
	// }
// }

// void MarioComms::setLED(MSG *msg)
// {
	// analogWrite(_pRED, (byte)msg->inputString->charAt(2));
	// analogWrite(_pGRN, (byte)msg->inputString->charAt(3));
	// analogWrite(_pBLU, (byte)msg->inputString->charAt(4));
// }


















