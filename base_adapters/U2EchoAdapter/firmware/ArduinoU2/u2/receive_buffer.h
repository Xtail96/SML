#include <ArduinoJson.h>
#include "serial_utils.h"

#define RECIEVE_BUFFER_SIZE 100

struct
{
private:
	char m_data[RECIEVE_BUFFER_SIZE];
	
public:
	void init()
	{
		this->clear();
		setupSerial(9600);
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
		readFromSerial(m_data);
		Serial.write(this->m_data);

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