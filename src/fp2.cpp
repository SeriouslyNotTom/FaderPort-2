#include <fp2.h>
#include <cstdio>
#include <Windows.h>
#include <mmeapi.h>
#include <stdlib.h>
#include <string>
#include <vector>

void Dispatcher::GetMidiDevices()
{
	UINT numDevices;
	MIDIINCAPS in_caps;
	MIDIOUTCAPS out_caps;

	numDevices = midiInGetNumDevs();
	if (numDevices == 0)
	{
		found_input = false;
		found_output = false;
		return;
	}

	for (int i = 0; i < numDevices; i++)
	{
		midiInGetDevCaps(i, &in_caps, sizeof(MIDIINCAPS));
		if (std::string(in_caps.szPname) == std::string("PreSonus FP2"))
		{
			MidiDevice new_dev;
			new_dev.Name = std::string(in_caps.szPname);
			new_dev.port_id = i;
			new_dev.is_input = true;
			in_port = new_dev;
			found_input = true;
		}
	}

	numDevices = midiOutGetNumDevs();
	if (numDevices == 0)
	{
		found_input = false;
		found_output = false;
		return;
	}

	for (int i = 0; i < numDevices; i++)
	{
		midiOutGetDevCaps(i, &out_caps, sizeof(MIDIOUTCAPS));
		if (std::string(out_caps.szPname) == std::string("PreSonus FP2"))
		{
			MidiDevice new_dev;
			new_dev.Name = std::string(out_caps.szPname);
			new_dev.port_id = i;
			new_dev.is_input = false;
			out_port = new_dev;
			found_output = true;
		}
	}
}

FaderPort_2 Dispatcher::connect()
{

	FaderPort_2 fp2 = FaderPort_2(this);
	return fp2;
}

bool Dispatcher::isDevicePresent()
{
	if (found_input != true || found_output != true)
	{
		GetMidiDevices();
		if (found_input != true && found_output != true)
		{
			return false;
		}
	}
	else
	{
		if (found_input == true && found_output == true)
		{
			return true;
		}
	}
}