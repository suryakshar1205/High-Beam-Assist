#include <Arduino.h>
#include <esp_camera.h>
// Define GPIO pins
#define LDR1_PIN 34       // ADC1_6 (GPIO34) for LDR1
#define LDR2_PIN 35       // ADC1_7 (GPIO35) for LDR2
#define LED_PIN 5         // GPIO5 for PWM control

// Define brightness levels
#define MAX_BRIGHTNESS 255   // High beam (Brightest)
#define LOW_BEAM_STAGE1 200  // Lowest low beam level
#define LOW_BEAM_STAGE2 150  // Medium low beam level
#define LOW_BEAM_STAGE3 100  // High low beam level
#define LOW_BEAM_STAGE4 50   // Highest low beam level
#define OFF_BRIGHTNESS 0     // Off

// Define LDR value thresholds for high and low beam stages
#define HIGH_BEAM_THRESHOLD 10   // Adjusted for high beam detection
#define LOW_BEAM_STAGE1_THRESHOLD 1600  // Stage 1 low beam start
#define LOW_BEAM_STAGE2_THRESHOLD 1400  // Stage 2 low beam start
#define LOW_BEAM_STAGE3_THRESHOLD 1200  // Stage 3 low beam start
#define LOW_BEAM_STAGE4_THRESHOLD 1000  // Stage 4 low beam start

// Smoothing factor for EMA (0 < alpha < 1)
float alpha = 0.1;

// Smoothed LDR values
float smoothedLDR1 = 0;
float smoothedLDR2 = 0;

// LED PWM properties
#define LED_CHANNEL 0
#define LED_FREQUENCY 5000
#define LED_RESOLUTION 8

void setup() {
    Serial.begin(115200);

    // Set pin modes
    pinMode(LDR1_PIN, INPUT);
    pinMode(LDR2_PIN, INPUT);

    // Setup LED PWM properties
    ledcSetup(LED_CHANNEL, LED_FREQUENCY, LED_RESOLUTION);
    ledcAttachPin(LED_PIN, LED_CHANNEL);
    ledcWrite(LED_CHANNEL, MAX_BRIGHTNESS);  // Start with full brightness (high beam)
    Serial.println("Setup complete. LED set to full brightness.");
}

void loop() {
    // Read LDR values
    int ldr1Value = analogRead(LDR1_PIN);
    int ldr2Value = analogRead(LDR2_PIN);

    // Apply the smoothing function (EMA)
    smoothedLDR1 = (alpha * ldr1Value) + ((1 - alpha) * smoothedLDR1);
    smoothedLDR2 = (alpha * ldr2Value) + ((1 - alpha) * smoothedLDR2);

    // Calculate the average of the smoothed LDR values
    int averageLDRValue = (smoothedLDR1 + smoothedLDR2) / 2;

    // Debugging: Print smoothed LDR values and brightness levels to the serial monitor
    Serial.print("Smoothed LDR1: ");
    Serial.print(smoothedLDR1);
    Serial.print(" | Smoothed LDR2: ");
    Serial.println(smoothedLDR2);

    Serial.print("Combined Average LDR Value: ");
    Serial.println(averageLDRValue);

    // Determine LED brightness based on smoothed LDR values
    if (averageLDRValue > LOW_BEAM_STAGE1_THRESHOLD) {
        // Bright light detected, switch to low beam stage 1
        ledcWrite(LED_CHANNEL, LOW_BEAM_STAGE1);
        Serial.println("Bright light detected! Setting LED to low beam stage 1.");
    } else if (averageLDRValue > LOW_BEAM_STAGE2_THRESHOLD) {
        // Bright light detected, switch to low beam stage 2
        ledcWrite(LED_CHANNEL, LOW_BEAM_STAGE2);
        Serial.println("Bright light detected! Setting LED to low beam stage 2.");
    } else if (averageLDRValue > LOW_BEAM_STAGE3_THRESHOLD) {
        // Bright light detected, switch to low beam stage 3
        ledcWrite(LED_CHANNEL, LOW_BEAM_STAGE3);
        Serial.println("Bright light detected! Setting LED to low beam stage 3.");
    } else if (averageLDRValue > LOW_BEAM_STAGE4_THRESHOLD) {
        // Bright light detected, switch to low beam stage 4
        ledcWrite(LED_CHANNEL, LOW_BEAM_STAGE4);
        Serial.println("Bright light detected! Setting LED to low beam stage 4.");
    } else if (averageLDRValue < HIGH_BEAM_THRESHOLD) {
        // Low light detected, switch to high beam
        ledcWrite(LED_CHANNEL, MAX_BRIGHTNESS);
        Serial.println("Low brightness detected! Setting LED to high beam.");
    } else {
        // Light level is between thresholds, turn off the LED
        ledcWrite(LED_CHANNEL, OFF_BRIGHTNESS);
        Serial.println("Brightness level in range. LED is off.");
    }

    delay(100);  // Adjust the delay as needed
}

