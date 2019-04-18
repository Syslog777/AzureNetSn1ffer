/* Copyright (c) Talib Muhammad. All rights reserved. */
#include "azure_netsn1ffer.h"
#include "applibs_versions.h"
#include <applibs/wificonfig.h>
#include <applibs/networking.h>
#include <sys/types.h> // defines type ssize_t
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>

using namespace std;

int AzureNetSn1ffer::forgetAllNetworks(void)
{
	printf("\n", "Forgetting current networks...\n");
	return WifiConfig_ForgetAllNetworks();
}

int AzureNetSn1ffer::forgetNetwork(WifiConfig_StoredNetwork * storedNetwork)
{
	printf("\n", "Forgetting stored network...\n");
	reportStoredNetwork(storedNetwork);
	return WifiConfig_ForgetNetwork(storedNetwork);
}

int AzureNetSn1ffer::getCurrentNetwork(WifiConfig_ConnectedNetwork * connectedNetwork)
{
	printf("\n", "Getting current network...\n");
	reportConnectedNetwork(connectedNetwork);
	return WifiConfig_GetCurrentNetwork(connectedNetwork);
}

ssize_t AzureNetSn1ffer::getScannedNetworks(WifiConfig_ScannedNetwork * scannedNetworkArray, size_t scannedNetworkArrayCount)
{
	printf("\n", "Getting current scanned network...\n");
	return WifiConfig_GetScannedNetworks(scannedNetworkArray, scannedNetworkArrayCount);
}

ssize_t AzureNetSn1ffer::getStoredNetworkCount(void)
{
	printf("\n", "Getting stored network count...\n");
	return WifiConfig_GetStoredNetworkCount();
}

int AzureNetSn1ffer::getStoredNetworks(WifiConfig_StoredNetwork * storedNetworkArray, size_t storedNetworkArrayCount)
{
	printf("\n", "Getting current stored networks...\n");
	return WifiConfig_GetStoredNetworks(storedNetworkArray, storedNetworkArrayCount);
}

int AzureNetSn1ffer::storeOpenNetwork(const uint8_t * ssid, size_t ssidLength)
{
	printf("\n", "Getting current open network...\n");
	return WifiConfig_StoreOpenNetwork(ssid, ssidLength);
}

int AzureNetSn1ffer::storeWPA2Network(const uint8_t * ssid, size_t ssidLength, const char * psk, size_t pskLength)
{
	printf("\n", "Storing current networks");
	return WifiConfig_StoreWpa2Network(ssid, ssidLength, psk, pskLength);
}

/*
@errors
If an error is encountered, returns -1 and sets errno to the error value.
EACCES: the application manifest does not include the WifiConfig capability.
EAGAIN: the Wi-Fi device isn't ready yet.
*/
ssize_t AzureNetSn1ffer::lanNetworkScan(void)
{
	printf("Scanning for local area networks....");
	return WifiConfig_TriggerScanAndGetScannedNetworkCount();
}

/*
struct WifiConfig_ConnectedNetwork {
	uint32_t z__magicAndVersion;
	uint8_t ssid[WIFICONFIG_SSID_MAX_LENGTH];
	uint8_t bssid[WIFICONFIG_BSSID_BUFFER_SIZE];
	uint8_t ssidLength;
	WifiConfig_Security_Type security;
	uint32_t frequencyMHz;
	int8_t signalRssi;
};
*/
void AzureNetSn1ffer::reportConnectedNetwork(WifiConfig_ConnectedNetwork * connectedNetwork)
{
	printf("\n-------CONNECTED NETWORK REPORT START-------\n");
	printf("\nssid[WIFICONFIG_SSID_MAX_LENGTH]: %u", connectedNetwork->ssid[WIFICONFIG_SSID_MAX_LENGTH]);
	printf("\nbssid[WIFICONFIG_BSSID_BUFFER_SIZE]: %u", connectedNetwork->bssid[WIFICONFIG_BSSID_BUFFER_SIZE]);
	printf("\nssidLength: %u" , connectedNetwork->ssidLength);
	printf("\nFREQUENCY_MHz: %u", connectedNetwork->frequencyMHz);
	printf("\n-------CONNECTED NETWORK REPORT END-------\n");
}

/*
struct WifiConfig_ScannedNetwork {
	uint32_t z__magicAndVersion;
	uint8_t ssid[WIFICONFIG_SSID_MAX_LENGTH];
	uint8_t bssid[WIFICONFIG_BSSID_BUFFER_SIZE];
	uint8_t ssidLength;
	WifiConfig_Security_Type security;
	uint32_t frequencyMHz;
	int8_t signalRssi;
};
*/
void AzureNetSn1ffer::reportScannedNetwork(WifiConfig_ScannedNetwork * scannedNetwork)
{
	printf("\n-------SCANNED NETWORK REPORT START-------");
	printf("\nSSIDLENGTH: %u", scannedNetwork->ssidLength);
	printf("\nSSID: %u", scannedNetwork->ssid);
	printf("\nBSSID: %u", scannedNetwork->bssid[WIFICONFIG_BSSID_BUFFER_SIZE]);
	printf("\nFREQUENCY_MHz: %u", scannedNetwork->frequencyMHz);
	printf("\nSIGNAL_Rssi: %i", scannedNetwork->signalRssi);
	printf("\n-------SCANNED NETWORK REPORT END-------\n");
}

/*
Notes:
struct WifiConfig_StoredNetwork {
	uint32_t z__magicAndVersion;
	uint8_t ssid[WIFICONFIG_SSID_MAX_LENGTH];
	uint8_t ssidLength;
	bool isEnabled;
	bool isConnected;
	WifiConfig_Security_Type security;
};
*/
void AzureNetSn1ffer::reportStoredNetwork(WifiConfig_StoredNetwork * storedNetwork)
{
	printf("\n-------SCANNED NETWORK REPORT START-------");
	if (storedNetwork->isEnabled)
	{
		printf("\nIS_ENABLED: true");
	}
	else
	{
		printf("\nIS_ENABLED: false");
	}

	if (storedNetwork->isConnected)
	{
		printf("\nIS_CONNECTED: true");
	}
	else
	{
		printf("\nIS_CONNECTED: false");
	}
	printf("\nSSIDLENGTH: %u", storedNetwork->ssidLength);
	printf("\n-------SCANNED NETWORK REPORT END-------\n");
}

ssize_t AzureNetSn1ffer::getInterfaceCount(void)
{
	printf("\nGetting interface count...");
	return Networking_GetInterfaceCount();
}

ssize_t AzureNetSn1ffer::getInterfaces(Networking_NetworkInterface *outNetworkInterfacesArray, size_t networkInterfacesArrayCount)
{
	printf("\nGetting network interfaces...");
	return Networking_GetInterfaces(outNetworkInterfacesArray, networkInterfacesArrayCount);
}

int AzureNetSn1ffer::isNetworkingReady(bool * outIsNetworkingReady)
{
	printf("Verifying whether or not internet connectivity is",
		"available and time is synced.");
	return Networking_IsNetworkingReady(outIsNetworkingReady);
}

int AzureNetSn1ffer::setInterfaceState(const char *networkInterfaceName, bool isEnabled)
{
	printf("Setting interface state...");
	return Networking_SetInterfaceState(networkInterfaceName, isEnabled);
}

void AzureNetSn1ffer::interfaceEnabled(Networking_NetworkInterface * networkInterface)
{
	if (networkInterface->isEnabled)
	{
		printf("\nIsEnabled: true");
	} else
	{
		printf("\nIsEnabled: false");
	}
}