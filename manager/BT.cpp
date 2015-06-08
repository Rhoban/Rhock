#include <iostream>
#include <string>
#include "BT.h"
#ifdef WIN32
#include "windows.h"
#include "ws2bth.h"
#include "bthsdpdef.h"
#include "bluetoothapis.h"
#include "initguid.h"
#endif

BT::BT()
{
}

void BT::listDevices()
{
    entries.clear();

#ifdef WIN32
    HBLUETOOTH_DEVICE_FIND founded_device;

    BLUETOOTH_DEVICE_INFO device_info;
    device_info.dwSize = sizeof(device_info);

    BLUETOOTH_DEVICE_SEARCH_PARAMS search_criteria;
    search_criteria.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
    search_criteria.fReturnAuthenticated = TRUE;
    search_criteria.fReturnRemembered = FALSE;
    search_criteria.fReturnConnected = FALSE;
    search_criteria.fReturnUnknown = FALSE;
    search_criteria.fIssueInquiry = FALSE;
    search_criteria.cTimeoutMultiplier = 0;

    founded_device = BluetoothFindFirstDevice(&search_criteria, &device_info);

    if(founded_device == NULL) {
        return;
    }

    do {
        BTInfo info;
        std::wstring ws(device_info.szName);
        info.name = QString::fromStdWString(ws);
        unsigned char addr[6];
        memcpy(addr, &device_info.Address, 6);
        QString qaddr;
        qaddr.sprintf("%02X%02X%02X%02X%02X%02X",
                    addr[5], addr[4], addr[3], addr[2], addr[1], addr[0]
                     );
        qaddr = qaddr.toLower();
        info.address = qaddr;
        info.connected = device_info.fConnected;

        entries[qaddr] = info;
    } while (BluetoothFindNextDevice(founded_device, &device_info));   
#endif
}

bool BT::hasDevice(QString addr)
{
    return entries.contains(addr);
}

QString BT::getDeviceName(QString addr)
{
    if (entries.contains(addr)) {
        return entries[addr].name;
    }

    return "";
}
