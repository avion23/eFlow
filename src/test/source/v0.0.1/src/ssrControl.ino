#include <deltaSigma.hpp>

void dispatch10ms(void) {
	static deltaSigma d(100);	// convert percent to bits
	if (processEnable) { // If process is enabled, begin the reflow.
		if (d.update(Output / 10)) {
			digitalWrite(SSR_OUTPUT, true);
			delay(2);
		} else {
			digitalWrite(SSR_OUTPUT, false);
		}
	} else {
		digitalWrite(SSR_OUTPUT, false);
	}
}

