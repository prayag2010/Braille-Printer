#include "character_map.h"
#include <SoftwareSerial.h>


#define charLimit 21


const int stepPinX = 3;
const int dirPinX = 6;

const int xLimitSW1 = 9;
const int xLimitSW2 = 10;

const int sol = A3;

const int stepPinY = 2;
const int dirPinY = 5;

const int enPin = 8;

boolean xDir = true;
boolean yDir = false;

int yCount = 0;
int steps = 0;

boolean solEn;
boolean goToStartBool = false;

String charBuffer;
int bufferLength = 0;
//zero indexed
int totalLines = 0;

boolean bufferReady = false;
boolean printCompleted = true;

SoftwareSerial soft(12, 13); //RX TX

void setup() {

	Serial.begin(115200);
	soft.begin(115200);

	// Sets the two pins as Outputs
	pinMode(stepPinX, OUTPUT);
	pinMode(dirPinX, OUTPUT);

	pinMode(xLimitSW1, INPUT_PULLUP);
	pinMode(xLimitSW2, INPUT_PULLUP);
	pinMode(sol, OUTPUT);
	digitalWrite(sol, LOW);

	pinMode(stepPinY, OUTPUT);
	pinMode(dirPinY, OUTPUT);

	pinMode(enPin, OUTPUT);
	digitalWrite(enPin, LOW);
}

void loop() {

	if (Serial.available() > 0) {
		char inputChar = (char)Serial.read();
		if (inputChar == '@') {
			charBuffer = "";
			bufferLength = 0;
			Serial.println("Character Buffer Cleared");
		}
		else if (inputChar == '!') {
			Serial.println("Received input is:");
			Serial.println(charBuffer);
			bufferReady = true;
			printCompleted = false;
			goToStartBool = false;

			totalLines = (int(bufferLength / 21)) - 1;  //-1 since 0 indexed
			if (bufferLength % 21 > 0)
				totalLines++;
			Serial.println("Total Lines:");
			Serial.println(totalLines);
			Serial.println("Buffer Length:");
			Serial.println(bufferLength);
		}
		else if (inputChar == ' ') {
			inputChar = 'z' + 1;
			charBuffer += inputChar;
			bufferLength++;
		}
		else if (inputChar == '#') {
			Serial.println("Current Buffer is:");
			Serial.println(charBuffer);
			Serial.println("Buffer Length is:");
			Serial.println(bufferLength);
		}
		else if (inputChar >= 'A' && inputChar <= 'Z') {
			inputChar += 32;
			charBuffer += inputChar;
			bufferLength++;
			Serial.println(charBuffer);
		}
		else if ((inputChar >= 'a' && inputChar <= 'z') || inputChar == ' ') {
			charBuffer += inputChar;
			bufferLength++;
			Serial.println(charBuffer);
		}
		else {
			inputChar = 'z' + 1;
			charBuffer += inputChar;
			bufferLength++;
		}
	}

	if (soft.available() > 0) {
		Serial.println("Input from Software Serial");
		char inputChar = (char)soft.read();
		if (inputChar == '@') {
			charBuffer = "";
			bufferLength = 0;
			Serial.println("Character Buffer Cleared");
		}
		else if (inputChar == '!') {
			Serial.println("Received input is:");
			Serial.println(charBuffer);
			bufferReady = true;
			printCompleted = false;
			goToStartBool = false;

			totalLines = (int(bufferLength / 21)) - 1;  //-1 since 0 indexed
			if (bufferLength % 21 > 0)
				totalLines++;
			Serial.println("Total Lines:");
			Serial.println(totalLines);
			Serial.println("Buffer Length:");
			Serial.println(bufferLength);
		}
		else if (inputChar == ' ') {
			inputChar = 'z' + 1;
			charBuffer += inputChar;
			bufferLength++;
		}
		else if (inputChar == '#') {
			Serial.println("Current Buffer is:");
			Serial.println(charBuffer);
			Serial.println("Buffer Length is:");
			Serial.println(bufferLength);
		}
		else if ((inputChar >= 'a' && inputChar <= 'z') || inputChar == ' ') {
			charBuffer += inputChar;
			bufferLength++;
			Serial.println(charBuffer);
		}
		else {
			inputChar = 'z' + 1;
			charBuffer += inputChar;
			bufferLength++;
		}
	}

	if (digitalRead(xLimitSW2)) {
		SW1();
	}

	if (digitalRead(xLimitSW1)) {
		SW2();
	}

	if (goToStartBool)
		goToStart();

	digitalWrite(dirPinX, xDir);
	digitalWrite(dirPinY, yDir);

	if (bufferReady) {
		for (int currentLine = 0; currentLine <= totalLines && !printCompleted; currentLine++) {
			goToStartBool = true;
			goToStart();
			Serial.print("Currently Printing Line Number: ");
			Serial.println(currentLine);
			for (int charRow = 0; charRow < 3 && !printCompleted; charRow++) {
				int charLineLimit;
				if (currentLine == totalLines) {
					charLineLimit = bufferLength - (charLimit * totalLines);
					Serial.println("Custom Char Limit is:");
					Serial.println(charLineLimit);
				}
				else {
					charLineLimit = charLimit;
					Serial.println("Using Max Char Limit");
				}
				for (int charIndex = 0; charIndex < charLineLimit && !printCompleted; charIndex++) {
					for (int charColumn = 0; charColumn < 2 && !printCompleted; charColumn++) {
						Serial.println(charIndex + (currentLine * charLimit));
						if ((charIndex + (currentLine * charLimit)) >= bufferLength && charRow == 2) {
							printCompleted = true;
							break;
						}
						if (character_map[charBuffer[charIndex + (currentLine * charLimit)] - 'a'][charRow][charColumn]) {
							emboss();
						}
						moveX(10);
					}
					moveX(11);
				}
				moveY(10);
				goToStartBool = true;
				goToStart();
				digitalWrite(dirPinX, xDir);
			}
			moveY(20);

		}
		Serial.println("Printing Done!!!!");
		bufferReady = false;
	}
}

void SW1(void)
{
	solEn = false;
	xDir = false;
	digitalWrite(dirPinX, xDir);
	digitalWrite(dirPinY, yDir);
	xForSmall();
	Serial.println(steps);
	steps = 0;
	// Serial.println("SWITCH 2");
	yFor();
	yCount = 0;
}

void SW2(void)
{
	solEn = true;
	xDir = true;
	digitalWrite(dirPinX, xDir);
	digitalWrite(dirPinY, yDir);
	xFor();
	Serial.println(steps);
	steps = 0;
	// Serial.println("SWITCH 1");
	yCount = 0;
}

void goToStart(void)
{
	while (goToStartBool) {
		xDir = false;
		digitalWrite(dirPinX, xDir);
		stepDirX();
		delay(3);
		if (digitalRead(xLimitSW1)) {
			goToStartBool = false;
			// Serial.println("Printhead at starting position");
			xDir = true;
			if (digitalRead(xLimitSW2)) {
				SW1();
			}
			if (digitalRead(xLimitSW1)) {
				SW2();
			}
		}
	}
}


void yFor()
{
	for (int i = 0; i <= 4; i++) {
		stepDirY();
		delay(3);
	}
}

void xFor()
{
	for (int i = 0; i <= 60; i++) {
		stepDirX();
		delay(3);
	}
}

void xForSmall()
{
	for (int i = 0; i <= 20; i++) {
		stepDirX();
		delay(3);
	}
}

void moveX(int step)
{
	for (int i = 0; i < step; i++) {
		stepDirX();
		delay(3);
	}
}

void moveY(int step)
{
	for (int i = 0; i < step; i++) {
		stepDirY();
		delay(3);
	}
}


void stepDirX()
{
	digitalWrite(stepPinX, HIGH);
	delayMicroseconds(500);
	digitalWrite(stepPinX, LOW);
	delayMicroseconds(500);
}

void stepDirY()
{
	digitalWrite(stepPinY, HIGH);
	delayMicroseconds(500);
	digitalWrite(stepPinY, LOW);
	delayMicroseconds(500);
}

void emboss()
{
	delay(200);
	digitalWrite(sol, HIGH);
	delay(100);
	digitalWrite(sol, LOW);
	delay(100);
}