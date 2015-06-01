#include "ril_asn1.h"
#include <unistd.h>

#define  LOG_TAG  "gps_ril_Test"
#include <cutils/log.h>
#define  D(...)   LOGD(__VA_ARGS__)

static OsHandle ril = NULL;


BrcmLbs_Result DebuggingCallback_SendToNetwork(
    BrcmLbsRilAsn1_Protocol protocol, 
    const unsigned char *msg, 
    size_t size, 
    BrcmLbs_UserData userData)
{
    int i;
    D("%s: ENTER\n", __FUNCTION__);
    D("%s: Param1, protocol = %d\n", __FUNCTION__, protocol);
    D("%s: Param3, msg size = %d\n", __FUNCTION__, size);

    for (i=0; i<size; i++)
    {
        D("%s: msg[%d]= 0x%X\n", __FUNCTION__, i, msg[i]);
    }

    if (size == 2 && msg[0] == 8 && msg[1] == 0x10)
    {
        D("%s: TEST FAILED, 0810 == incorrect data\n",__FUNCTION__);
    }
    else
    {
        D("%s: TEST PASSED\n",__FUNCTION__);
    }

    return 0;
}



int main(int argc, char *argv[])
{
    int i=0;

    // not referenced:
    argc = argc;
    argv = argv;

    unsigned char msg[] = 
    {
        0x85, 0x18, 0x40, 0x40, 0x84, 0x00, 0x00, 0x8A, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0, 0x20,
        0x14, 0xA0, 0x20, 0x10, 0x1E, 0xA0, 0x69, 0x80, 0x00, 0x80, 0x00, 0xD1, 0xDE, 0x5D, 0x71, 0x80, 0x00, 0x04, 0xDD, 0x70,
        0x00, 0x80, 0x00, 0xA1, 0x0C, 0xE6, 0x00, 0x80, 0x52, 0x2A, 0x00, 0x03, 0xDB, 0xE5, 0xC0, 0x62, 0x00, 0x02, 0x9B, 0xF1,
        0x19, 0x9A, 0x00, 0x03, 0x1D, 0x43, 0xBC, 0x01, 0xFE, 0xB0, 0x02, 0x00, 0x01, 0x42, 0x00, 0x00, 0x45, 0x55, 0x55, 0x55,
        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x50, 0x10, 0x0A, 0x50, 0x10, 0x60, 0x0D, 0x8A, 0x76, 0x40, 0x00, 0x40, 0x00,
        0x2B, 0xBA, 0x0C, 0x6E, 0xC0, 0x00, 0x01, 0x98, 0x80, 0x00, 0x40, 0x00, 0x50, 0x86, 0x42, 0x00, 0x40, 0x29, 0x15, 0x00,
        0x01, 0x96, 0x62, 0x42, 0xF5, 0x00, 0x01, 0x4C, 0x24, 0x4C, 0xCD, 0x00, 0x00, 0x61, 0x5A, 0xB6, 0x00, 0xFF, 0x50, 0x41,
        0x00, 0x01, 0x21, 0x00, 0x00, 0x22, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA8, 0x08, 0x05, 0x28,
        0x08, 0x00, 0x08, 0x78, 0x00, 0x20, 0x00, 0x20, 0x00, 0x37, 0xBB, 0x5A, 0x05, 0x20, 0x00, 0x00, 0xD0, 0x80, 0x00, 0x20,
        0x00, 0x28, 0x43, 0x14, 0xC0, 0x20, 0x14, 0x8A, 0x80, 0x00, 0x22, 0x38, 0xB1, 0x77, 0x80, 0x00, 0xA7, 0xE1, 0x46, 0x66,
        0x80, 0x00, 0x8B, 0xE6, 0x4A, 0x00, 0x7F, 0xA9, 0x40, 0x80, 0x02, 0x09, 0x02, 0x01, 0x01, 0x89, 0x00, 0x00
    };        

/*
    unsigned char msg[] = 
    {
        0x61, 0x10, 0x33, 0x00, 0x61, 0x01, 0x4B, 0x1C, 0xD0, 0x15, 0x55, 0x54, 0x55, 0x55, 0x54, 0x6D, 0x55, 0x54, 0x75, 0x55,
        0x54, 0x8D, 0x55, 0x54, 0xAD, 0x55, 0x54, 0xB5, 0x55, 0x54, 0xC5, 0x55, 0x54, 0xF5, 0x55, 0x54, 0x09, 0x82, 0x01, 0x01,
        0x88, 0xC0, 0x01, 0x01, 0x09, 0x80
     };        

    unsigned char msg[] = 
    {
        0xA5, 0x18, 0x40, 0x41, 0x04, 0x00, 0x00, 0x8A, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0, 0x15,
        0x88, 0xA0, 0x20, 0x08, 0x22, 0xA0, 0x35, 0x80, 0x00, 0x80, 0x00, 0x97, 0x5D, 0x5A, 0xAE, 0x80, 0x00, 0x02, 0xC2, 0xB0,
        0x00, 0x80, 0x00, 0xA1, 0x0C, 0xC0, 0x00, 0x56, 0x22, 0x2A, 0x00, 0x03, 0x4B, 0x8D, 0x68, 0x12, 0x00, 0x02, 0x97, 0x50,
        0xD9, 0x9A, 0x00, 0x02, 0x59, 0x30, 0x5C, 0x01, 0xFE, 0x8F, 0x82, 0x00, 0x02, 0x82, 0x00, 0x00, 0x45, 0x55, 0x55, 0x55,
        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x50, 0x0A, 0xC4, 0x50, 0x10, 0x04, 0x11, 0x80, 0x1A, 0x40, 0x00, 0x40, 0x00,
        0x31, 0x86, 0xCA, 0xF5, 0xC0, 0x00, 0x00, 0xB0, 0x40, 0x00, 0x40, 0x00, 0x50, 0x86, 0x82, 0x00, 0x2B, 0x11, 0x15, 0x00,
        0x01, 0xF9, 0x09, 0x40, 0xA3, 0x00, 0x01, 0x4A, 0x11, 0xAC, 0xCD, 0x00, 0x00, 0xFF, 0xA6, 0xDC, 0x00, 0xFF, 0x48, 0x81,
        0x00, 0x01, 0xA1, 0x00, 0x00, 0x22, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA8, 0x05, 0x62, 0x28,
        0x00, 0x10, 0x02, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x38, 0xFE, 0xD0, 0xAF, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0xDC, 0xE6, 0xE1, 0xBE, 0x80, 0x3E, 0x11, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x2E
    };

    unsigned char msg[] = 
    {
        0x41, 0x10, 0x33, 0x00, 0x71, 0x7C, 0x0D, 0xA3, 0x50, 0x0D, 0x55, 0x54, 0x2D, 0x55, 0x54, 0x4D, 0x55, 0x54, 0x85, 0x55,
        0x54, 0x8D, 0x55, 0x54, 0xA5, 0x55, 0x54, 0xCD, 0x55, 0x54, 0xE5, 0x55, 0x54, 0xED, 0x55, 0x54, 0x09, 0x82, 0x01, 0x01,
        0x88, 0x80, 0x01, 0x01, 0x09, 0x80
    };        
*/
    static BrcmLbsRilAsn1_Callbacks cbs;

    cbs.onRilSendToNetwork = DebuggingCallback_SendToNetwork;

    D("Calling Init");
    ril = BrcmLbsRilAsn1_init(&cbs, NULL);

    D("Sleeping 2 seconds...");
    sleep(2);

    D("Calling sendToGps ...");
    BrcmLbsRilAsn1_sendToGps(ril, BRCM_LBS_RIL_RRLP, msg, sizeof(msg));
    
    D("Sleeping 60 seconds while expecting callback...");
    sleep(60);

    return 0;
}

