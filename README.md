# eFlow
ESP8266 Based Reflow Oven

For more information, go to: http://www.casler.org/wordpress/?p=124

I've converted this project to a platformio project.

Compile with
`cd source/v0.0.1 && platformio run -e esp12e`

Unit Testing is a workaround using doctest, not the native platformio testing. Run unit tests with
`cd source/v0.0.1 && platformio run -e native && .pioenvs/native/program`

