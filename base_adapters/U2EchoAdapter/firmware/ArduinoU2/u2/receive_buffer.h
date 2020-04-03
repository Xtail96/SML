#include <ArduinoJson.h>

#define RECIEVE_BUFFER_SIZE 100

struct
{
private:
	char m_data[RECIEVE_BUFFER_SIZE];

	void setupSerial(int baudRate)
	{
		// setup communication via serial port
		Serial.begin(baudRate);
		while (!Serial) {
			; // wait for serial port to connect. Needed for native USB
		}
	}

	void readFromSerial(char* buff)
	{
		int size = Serial.available();
		for(int i = 0; i < size; i++)
		{
			buff[i] = char(Serial.read());
		}
	}
	
public:
	void init()
	{
		this->clear();
		this->setupSerial(9600);
	}

	void clear()
	{
		for(int i = 0; i < RECIEVE_BUFFER_SIZE; i++)
		{
			m_data[i] = 0;
		}
	}

	bool isEmpty()
	{
		bool empty = true;
		for(int i = 0; i < RECIEVE_BUFFER_SIZE; i++)
		{
			if(m_data[i] != 0)
			{
				empty = false;
				break;
			}
		}
		return empty;
	}

	JsonObject readAsJson()
	{
		this->clear();
		this->readFromSerial(m_data);

		if(this->isEmpty()) return JsonObject();
		DynamicJsonDocument doc(RECIEVE_BUFFER_SIZE);
		auto error = deserializeJson(doc, this->m_data);
		if (error)
		{
		    Serial.print(F("deserializeJson() failed with code "));
		    Serial.println(error.c_str());
		    this->clear();
		    return JsonObject();
		}
		
		JsonObject root;
		root = doc.as<JsonObject>();
		return root;
	}

} RECIEVE_BUFFER;