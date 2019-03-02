

#include <libopencm3/usb/usbstd.h>

const struct usb_device_descriptor devDescriptor = {
	.bLength = USB_DT_DEVICE_SIZE,
	.bDescriptorType = USB_DT_DEVICE,
	.bcdUSB = 0x0200,
	.bDeviceClass = 0,
	.bDeviceSubClass = 0,
	.bDeviceProtocol = 0,
	.bMaxPacketSize0 = 64,
	.idVendor = 0x0483,
	.idProduct = 0x5710,
	.bcdDevice = 0x0200,
	.iManufacturer = 1,
	.iProduct = 2,
	.iSerialNumber = 3,
	.bNumConfigurations = 1,
};

 const uint8_t hidReportDescriptor[] = {
	0x05, 0x01, /* USAGE_PAGE (Generic Desktop)         */
	0x09, 0x02, /* USAGE (Mouse)                        */
	0xa1, 0x01, /* COLLECTION (Application)             */
	0x09, 0x01, /*   USAGE (Pointer)                    */
	0xa1, 0x00, /*   COLLECTION (Physical)              */
	0x05, 0x09, /*     USAGE_PAGE (Button)              */
	0x19, 0x01, /*     USAGE_MINIMUM (Button 1)         */
	0x29, 0x05, /*     USAGE_MAXIMUM (Button 5)         */
	0x15, 0x00, /*     LOGICAL_MINIMUM (0)              */
	0x25, 0x01, /*     LOGICAL_MAXIMUM (1)              */
	0x95, 0x05, /*     REPORT_COUNT (5)                 */
	0x75, 0x01, /*     REPORT_SIZE (1)                  */
	0x81, 0x02, /*     INPUT (Data,Var,Abs)             */
	0x95, 0x01, /*     REPORT_COUNT (1)                 */
	0x75, 0x03, /*     REPORT_SIZE (3)                  */
	0x81, 0x01, /*     INPUT (Cnst,Ary,Abs)             */
	0x05, 0x01, /*     USAGE_PAGE (Generic Desktop)     */
	0x09, 0x30, /*     USAGE (X)                        */
	0x09, 0x31, /*     USAGE (Y)                        */
	0x16, 0x00, 0x80,/*LOGICAL_MINIMUM (-32768) 		*/
	0x26, 0xFF, 0x7F,/*LOGICAL_MAXIMUM (32767) 			*/
	0x75, 0x10, /*     REPORT_SIZE (16)                 */
	0x95, 0x02, /*     REPORT_COUNT (2)                 */
	0x81, 0x06, /*     INPUT (Data,Var,Rel)             */
	0x09, 0x38,	/*	   USAGE (Wheel)					*/
	0x15, 0x81,	/*	   LOGICAL_MINIMUM (-127)			*/
	0x25, 0x7F,	/*	   LOGICAL_MAXIMUM (127)			*/
	0x95, 0x01,	/*	   REPORT_COUNT (1)					*/
	0x75, 0x08,	/*	   REPORT_SIZE (8)					*/
	0x81, 0x06,	/*	   INPUT (Data, Var, Rel)			*/
	0xc0,       /*   END_COLLECTION                     */
	0xc0        /* END_COLLECTION                       */
};

const struct {
	struct usb_hid_desciptor hidDescriptor;
	struct {
		uint8_t 	reportDescriptorType;
		uint16_t	descriptorLength;
	} __attribute__((packed)) hidReport;
} __attribute__((packed)) // CONTINUE HERE!!

const char *usbStrings[] = {
	"Mushbie Technologies",
	"Dank Mouse",
	"DEMO",
};

const struct usb_endpoint_descriptor hidEndpoint = {
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bEndpointAddress = 0x81,
	.bmAttributes = USB_ENDPOINT_ATTR_INTERRUPT,
	.wMaxPacketSize = 16,
	.bInterval = 0x01,
};

const struct usb_interface_descriptor hid_iface = {
	.bLength = USB_DT_INTERFACE_SIZE,
	.bDescriptorType = USB_DT_INTERFACE,
	.bInterfaceNumber = 0,
	.bAlternateSetting = 0,
	.bNumEndpoints = 1,
	.bInterfaceClass = USB_CLASS_HID,
	.bInterfaceSubClass = 1, /* boot */
	.bInterfaceProtocol = 2, /* mouse */
	.iInterface = 0,

	.endpoint = &hidEndpoint,

	.extra = &hid_function,
	.extralen = sizeof(hid_function),
};