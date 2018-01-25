/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_


// MIDI
	#define USB_DESCRIPTOR_STRING L"KikGen MIDI factory"
	#define PRODUCT_STRING 				L"KloK MIDI Clock"

	/* Includes: */
	#include <avr/pgmspace.h>

 #include <LUFA/Drivers/USB/USB.h>


		/* Product-specific definitions: */
		#define ARDUINO_UNO_PID		0x0001
		#define ARDUINO_MEGA2560_PID	0x0010
		#define ARDUINO_USBSERIAL_PID	0x003B
		#define ARDUINO_MEGAADK_PID	0x003F
		#define ARDUINO_MEGA2560R3_PID	0x0042
		#define ARDUINO_UNOR3_PID	0x0043
		#define ARDUINO_MEGAADKR3_PID	0x0044
	/* Macros: */

    ////////////////////////////////////////// MIDI //////////////////////////////
		/** Endpoint address of the MIDI streaming data IN endpoint, for device-to-host data transfers. */
		#define MIDI_STREAM_IN_EPADDR       (ENDPOINT_DIR_IN  | 1)

		/** Endpoint address of the MIDI streaming data OUT endpoint, for host-to-device data transfers. */
		#define MIDI_STREAM_OUT_EPADDR      (ENDPOINT_DIR_OUT | 2)

		/** Endpoint size in bytes of the Audio isochronous streaming data IN and OUT endpoints. */
		#define MIDI_STREAM_EPSIZE          64

		/** Endpoint address of the CDC device-to-host notification IN endpoint. */
		#define CDC_NOTIFICATION_EPADDR       (ENDPOINT_DIR_IN  | 2)

    ///////////////////////////// CDC - Arduino ///////////////////////////////
		/** Endpoint address of the CDC device-to-host data IN endpoint. */
		#define CDC_TX_EPADDR                  (ENDPOINT_DIR_IN  | 3)

		/** Endpoint address of the CDC host-to-device data OUT endpoint. */
		#define CDC_RX_EPADDR                  (ENDPOINT_DIR_OUT | 4)

		/** Size in bytes of the CDC device-to-host notification IN endpoint. */
		#define CDC_NOTIFICATION_EPSIZE        8

		/** Size of the CDC data interface TX and RX data endpoint banks, in bytes. */
		#define CDC_TX_EPSIZE                64
		#define CDC_TX_BANK_SIZE 2
		#define CDC_RX_EPSIZE                32
		#define CDC_RX_BANK_SIZE 1

		/** Size in bytes of the CDC data IN and OUT endpoints. */
		#define CDC_TXRX_EPSIZE                64

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t     Config;

			// MIDI Audio Control Interface
			USB_Descriptor_Interface_t                Audio_ControlInterface;
			USB_Audio_Descriptor_Interface_AC_t       Audio_ControlInterface_SPC;

			// MIDI Audio Streaming Interface
			USB_Descriptor_Interface_t                Audio_StreamInterface;
			USB_MIDI_Descriptor_AudioInterface_AS_t   Audio_StreamInterface_SPC;
			USB_MIDI_Descriptor_InputJack_t           MIDI_In_Jack_Emb;
			USB_MIDI_Descriptor_InputJack_t           MIDI_In_Jack_Ext;
			USB_MIDI_Descriptor_OutputJack_t          MIDI_Out_Jack_Emb;
			USB_MIDI_Descriptor_OutputJack_t          MIDI_Out_Jack_Ext;
			USB_Audio_Descriptor_StreamEndpoint_Std_t MIDI_In_Jack_Endpoint;
			USB_MIDI_Descriptor_Jack_Endpoint_t       MIDI_In_Jack_Endpoint_SPC;
			USB_Audio_Descriptor_StreamEndpoint_Std_t MIDI_Out_Jack_Endpoint;
			USB_MIDI_Descriptor_Jack_Endpoint_t       MIDI_Out_Jack_Endpoint_SPC;
		} USB_Descriptor_Configuration_t;

		typedef struct
		{
			USB_Descriptor_Configuration_Header_t    Config;

			// CDC Command Interface
			USB_Descriptor_Interface_t               CDC_CCI_Interface;
			USB_CDC_Descriptor_FunctionalHeader_t    CDC_Functional_Header;
			USB_CDC_Descriptor_FunctionalACM_t       CDC_Functional_ACM;
			USB_CDC_Descriptor_FunctionalUnion_t     CDC_Functional_Union;
			USB_Descriptor_Endpoint_t                CDC_NotificationEndpoint;

			// CDC Data Interface
			USB_Descriptor_Interface_t               CDC_DCI_Interface;
			USB_Descriptor_Endpoint_t                CDC_DataOutEndpoint;
			USB_Descriptor_Endpoint_t                CDC_DataInEndpoint;
		} USB_Descriptor_ConfigurationCDC_t;

		/** Enum for the device interface descriptor IDs within the device. Each interface descriptor
		 *  should have a unique ID index associated with it, which can be used to refer to the
		 *  interface from other descriptors.
		 */
		enum InterfaceDescriptors_t
		{
			INTERFACE_ID_AudioControl = 0, /**< Audio control interface descriptor ID */
			INTERFACE_ID_AudioStream  = 1, /**< Audio stream interface descriptor ID */
		};

		enum InterfaceDescriptorsCDC_t
		{
			INTERFACE_ID_CDC_CCI = 0, /**< CDC CCI interface descriptor ID */
			INTERFACE_ID_CDC_DCI = 1, /**< CDC DCI interface descriptor ID */
		};

		/** Enum for the device string descriptor IDs within the device. Each string descriptor should
		 *  have a unique ID index associated with it, which can be used to refer to the string from
		 *  other descriptors.
		 */
		enum StringDescriptors_t
		{
			STRING_ID_Language     = 0, /**< Supported Languages string descriptor ID (must be zero) */
			STRING_ID_Manufacturer = 1, /**< Manufacturer string ID */
			STRING_ID_Product      = 2, /**< Product string ID */
			STRING_ID_Serial			 = 0xDC, /**< Serial number string ID */
		};

		/* Function Prototypes: */
			uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
			                                    const uint16_t wIndex,
			                                    const void** const DescriptorAddress)
			                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif
