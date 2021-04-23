#include <cstdio>
#include <Windows.h>
#include <mmeapi.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fp2.h>


void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	switch (wMsg) {
	case MIM_OPEN:
		printf("wMsg=MIM_OPEN\n");
		break;
	case MIM_CLOSE:
		printf("wMsg=MIM_CLOSE\n");
		break;
	case MIM_DATA:

		
		//fprintf(stdout, "Data: %01x %01x %01x\r\n", b1_mask&dwParam1, (b2_mask & dwParam1)>>8, (b3_mask & dwParam1)>>16);

		//printf("wMsg=MIM_DATA, dwInstance=%08x, dwParam1=%08x, dwParam2=%08x\n", dwInstance, dwParam1, dwParam2);
		break;
	case MIM_LONGDATA:
		printf("wMsg=MIM_LONGDATA\n");
		break;
	case MIM_ERROR:
		printf("wMsg=MIM_ERROR\n");
		break;
	case MIM_LONGERROR:
		printf("wMsg=MIM_LONGERROR\n");
		break;
	case MIM_MOREDATA:
		printf("wMsg=MIM_MOREDATA\n");
		break;
	default:
		printf("wMsg = unknown\n");
		break;
	}
	return;
}

int main(int argc, char* argv[])
{
	/*std::vector<MidiDevice> devices = GetDevices();

	MidiDevice fp2_output, fp2_input;
	bool input_found = false;
	bool output_found = false;

	for each (MidiDevice mididev in devices)
	{
		fprintf(stdout, "Input Device? : %i\r\n    Device ID: %i\r\n    Name: %s\r\n", mididev.input_deivce, mididev.device_id, mididev.Name.c_str());
		if (mididev.Name == std::string("PreSonus FP2"))
		{
			if (mididev.input_deivce)
			{
				fp2_input = mididev;
				input_found = true;
			}
			else { fp2_output = mididev; output_found = true; }
		}
	}

	if (input_found==false || output_found==false)
	{
		fprintf(stderr, "PreSonus FP2 NOT FOUND\r\n");
		exit(0);
	}

	HMIDIIN hMidiDevice = NULL;
	HMIDIOUT hMidiDevice_out = NULL;
	UINT NumDeviceNum_out = 0;
	UINT NumDeviceNum = 0;
	MMRESULT rv;

	rv = midiInOpen(&hMidiDevice, fp2_input.device_id, (DWORD_PTR)(void*)MidiInProc, 0, CALLBACK_FUNCTION);
	midiInStart(hMidiDevice);

	rv = midiOutOpen(&hMidiDevice_out, fp2_output.device_id, 0, 0, CALLBACK_NULL);
	
	int slider_val = 0;
	int slider_max = 0x3FFF;
	int increment = 128;

	DWORD testa = 0x000000E0;
	DWORD tt = 0xFF << 16;
	DWORD testb = testa + (slider_max << 16);

	int pi = 0;
	int pi_max = 360 * 4;

	bool running = true;
	while (running)
	{
		Sleep(16);
		slider_val = 8192 + (sin(pi * (3.1415f / 180.0f))*8192);
		pi = pi + 64;
		if (pi == pi_max + 64) { pi = 0; }
		fprintf(stdout, "num:%i\r\n", slider_val);
		int low = (0x7F & slider_val);
		int high = (0x3F80 & slider_val)>>7;
		midiOutShortMsg(hMidiDevice_out, 0x000000E0 + (low<<8) + (high<<16));

	}

	return 0;*/

	Dispatcher dis = Dispatcher();
	bool found = dis.isDevicePresent();

	return 0;
}