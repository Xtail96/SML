#include <ArduinoJson.h>
#include "serial_utils.h"

#define RECIEVE_BUFFER_SIZE 100

struct
{
public:
	char m_data[RECIEVE_BUFFER_SIZE];

	void init()
	{
		this->clear();
		setupSerial(9600);
	}

	void read()
	{
		readFromSerial(m_data);
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
} RECIEVE_BUFFER;