
# Create a realtime LED audio waveform based on the pitch and volume with Arduino
### Watch the video (not really recommended doesn't explain coding or wiring but you will see the end result
The entire process was filmed here: https://youtu.be/lU1GVVU9gLU

## Requirements
- WS2812B LED strip: https://goo.gl/YoFYP5
- Arduino: https://goo.gl/Ah6GGG
- 5v Power Source

## How it works

-Connect your WS2812b to a 5v power source (don't connect it directly to your Arduino, it's templting but anything over 800mAh will put your Arduino under stress).

-The center pin on the LED strip, green cable, will go to any of the digital out pins 3-7 on your arduino.

-Connect a Pre-amp audio source (like the + prong off an RCA connector coming from any audio soruce (3.5mm jack on a mobile phone or an output port from an audio mixer) to pin labeled A4 on your Arduino, it's important that it isn't amplified!)

-Connect your arduino to a power source (the USB connector is fine) and run a GND wire to the white cable on your LEDs, this way the arduino and LEDs can have shared ground if they don't share a power source, if both the strip and the Arduino are connected to the same power source this step may be optional.

## Note
Regulate the volume from your audio source (computer, phone or audio mixer) up and down to achieve desired effect
This for does not contain Devon's bug where red lights would randomly show up on the strip 8:15 on his video to see.
I thank Devon for giving me the ambition to make this project happen, I'm soon gonna port this to Adafruit_NeoPixel and I plan on adding Screensaver mode.
