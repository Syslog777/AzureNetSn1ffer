/*
--Requirements
	Project settings must mod TargetApi to beta version.
	app_manifest.json must include WifiConfig and NetworkConfig as true
*/

/*
Quick self lessons:
Azure setup: https://blog.aignacio.com/2018/12/14/review-azure-sphere-mt3620/
Pointer tutorial: https://stackoverflow.com/questions/1143262/what-is-the-difference-between-const-int-const-int-const-and-int-const?rq=1
Memory allocation: https://www.programiz.com/c-programming/c-dynamic-memory-allocation
Debugging segmentation faults: https://www.cprogramming.com/debugging/segfaults.html
When to use malloc: https://stackoverflow.com/questions/8800482/when-and-why-to-use-malloc
new vs malloc: https://www.includehelp.com/cpp-tutorial/difference-between-new-and-malloc.aspx
Format specifiers: https://www.thecrazyprogrammer.com/2016/10/format-specifiers-c.html
uint8_t vs uint16_t or uint32_t :https://stackoverflow.com/questions/26362386/why-is-the-format-specifier-for-uint8-t-and-uint16-t-the-same-u
Use printf on multiple lines: https://stackoverflow.com/questions/1752079/in-c-can-a-long-printf-statement-be-broken-up-into-multiple-lines
Printing out bool with prinf: https://stackoverflow.com/questions/17307275/what-is-the-printf-format-specifier-for-bool
Why device can only be claimed once: https://social.msdn.microsoft.com/Forums/en-US/caea57b7-9f9d-45c6-841b-8a2e718393aa/changing-directory-and-tenant-before-claiming-device?forum=azuresphere
How to uninstall Visual Studio 2017: https://developercommunity.visualstudio.com/content/problem/24239/cannot-uninstall-microsoft-visual-studio-2017-inst.html
&& https://docs.microsoft.com/en-us/visualstudio/install/uninstall-visual-studio?view=vs-2017
*/

/*Purpose:
To collect local wifi data and display it to the local console.
*/

/* 
Bugs:
1. If a new device is brought in, visual studio and the azure sdk will throw errors and not fully 
communicate with the bord. This may be due to old cache or configuration files. I had to fully
uninstall the SDK and Visual Studio 2017. I was able to update the firmware, however.
2. My project that worked with board1 didn't work with board2, even though.
*/

#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "azure_netsn1ffer.h"

// applibs_versions.h defines the API struct versions to use for applibs APIs.
#include "applibs_versions.h"
#include <applibs/log.h>

/*
Scans the surrounding area for networks and then prints out their network info
*/
size_t reportLan(AzureNetSn1ffer * sniffer)
{
	size_t networkCount = sniffer->lanNetworkScan();
	WifiConfig_ScannedNetwork * scannedNetworkArray =
		(WifiConfig_ScannedNetwork *)malloc(sizeof(WifiConfig_ScannedNetwork) * networkCount);
	printf("\nLocal area networks in range: %i", networkCount);
	if (networkCount == 0) {
		printf("\nNo networks were found.");
		return 0;
	}
	else if (networkCount < 0)
	{
		printf("\n Something went wrong while scanning.");
		return -1;
	}
	ssize_t result = sniffer->getScannedNetworks(scannedNetworkArray, networkCount);
	if (result < 0)
	{
		return result;
	}
	for (size_t i = 0; i < networkCount; i++)
	{
		sniffer->reportScannedNetwork(&scannedNetworkArray[i]);
	}
	return result;
}

/* Prints each interface info to CLI output*/
int reportInterfaces(AzureNetSn1ffer * sniffer)
{
	printf("\n-------INTERFACE REPORT START-------");
	ssize_t interfaceCount = sniffer->getInterfaceCount();
	Networking_NetworkInterface *outNetworkInterfacesArray =
		(Networking_NetworkInterface*)malloc(sizeof(Networking_NetworkInterface) * interfaceCount);
	
	if (interfaceCount == 0) {
		printf("No interfaces were found.");
		return 0;
	}
	else if (interfaceCount < 0)
	{
		printf("\n Something went wrong while searching for interfaces.");
		return -1;
	}
	ssize_t result = sniffer->getInterfaces(outNetworkInterfacesArray, interfaceCount);
	if (result < 0)
	{
		return result;
	}
	for (ssize_t i = 0; i < interfaceCount; i++)
	{
		printf("\nInterface name: %s", &outNetworkInterfacesArray[i].interfaceName);
		sniffer->interfaceEnabled(&outNetworkInterfacesArray[i]);
	}
	printf("\n-------INTERFACE REPORT END-------\n");
	return result;
}

// Main entry point for this application.
int main(int argc, char *argv[])
{
    Log_Debug("\n");
	AzureNetSn1ffer sniffer;
	size_t result = reportLan(&sniffer); //scan the LAN
	if (result != 0)
		return result;
	result = reportInterfaces(&sniffer); //Check interfaces
	if (result != 0)
		return result;
    Log_Debug("\n");
    return 0;
}
