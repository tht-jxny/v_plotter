# Vertical Plotter
A V-plotter for whiteboards controlled by a WEMOS D1 ESP32.


### Components
For a vertical plotter two motors placed in the top left and right corner move around a pen using tooth belts. A servo motor is used to lift the pen from the surface. An ESP32 is used to control everything. To display debugging messages and to give status updates a simple I2C OLED display is used. The motors cannot be directly connected to the microcontoller as they would get damaged immediately. So one needs an addition motor driver board for each motor. 

- [Servo motor](https://www.amazon.de/meerkleurige-Dupont-stekker-Breadboard-Arduino/dp/B07FQBZ34J/): The simplest solution available
- [Display](https://www.amazon.de/AZDelivery-Display-Arduino-Raspberry-Gratis/dp/B07FYG8MZN/): state of the art
- [Stepper Motor](https://www.amazon.de/STEPPERONLINE-Schrittmotor-63-74oz-4-Draht-Stepper/dp/B07KZL4XCL) along with [Tooth Belt](https://www.amazon.de/ARCELI-Rasterma%C3%9F-Gummi-Zahnriemen-Aluminium-Zahnscheibe-3D-Drucker/dp/B07QH94G71/): ... 
