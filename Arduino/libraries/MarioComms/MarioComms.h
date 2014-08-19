/*
	MarioComms.h - Library  for use in communication between arduino devices as well as raspberry pi over
	a serial interface (through USB), in the JCURoboClub's Project-Mario.
*/

#include <Arduino.h>
#include <Serial.h>

class MarioComms
{
	public:
		/*
		*	Constants
		*/
		enum Command {
			CMD_newID		= 0x01,
			CMD_sendID		= 0x02,
			CMD_LEDColour	= 0x6C
		};
		
		enum Header {
			HDR_UID			= 'U',
		};
		
		/*
		*	Structures
		*/
		typedef struct {
			int len;
			String inputString;
		} MSG;
		
		/*
		*	Variables
		*/
		MSG Msg;
		
		/*
		*
		*/
		MarioComms(int rsvLen, int pRED, int pGRN, int pBLU);
		
		/*
		*	functions
		*/
		void msgReset(MSG *msg);
		void readMsg(MSG *msg);
		void collectMsg(MSG *msg);
		void setLED(MSG *msg);
		void sendUID(int size, byte uid[]);
		void writeID(MSG *msg);
		
	private:
		int _pRED;
		int _pGRN;
		int _pBLU;
	
};
