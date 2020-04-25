#define SENSORS_COUNT 12
#define DEVICES_COUNT 3

// SENSORS_PACKAGE_SIZE = ceil(SENSORS_COUNT / 8)
#define SENSORS_PACKAGE_SIZE 2

// DEVICES_PACKAGE_SIZE = DEVICES_COUNT
#define DEVICES_PACKAGE_SIZE 3

// GENERAL_PACKAGE_SIZE = SENSORS_PACKAGE_SIZE + DEVICES_PACKAGE_SIZE
#define GENERAL_PACKAGE_SIZE 6

struct Sensor
{
  int pin;
  bool currentState;
  bool previousState;
  byte enableMask;
  byte resetMask;

  Sensor(int _pin, byte _enableMask, byte _resetMask)
  {
    this->pin = _pin;
    this->enableMask = _enableMask;
    this->resetMask = _resetMask;
    this->currentState = true;
    this->previousState = this->currentState;
  }

  Sensor()
  {
    this->pin = 0;
    this->enableMask = 0xff;
    this->resetMask = 0x00;
    this->currentState = true;
    this->previousState = this->currentState;
  }
};

struct Device
{
  int pin;
  bool enable;
  byte onMask = 0x01;
  byte offMask = 0x00;

  Device(int _pin = 13)
  {
    this->pin = _pin;
    this->enable = false;
  }
};


struct
{
  byte errorCode;
  byte sensors[SENSORS_PACKAGE_SIZE];
  byte devices[DEVICES_PACKAGE_SIZE];
} Package;


Sensor sensors[SENSORS_COUNT];
Device devices[DEVICES_COUNT];

// требуется ли отправить обновленное состояние
bool needToSend = false;

byte read_byte()
{
  byte incomingByte = 0;
  if(Serial.available() > 0)
  {
    incomingByte = Serial.read();
  }
  return incomingByte;
}

void write_byte(byte data)
{
  if (Serial.availableForWrite() > 0)
  {
    Serial.write(data);
  }
}

void pack_sensors()
{
  for (int i = 0; i < SENSORS_PACKAGE_SIZE; i++)
  {
     byte group = 0xff;

     int lowIndex = i * 8;
     int highIndex = min(lowIndex + 8, SENSORS_COUNT);

     for (int j = lowIndex; j < highIndex; j++)
     {
        if (sensors[j].currentState == false)
        {
          group &= sensors[j].enableMask;
        }
        else
        {
          group |= sensors[j].resetMask;
        }
     }

     Package.sensors[i] = group;
  }
}

void pack_devices()
{
  for (int i = 0; i < DEVICES_PACKAGE_SIZE; i++)
  {
    if (devices[i].enable)
    {
      Package.devices[i] = devices[i].onMask;
    }
    else
    {
      Package.devices[i] = devices[i].offMask;
    }
  }
}

void make_package()
{
  Package.errorCode = 0;
  pack_sensors();
  pack_devices();
}

void send_current_state()
{
  make_package();
  if (Serial.availableForWrite() > 0)
  {
    byte package[GENERAL_PACKAGE_SIZE];

    package[0] = Package.errorCode;

    int shift = 1;
    for (int i = 0; i < SENSORS_PACKAGE_SIZE; i++)
    {
      package[i+shift] = Package.sensors[i];
    }

    shift += SENSORS_PACKAGE_SIZE;
    for (int i = 0; i < DEVICES_PACKAGE_SIZE; i++)
    {
      package[i+shift] = Package.devices[i];
    }

    Serial.write(package, GENERAL_PACKAGE_SIZE);
  }
}

void setup() {
  // setup sensors
  // first group
  sensors[0] = Sensor(0, 0xfe, 0x01);
  sensors[1] = Sensor(1, 0xfd, 0x02);
  sensors[2] = Sensor(4, 0xfb, 0x04);
  sensors[3] = Sensor(5, 0xf7, 0x08);
  sensors[4] = Sensor(A2, 0xef, 0x10);
  sensors[5] = Sensor(A3, 0xdf, 0x20);
  sensors[6] = Sensor(3, 0xbf, 0x40);
  sensors[7] = Sensor(6, 0x7f, 0x80);

  // second group
  sensors[8] = Sensor(A4, 0xfe, 0x01);
  sensors[9] = Sensor(A5, 0xfd, 0x02);
  sensors[10] = Sensor(2, 0xfb, 0x04);
  sensors[11] = Sensor(7, 0xf7, 0x08);

  for (int i = 0; i < SENSORS_COUNT; i++)
  {
    pinMode(sensors[i].pin, INPUT);
  }

  // setup devices
  devices[0] = Device(13);
  devices[1] = Device(12);
  devices[2] = Device(11);

  for (int i = 0; i < DEVICES_COUNT; i++)
  {
    pinMode(devices[i].pin, OUTPUT);
  }

  // setup communication via serial port
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
}

void check_sensors()
{
  for (int i = 0; i < SENSORS_COUNT; i++)
  {
    sensors[i].currentState = digitalRead(sensors[i].pin);
    if(sensors[i].currentState != sensors[i].previousState)
    {
      needToSend = true;
      sensors[i].previousState = sensors[i].currentState;
    }
  }
}

void check_serial_port()
{
  byte commandKey = 0xff;
  byte indexByte = 0xff;
  byte paramsByte = 0xff;
  int bufferSize = Serial.available();
  if(bufferSize > 0)
  {
    byte message[3];
    for(int i = 0; i < bufferSize; i++)
    {
       message[i] = Serial.read();
    }

    commandKey = message[0];
    indexByte = message[1];
    paramsByte = message[2];
    
    switch(commandKey)
    {
      case 0x00:
        // switch off
        needToSend = true;
        switch(indexByte)
        {
          case 0x00:
            devices[0].enable = false;
            break;
          case 0x01:
            devices[1].enable = false;
            break;
          case 0x02:
            devices[2].enable = false;
            break;
          default:
            break;
        }
        break;
      case 0x01:
        // switch on
        needToSend = true;
        switch(indexByte)
        {
          case 0x00:
            devices[0].enable = true;
            break;
          case 0x01:
            devices[1].enable = true;
            break;
          case 0x02:
            devices[2].enable = true;
            break;
          default:
            break;
        }
        break;
      case 0x02:
        // return current state
        needToSend = true;
        break;
      default:
        break;
    }
  }
}

void switch_devices()
{
  for (int i = 0; i < DEVICES_COUNT; i++)
  {
    if (devices[i].enable)
    {
      digitalWrite(devices[i].pin, HIGH);
    }
    else
    {
      digitalWrite(devices[i].pin, LOW);
    }
  }
}

void send_response()
{
  if(needToSend)
  {
    send_current_state();
  }
}

void loop() {
  needToSend = false;

  check_sensors();
  check_serial_port();
  switch_devices();
  send_response();
}
