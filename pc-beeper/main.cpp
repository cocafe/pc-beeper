#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>

#include <Windows.h>
#include <windowsx.h>

#include <winring0.h>
#include <getopt.h>

#define BIT(nr)				(1 << (nr))

#define PIT_CHNL0_PORT			(0x40)
#define PIT_CHNL1_PORT			(0x41)
#define PIT_CHNL2_PORT			(0x42)

#define PIT_CMD_PORT			(0x43)

#define PIT_CMD_CHNL2			((0x02) << 6)
#define PIT_CMD_LMSB_RW			((0x03) << 4)
#define PIT_CMD_OUT_SQUARE_WAVE		((0x03) << 1)
#define PIT_CMD_COUNT_MODE_BIN		((0x00) << 0)

#define SYS_SPKR_PORT			(0x61)

#define SYS_SPKR_ENABLE			BIT(0)
#define SYS_SPKR_GATE2_ENABLE		BIT(1)

#define PCLK_8284_HZ			(1193182)	// 1193180

#define BEEP_FREQ_HZ			(440)
#define BEEP_DURATION			(1000)

static uint32_t beep_freq = BEEP_FREQ_HZ;
static uint32_t duration_ms = BEEP_DURATION;

void print_help(void)
{
	fprintf_s(stdout, "Usage:\n");
	fprintf_s(stdout, "    pc-beep.exe [-d <ms>] [-f <Hz>] [-? / -h]\n");
	fprintf_s(stdout, "Options:\n");
	fprintf_s(stdout, "    -d    Duration, in ms. Defualt: %d ms\n", BEEP_DURATION);
	fprintf_s(stdout, "    -f    Beep frequency, in Hz. Default: %d Hz\n", BEEP_FREQ_HZ);
}

int parse_opts(int argc, char *argv[])
{
	int c;

	opterr = 0;

	while ((c = getopt(argc, argv, "hd:f:")) != -1) {

		switch (c)
		{
			case 'h':
				return -1;

			case 'd':
				if (sscanf_s(optarg, "%u", &duration_ms) != 1) {
					printf_s("%s(): failed to parse for option -d\n", __func__);
					return -1;
				}

				break;

			case 'f':
				if (sscanf_s(optarg, "%u", &beep_freq) != 1) {
					printf_s("%s(): failed to parse for option -f\n", __func__);
					return -1;
				}

				break;

			case '?':
				if (optopt == 'd' || optopt == 'f')
					fprintf_s(stderr, "%s(): option -d & -f needs an arguemnt\n", __func__);
				else if (isprint(optopt))
					fprintf_s(stderr, "%s(): unknonw option -%c\n", __func__, optopt);
				else
					fprintf_s(stderr, "%s(): failed to parse character: \\x%x\n", __func__, optopt);

				return -1;

			default:
				break;
		}
	}

	return 0;
}

void beep(uint32_t freq)
{
	uint32_t div;
	uint8_t reg;

	div = PCLK_8284_HZ / freq;

	// Config CMD PORT
	reg = PIT_CMD_CHNL2 | PIT_CMD_LMSB_RW | PIT_CMD_OUT_SQUARE_WAVE | PIT_CMD_COUNT_MODE_BIN; //0xb6
	WriteIoPortByte(PIT_CMD_PORT, reg);

	// Send data to channel 2
	WriteIoPortByte(PIT_CHNL2_PORT, (uint8_t)(div & 0xff));
	WriteIoPortByte(PIT_CHNL2_PORT, (uint8_t)((div) >> 8));

	reg = ReadIoPortByte(SYS_SPKR_PORT);

	WriteIoPortByte(SYS_SPKR_PORT, reg | SYS_SPKR_ENABLE | SYS_SPKR_GATE2_ENABLE);
}

void beep_stop()
{
	uint8_t reg = ReadIoPortByte(SYS_SPKR_PORT) & ~(SYS_SPKR_ENABLE | SYS_SPKR_GATE2_ENABLE);

	WriteIoPortByte(SYS_SPKR_PORT, reg);
}

void sigint_handle(int sig)
{
	#define UNUSED_PARAM(sig)

	beep_stop();

	WinRing0_deinit();

	exit(0);
}

int main(int argc, char *argv[])
{
	if (parse_opts(argc, argv)) {
		print_help();
		return 0;
	}

	if (WinRing0_init()) {
		fprintf_s(stderr, "%s(): failed to init WinRing0 driver, may try with administrator permission again\n", __func__);

		return -1;
	}

	signal(SIGINT, sigint_handle);

	beep(beep_freq);
	
	Sleep(duration_ms);

	beep_stop();

	WinRing0_deinit();

	return 0;
}