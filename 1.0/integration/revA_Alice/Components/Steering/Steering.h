//Steering group

void initializeSteeringTimer(void);
void setSteeringPWMSpeed(int spd);
void setSteeringDirection(int dir);

//JUST SETS ANGLE TARGET. Actual angle changing is lower level
char setAngle(unsigned char* angleTarget);

//get the current angle of the steering system
char getAngle(unsigned char* sensorResponse);

//get the angle target. argument name is sensorResponse for the sake of consistancy
char getDesiredAngle(unsigned char* sensorResponse);

//change the PID controller
char changePID(char P, char I, char D);

//not sure what this does. Also not sure why upper and lower are separated
//but its in the specs so...
char setLimits(char upper, char lower);

void vTaskSteer(void* parameter);

