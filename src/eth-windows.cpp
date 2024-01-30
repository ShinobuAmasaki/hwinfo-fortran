#ifdef _WIN32

#include <iostream>
#include <iomanip>
#include <WinSock2.h>
#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")

extern "C"{

int eth_get_num_devices(void)
{
   ULONG bufferSize = 0;

   if (GetAdaptersInfo(nullptr, &bufferSize) == ERROR_BUFFER_OVERFLOW) {

      // alloc memory
      PIP_ADAPTER_INFO adapterInfo = reinterpret_cast<IP_ADAPTER_INFO*> (malloc(bufferSize));
      if (adapterInfo != nullptr) {

         int count = 0;
         // Get information
         if (GetAdaptersInfo(adapterInfo, &bufferSize) == NO_ERROR) {

            PIP_ADAPTER_INFO currentAdapter = adapterInfo;

            while (currentAdapter != nullptr) {
               count++;
               currentAdapter = currentAdapter->Next;
            }
         }
         return count;

      } else {
         std::cerr << "Memory allocation failed." << std::endl;
         return -1;
      }
   } else {
      std::cerr << "Failed to get buffer size." << std::endl;
      return -1;
   }

}

void eth_get_device_name(int index, char**name)
{
      ULONG bufferSize = 0;

   if (GetAdaptersInfo(nullptr, &bufferSize) == ERROR_BUFFER_OVERFLOW) {

      // alloc memory
      PIP_ADAPTER_INFO adapterInfo = reinterpret_cast<IP_ADAPTER_INFO*> (malloc(bufferSize));
      if (adapterInfo != nullptr) {

         int count = 0;
         // Get information
         if (GetAdaptersInfo(adapterInfo, &bufferSize) == NO_ERROR) {

            PIP_ADAPTER_INFO currentAdapter = adapterInfo;

            while (currentAdapter != nullptr) {
               if (count == index-1) {
                  strcpy(*name, currentAdapter->Description);
                  return;
               }
               count++;
               currentAdapter = currentAdapter->Next;
            }
         }
         return;

      } else {
         std::cerr << "Memory allocation failed." << std::endl;
         return;
      }
   } else {
      std::cerr << "Failed to get buffer size." << std::endl;
      return;
   }

}

long long eth_get_mac_addr(int index)
{
      ULONG bufferSize = 0;

   if (GetAdaptersInfo(nullptr, &bufferSize) == ERROR_BUFFER_OVERFLOW) {

      // alloc memory
      PIP_ADAPTER_INFO adapterInfo = reinterpret_cast<IP_ADAPTER_INFO*> (malloc(bufferSize));
      if (adapterInfo != nullptr) {

         int count = 0;
         // Get information
         if (GetAdaptersInfo(adapterInfo, &bufferSize) == NO_ERROR) {

            PIP_ADAPTER_INFO currentAdapter = adapterInfo;

            while (currentAdapter != nullptr) {
               if (count == index-1) {
                  long long macAddress = 0;
                  for (int i = 0; i < currentAdapter->AddressLength; ++i) {
                     macAddress = (macAddress << 8) | currentAdapter->Address[i];
                  }

                  return macAddress;
               }
               count++;
               currentAdapter = currentAdapter->Next;
            }
         }
         return 0;

      } else {
         std::cerr << "Memory allocation failed." << std::endl;
         return -1;
      }
   } else {
      std::cerr << "Failed to get buffer size." << std::endl;
      return -1;
   }

}

}
#endif