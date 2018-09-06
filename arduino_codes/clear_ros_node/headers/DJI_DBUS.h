/*
 DJI DBUS data decoder library
 (c) S. Driussi 20141215
 Not for commercial use

 Work started from mikeshub Futaba library
 https://github.com/mikeshub/FUTABA_SBUS

 Refer to naza_dbus_decoder_wiring.jpg diagram for proper connection

 Modified by F.Cadelas to simplify funcionality to channel decoding
 */
#ifndef DJI_DBUS_H_
#define DJI_DBUS_H_

#include <Arduino.h>

#define DBUS_SIGNAL_OK          0x00
#define DBUS_SIGNAL_LOST        0x01
#define DBUS_SIGNAL_FAILSAFE    0x03
#define BAUDRATE 100000
#define RC_PORT Serial2

//! Custom defines to give name to the DJI DT7 Remote Control channels and values
#define MIN_CONTROL_ROD_VALUE  364.0
#define MAX_CONTROL_ROD_VALUE 1684.0

#define NEW_DATA_AVAILABLE 1
#define READY_TO_RECEIVE_NEW_DATA 0
#define SPEED_CONTROL_ROD 2
#define STEERING_CONTROL_ROD 0
#define EMERGENCY_SWITCH 6
#define NO_EMERGENCY 1024
#define OPERATIONAL_MODE_SWITCH 5
#define ROS_MODE 1541
#define RC_SAFETY_SYSTEM_DISABLED 1541
#define REARM_AND_HORN_CONTROL 4
#define REARM 364
#define ACTIVATE_HORN 1684

//#define ALL_CHANNELS

class DJI_DBUS;
typedef DJI_DBUS* DJI_DBUSPtr;

class DJI_DBUS
{
public:
  DJI_DBUS(HardwareSerial & serial) :
      _serial(serial)
  {
  }

  uint8_t sbusData[25];
  int16_t channels[18];
  uint8_t failsafe_status;
  int toChannels;

  void begin();
  int16_t Channel(uint8_t ch);
  uint8_t DigiChannel(uint8_t ch);
  void UpdateChannels(void);
  void FeedLine(void);
  void UpdateSignalState(void);

private:
  HardwareSerial & _serial;
  uint8_t inBuffer[25];
  int bufferIndex;
  uint8_t inData;
  int feedState;
};

#endif  //  DJI_DBUS_H_

