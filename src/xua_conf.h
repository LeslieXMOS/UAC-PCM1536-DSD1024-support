// Copyright 2012-2025 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

// Defines relating to device configuration and customisation.

#ifndef _XUA_CONF_H_
#define _XUA_CONF_H_

/* Audio Class version - Default is 2.0 */
#define AUDIO_CLASS        (2)

/*** Defines relating to channel counts ***/
/* Number of I2S channels to DACs*/
#define I2S_CHANS_DAC      (0)

/* Number of I2S channels from ADCs */
#define I2S_CHANS_ADC      (0)

/* Number of USB streaming channels - by default calculate by counting audio interfaces */
#define NUM_USB_CHAN_IN    (0)  /* Device to Host */
#define NUM_USB_CHAN_OUT   (2)  /* Host to Device */

/*** Defines relating to audio frequencies ***/
#define XUA_USE_SW_PLL      (0)

/* Master clock defines (in Hz) */
#define MCLK_441           (4*512*44100)   /* 44.1, 88.2 etc */
#define MCLK_48            (4*512*48000)   /* 48, 96 etc */

#define DEFAULT_FREQ       (192000)

/* Minimum sample frequency device runs at */
#define MIN_FREQ           (192000)

/* Maximum sample frequency device runs at */
#define MAX_FREQ           (1536000)

/* Enable HiBW ISO support */
#define XUD_USB_ISO_MAX_TXNS_PER_MICROFRAME (2)

/*** Defines relating to feature placement regarding tiles ***/
#define XUA_XUD_TILE_NUM           (1)
#define XUA_PLL_REF_TILE_NUM       (1)

#define XUA_AUDIO_IO_TILE_NUM      (1)
#define XUA_MIDI_TILE_NUM          (1)

/*** Defines relating to USB descriptor strings and ID's ***/
#define VENDOR_ID          (0x20B1) /* XMOS VID */
#define PID_AUDIO_2        (0x0018)
#define PID_AUDIO_1        (0x0017)

#ifndef DFU_PID
#if (AUDIO_CLASS == 1)
#define DFU_PID             (0xD000 + PID_AUDIO_1)
#else
#define DFU_PID             (0xD000 + PID_AUDIO_2)
#endif
#endif

#define PRODUCT_STR_A2     "HiBW XMOS (UAC2.0)"
#define PRODUCT_STR_A1     "HiBW XMOS (UAC1.0)"

/* Board power source - Default is bus-powered */
#ifndef XUA_POWERMODE
#define XUA_POWERMODE      XUA_POWERMODE_BUS
#endif

/* Enable/Disable example HID code - Default is off */
#ifndef HID_CONTROLS
#define HID_CONTROLS       (0)
#endif

#endif