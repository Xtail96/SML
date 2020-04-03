void setupSerial(int baudRate)
{
	// setup communication via serial port
	Serial.begin(baudRate);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB
	}
}

void sendToSerial(String s)
{
  char buff[sizeof(s)];
  s.toCharArray(buff, sizeof(buff));
  Serial.write(buff, s.length());
}

void readFromSerial(char* buff)
{
	int size = Serial.available();
	for(int i = 0; i < size; i++)
	{
		buff[i] = char(Serial.read());
	}


	/*

	//String s(Serial.available());
	int size = Serial.available();
	char buf[sizeof(Serial.available())];
	int i = 0;
	while (Serial.available() > 0)
	{
		buf[i] = char(Serial.read());
		//sendToSerial(String(Serial.available()));
		sendToSerial(String(buf));
		//Serial.write(buf, size);
		
	}


	String s;
	for(int i = 0; i < size; i++)
	{
		s += String(buf[i]);
	}
	Serial.print(s.length());
	sendToSerial(s);
	return String(s);
	*/

  //String data = Serial.readString();
  //sendToSerial(data);
}
