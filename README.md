# Vertical Plotter
A V-plotter for whiteboards controlled by a WEMOS D1 ESP32.


### Components
For a vertical plotter two motors placed in the top left and right corner move around a pen using tooth belts. A servo motor is used to lift the pen from the surface. An ESP32 is used to control everything. To display debugging messages and to give status updates a simple I2C OLED display is used. The motors cannot be directly connected to the microcontoller as they would get damaged immediately. So one needs an addition motor driver board for each motor. 

- [Servo motor](https://www.amazon.de/meerkleurige-Dupont-stekker-Breadboard-Arduino/dp/B07FQBZ34J/): The simplest solution available
- [Display](https://www.amazon.de/AZDelivery-Display-Arduino-Raspberry-Gratis/dp/B07FYG8MZN/): state of the art
- [Stepper Motor](https://www.amazon.de/STEPPERONLINE-Schrittmotor-63-74oz-4-Draht-Stepper/dp/B07KZL4XCL) along with [Tooth Belt](https://www.amazon.de/ARCELI-Rasterma%C3%9F-Gummi-Zahnriemen-Aluminium-Zahnscheibe-3D-Drucker/dp/B07QH94G71/): Standard NEMA 17 Motor
- [Motor Driver Board](https://www.amazon.de/UEETEK-DRV8825-Schrittmotor-K%C3%BChlk%C3%B6rper-3D-Drucker/dp/B073VK4YN7/): This was used instead of an A4988 driver board because the DRV8825 can handle a higher current and appeared at the time of purchase as the choice of overall  higher quality.
- [D1 Mini ESP32](https://www.amazon.de/AZDelivery-Bluetooth-Internet-Entwicklungsboard-kompatibel/dp/B08BTRQNB3): Chosen because of its compact form-factor and the WiFi- **and** Bluetooth-module. I was using *fritzing* to create the schematics for the project and unfortunately, only the WEMOS D1 Mini was available as a proper microcontoller. Questions concerning the microcontroller can be asked in the *Issues-Tab*.

### Schematics and PCB
I decided to create a PCB for my application as it is easier to solder all the components together. I started using fritzing for the schematics with this result:
![schematics-fritzing](res/schematics_fritzing.png)










### Structure of this repo
The `/res`-folder contains images and several resources to learn about the components involved.  
The `/freecad`-folder contains 3D models as  `.stl` files. Included are models for the gondola, weight-mounts, motor mounts, a case for the control unit and mounts that go directly onto the whiteboard.  
Everything connected to the firmware is located in the `/firmware`-folder. This includes test scripts to examine if every part works as intended. The `config.h` file must be modified with the parameters of your specific case.


### Assembly



### Possible Future Improvements
##### PCB
- More labels
- Altered Capacitor and 12V plug connectors

#### 3D models
- Motor mount additions
- Move motor axle further away from drawing surface
- Design upper PCB case


### TODO:
- Tidy up repo
- Add pictures and guide
- Develop code
