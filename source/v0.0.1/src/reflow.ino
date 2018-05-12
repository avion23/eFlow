uint16_t processTimer = 0;
uint16_t processReflowTimer = 0;
uint8_t processReflowInitTimer = 0;
uint8_t profileZone = 0;
double Kp_previous = 0, Ki_previous = 0, Kd_previous = 0;
uint8_t processAgressiveness = 15;
uint8_t processTempReached = 0;
uint8_t processTempHysteresis = 3;


void dispatchProcessPerSecond() {
}

void processGo(void) {


	processTimer = 0;
	processReflowInitTimer = 0;
	processReflowTimer = 0;
	profileZone = 0;

	memset(&reflowStats, 0, sizeof reflowStats);
	return;
}

void processStop(void) {

	Serial.println("Process Aborting ...");

	//if (processEnable == 2) {

	processTempReached = 0;
	Setpoint = 0;

	processTimer = 0;
	processReflowTimer = 0;
	processReflowInitTimer = 0;
	profileZone = 0;

	//}

}

