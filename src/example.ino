/* Buttons to USB Keyboard Example
   You must select Keyboard from the "Tools > USB Type" menu
   This example code is in the public domain.
*/

#include <Bounce.h>
#include <Adafruit_NeoPixel.h>
#include <Metro.h>
#include <avr/power.h>

#define PIN            17
#define NUMPIXELS      6

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Metro ledsMetro = Metro(500);

Bounce bounces[] = {
    Bounce(2, 10),
    Bounce(3, 10),
    Bounce(4, 10),
    Bounce(5, 10),
    Bounce(6, 10),
    Bounce(7, 10)
};

//Bounce button0 = Bounce(2, 10);
//Bounce button1 = Bounce(3, 10);  // 10 ms debounce time
//Bounce button2 = Bounce(4, 10);
//Bounce button3 = Bounce(5, 10);
//Bounce button4 = Bounce(6, 10);
//Bounce button5 = Bounce(7, 10);

int buttons[6] = {0, 0, 0, 0, 0, 0};
Metro animationMetro = Metro(100);
int buttonsToLed[6] = {0, 1, 2, 3, 4, 5};

void setup() {
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);

    pixels.begin();
}

void checkButtons() {
    for(int i = 0; i < 6; i++) {
        bounces[i].update();

        if (bounces[i].fallingEdge()) {
            buttons[i] = 1;

            Keyboard.print(i);
            Keyboard.println(" press");
        }
        if (bounces[i].risingEdge()) {
            buttons[i] = 2;

            Keyboard.print(i);
            Keyboard.println(" release");
        }
    }
}

void animateLeds() {
    for(int i = 0; i < 6; i++) {
        int led = buttonsToLed[i];

        if(buttons[i] == 0) {
            buttons[i] = -1;
            pixels.setPixelColor(led, pixels.Color(0, 150, 0));
        } else if(buttons[i] == 1) {   // pressed
            buttons[i] = 2;
            pixels.setPixelColor(led, pixels.Color(150, 0, 0));
        } else if (buttons[i] == 2) {
            buttons[i] = 3;
            pixels.setPixelColor(led, pixels.Color(0, 0, 150));
        }
    }

    pixels.show();
}

void loop() {
    checkButtons();

    if(animationMetro.check()) {
        animateLeds();
        animationMetro.reset();
    }
}