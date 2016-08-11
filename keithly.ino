                   // GPIB Pin
                   //     Description
#define EOI  A5    // 05  End-or-Identify
#define DAV  A4    // 06  Data Valid
#define NRFD A3    // 07  Not ready for data
#define NDAC 12    // 08  Not data accepted
#define IFC  11    // 09  Interface clear
#define SRQ  A2    // 10  Service request
#define ATN  A1     // 11  Attention
#define REN  10     // 17  Remote enable

#define DIO1 2     // 01  Data IO 1 LSB
#define DIO2 3     // 02  Data IO 2
#define DIO3 4     // 03  Data IO 3
#define DIO4 5     // 04  Data IO 4
#define DIO5 6     // 13  Data IO 5
#define DIO6 7     // 14  Data IO 6
#define DIO7 8     // 15  Data IO 7
#define DIO8 9     // 16  Data IO 8 MSB

#define TIMEOUT 300000

/**
 * Sets up serial and correct pin modes
 */
void setup()
{
	Serial.begin(9600);

	pinMode(ATN, OUTPUT);
	digitalWrite(ATN, HIGH);
}

/**
 * Main program loop. Repeatedly reads a single byte.
 */
void loop()
{
	Serial.print(readByte());
}

/**
 * Negotiates the receipt of and receives a single byte from the GPIB bus
 * @return The byte
 */
char readByte()
{
	pinMode(NRFD, OUTPUT);
	pinMode(NDAC, OUTPUT);

	digitalWrite(NRFD, HIGH);
	digitalWrite(NDAC, LOW);

	waitUntil(DAV, LOW);
	digitalWrite(NRFD, LOW);

	char data = getData();

	digitalWrite(NDAC, HIGH);

	waitUntil(DAV, HIGH);
	digitalWrite(NDAC, LOW);

	return data;
}

/**
 * Waits until a port has a specific status
 * @param  port   The port number we are concerned with
 * @param  status The status (ie HIGH or LOW)
 * @return        false if we timeout
 */
bool waitUntil(int port, int status)
{
	unsigned long t = millis();
	while (digitalRead(port) != status)
	{
		if (millis() - t > TIMEOUT)
		{
			errorTimeout(port, status);
			return false;
		}
	}
	return true;
}

/**
 * Prints out a timeout error message and then halts program execution
 * @param port   The port the timeout occurred on
 * @param status The status we were waiting for
 */
void errorTimeout(int port, int status)
{
	Serial.print("Error timeout: ");
	Serial.print(port);
	Serial.print(" ");
	Serial.println(status);
	Serial.println("Restart microcontroller");

	while (true) {}
}

/**
 * Obtains the current byte on the data bus
 * @return The byte
 */
char getData()
{
	pinMode(DIO1, INPUT);
	pinMode(DIO2, INPUT);
	pinMode(DIO3, INPUT);
	pinMode(DIO4, INPUT);
	pinMode(DIO5, INPUT);
	pinMode(DIO6, INPUT);
	pinMode(DIO7, INPUT);
	pinMode(DIO8, INPUT);

	char dataA = 0;
	char dataB = 0;

	dataB = bitWrite(dataA, 0, digitalRead(DIO1));
	dataA = bitWrite(dataB, 1, digitalRead(DIO2));
	dataB = bitWrite(dataA, 2, digitalRead(DIO3));
	dataA = bitWrite(dataB, 3, digitalRead(DIO4));
	dataB = bitWrite(dataA, 4, digitalRead(DIO5));
	dataA = bitWrite(dataB, 5, digitalRead(DIO6));
	dataB = bitWrite(dataA, 6, digitalRead(DIO7));
	dataA = bitWrite(dataB, 7, digitalRead(DIO8));

	return ~dataA;
}
