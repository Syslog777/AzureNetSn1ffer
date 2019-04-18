/* Copyright (c) Talib Muhammad. All rights reserved. */
#ifndef AZURENETSN1FFER
#define AZURENETSN1FFER

/// This identifier should be defined before including any of the networking-related header files.
/// It indicates which version of the Wi-Fi data structures the application uses.
#define NETWORKING_STRUCTS_VERSION 1

/// This identifier must be defined before including any of the Wi-Fi related header files.
/// It indicates which version of the Wi-Fi data structures the application uses.
#define WIFICONFIG_STRUCTS_VERSION 1

// applibs_versions.h defines the API struct versions to use for applibs APIs.
#include "applibs_versions.h"
#include <applibs/wificonfig.h>
#include <applibs/networking.h>
#include <sys/types.h> // defines type ssize_t
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>

// @function ForgetAllNetworks	Removes all stored Wi-Fi networks from the device. Disconnects the device from any connected network.
// @function ForgetNetwork	Removes a Wi-Fi network from the device. Disconnects the device from the network if it's currently connected.
// @function GetCurrentNetwork	Gets the Wi-Fi network that is connected to the device.
// @function GetScannedNetworks	Gets the Wi-Fi networks found by the last scan operation.
// @function GetStoredNetworkCount	Gets the number of stored Wi-Fi networks on the device.
// @function GetStoredNetworks	Retrieves all stored Wi-Fi networks on the device.
// @function StoreOpenNetwork	Stores an open Wi-Fi network without a key.
// @function StoreWpa2Network	Stores a WPA2 Wi-Fi network that uses a pre-shared key.
// @function LanNetworkScan	Starts a scan to find all available Wi-Fi networks.
// @function GetInterfaceCount Gets the number of network interfaces in an Azure Sphere device.
// @function GetInterfaces Gets the list of network interfaces in an Azure Sphere device.
// @function IsNetworkingReady Verifies whether internet connectivity is available and time is synced.
// @function SetInterfaceState Enables or disables a network interface.

class AzureNetSn1ffer {
public:
	int forgetAllNetworks(void);
	int forgetNetwork(WifiConfig_StoredNetwork * storedNetwork);
	int getCurrentNetwork(WifiConfig_ConnectedNetwork * connectedNetwork);
	ssize_t getScannedNetworks(WifiConfig_ScannedNetwork * scannedNetworkArray, size_t scannedNetworkArrayCount);
	ssize_t getStoredNetworkCount(void);
	int getStoredNetworks(WifiConfig_StoredNetwork * storedNetworkArray, size_t storedNetworkArrayCount);
	int storeOpenNetwork(const uint8_t * ssid, size_t ssidLength);
	int storeWPA2Network(const uint8_t * ssid, size_t ssidLength, const char * psk, size_t pskLength);
	ssize_t lanNetworkScan(void);
	void reportConnectedNetwork(WifiConfig_ConnectedNetwork * connectedNetwork);
	void reportScannedNetwork(WifiConfig_ScannedNetwork * scannedNetwork);
	void reportStoredNetwork(WifiConfig_StoredNetwork * storedNetwork);
	ssize_t getInterfaceCount(void);
	ssize_t getInterfaces(Networking_NetworkInterface *outNetworkInterfacesArray, size_t networkInterfacesArrayCount);
	int isNetworkingReady(bool * outIsNetworkingReady);
	int setInterfaceState(const char *networkInterfaceName, bool isEnabled);
	void interfaceEnabled(Networking_NetworkInterface * networkInterface);
};
#endif 