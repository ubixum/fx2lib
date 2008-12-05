#include <cstdio>
#include <cassert>

#include "fx2.h"


fx2::fx2():dev_handle(NULL) {

 int rv=libusb_init(&libusb_ctx);
 assert(!rv);

}

fx2::~fx2() {

 if (isopen()) close();
 
 libusb_exit(libusb_ctx);
}


void fx2::open(int vid,int pid) {
    dev_handle=libusb_open_device_with_vid_pid (libusb_ctx,vid,pid);
    assert(dev_handle);
    if (dev_handle) {
     int rv=libusb_claim_interface(dev_handle,0);
     assert(!rv);
     rv=libusb_set_interface_alt_setting(dev_handle,0,0);
     assert(!rv);
    }
}

void fx2::close() {
    assert(dev_handle);
    libusb_release_interface(dev_handle,0);
    libusb_close(dev_handle);
    dev_handle=NULL;
}


int fx2::do_usb_command(char* buf, int size, unsigned char type, unsigned char request, unsigned short value, unsigned short index, unsigned short length ) {
 assert(dev_handle);
 return libusb_control_transfer (
    dev_handle,
    type,
    request,
    value,
    index,
    (unsigned char*)buf,
    length,
    1000);
}



bool fx2::ep_bulk(char* buf, int size, unsigned char ep, int timeout) {
 assert(dev_handle);
 int transferred;
 int rv=libusb_bulk_transfer ( dev_handle, ep, (unsigned char*)buf, size, &transferred, timeout );

 if (!rv) 
 {
  printf ( "Transfer Succeeded. (Bytes: %d)\n", transferred );
  return true;
 }

 if (rv==LIBUSB_ERROR_TIMEOUT) {
    printf ( "Transfer Timeout.  %d bytes transferred.\n", transferred );
 } else if (rv<0) {
    printf ( "Transfer Error: %d\n", rv );
 }

 return false;

}