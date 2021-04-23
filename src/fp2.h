#pragma once

#include <stdlib.h>
#include <functional>
#include <string>
#include <vector>
#include <Windows.h>

enum FP2_Button
{
	Prev=0x2E,
	Encoder=0x20,
	Next=0x2F,
	Link=0x05,
	Pan=0x2A,
	Channel=0x36,
	Scroll=0x38,
	Master=0x3A,
	Click=0x3B,
	Section=0x3C,
	Marker=0x3D,
	Read=0x4A,
	Write=0x4B,
	Touch=0x4D,
	Loop=0x56,
	Rewind=0x5B,
	FastForward=0x5C,
	Stop=0x5D,
	Play=0x5E,
	Record=0x5F,
	Footswitch=0x66
};

enum FP2_Command
{
	BUTTON=0x90,
	LED_RED=0x91,
	LED_GREEN=0x92,
	LED_BLUE=0x93,
	SLIDER_MOVE=0xE0,
	ENCODER_MOVE=0xB03C
};

enum FP2_LED_State
{
	OFF=0x00,
	ON=0x7F,
	FLASHING=0x01
};

enum FP2_Button_Event_Type
{
	Release=0x00,Pressed=0x7F
};

const typedef std::function<void(int new_val)> FP2_SliderMove;
const typedef std::function<void(FP2_Button btn, FP2_Button_Event_Type btn_event)> FP2_ButtonEvent;
const typedef std::function<void(int encoder_val)> FP2_EncoderMove;

struct MidiDevice
{
	std::string Name;
	int port_id;
	bool is_input;
};

//i think this is a forward declarion?
class FaderPort_2;

class MidiWorker
{
	int out_buffer_size = 64;
	DWORD* out_buffer = new DWORD[out_buffer_size];
	int out_buffer_len = 0;
	int out_buffer_index = 0;

	int in_buffer_size = 256;
	DWORD* in_buffer = new DWORD[in_buffer_size];
	int in_buffer_len = 0;
	int in_buffer_index = 0;

	HMIDIIN midi_in_h;
	HMIDIOUT midi_out_h;

	void start()
	{

	}

	void loop()
	{

	}
};

class Dispatcher
{
private:
	void GetMidiDevices();
	MidiDevice in_port, out_port;
	bool found_input, found_output, connected;
	HMIDIIN midiin_handle;
	HMIDIOUT midiout_handle;


public:
	bool isDevicePresent();
	FaderPort_2 connect();
	void disconnect();
};

class FaderPort_2
{
private:
	Dispatcher* _dispatcher;
	int last_known_slider_pos;

	std::vector<FP2_SliderMove*> sliderMove_cbs;
	std::vector<FP2_ButtonEvent*> buttonEvent_cbs;
	std::vector<FP2_EncoderMove*> encoderMove_cbs;

public:
	void internal_indata(DWORD data);

	FaderPort_2(Dispatcher* parent);

	void sliderMove_registerCallback(FP2_SliderMove* cb);
	void setSliderPos(int new_pos);
	//recommended not to use this as it only tells you the last value it received
	//the slider has to actually move and send an update via midi for the code to know here it is
	int getLastKnownSliderPos();

	void setLEDState(char button, FP2_LED_State new_state);
	/// <summary>
	/// Set LED Button Colour, note that the colours are 7 bit
	/// </summary>
	/// <param name="button">Button ID in hex</param>
	/// <param name="red">red led value in 7 bit</param>
	/// <param name="green">green led value in 7 bit</param>
	/// <param name="blue">blue led value in 7 bit</param>
	void setLEDColor(char button, char red, char green, char blue);

	void buttonEvent_registerCallback(FP2_ButtonEvent* cb);
	void encoderMove_registerCallback(FP2_EncoderMove* cb);

};

