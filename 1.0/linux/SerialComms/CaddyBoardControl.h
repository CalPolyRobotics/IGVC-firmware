#include "SerialComms.hpp"


class CaddyBoardControl {

	public:
	
	COMM_STATUS initializeComms(char* portStr, int baud);
   ReturnPayload getResults() {return atmega.getResults();}

	int setFNR(char direction);
   int setAngle(int ang);
   int getFNR();
   int getAngle();
   int getSpeed();
   int getSonar(int sonar);
   int getSonarGroup(int group);
   int getSonarAll();
   int toggleMotorDriver();
   int getHallEffectTicks();
	
	int setFNRForward() {return setFNR(1);}
	int setFNRNeutral() {return setFNR(0);}
	int setFNRReverse() {return setFNR(2);}
   
   int steerCenter() {return setAngle(0);}


	private:

   int sendCommand(Packet *packet);

	SerialComms atmega;

};
