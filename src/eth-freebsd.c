#ifdef __FreeBSD__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <net/route.h>
#include <stdint.h>
#include <netinet/in.h>

uint64_t convert_network_to_host_order(uint64_t val) {
    return be64toh(val);
}

int eth_get_num_devices(void)
{
   int mib[6];
   size_t len;
   char *buf;
   struct if_msghdr *ifm;
   int count = 0;

   // create a sysctl message for getting nic information
   mib[0] = CTL_NET;
   mib[1] = AF_ROUTE;
   mib[2] = 0;
   mib[3] = AF_LINK;
   mib[4] = NET_RT_IFLIST;
   mib[5] = 0;

   if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0 ) {
      perror("sysctl");
      return -1;
   }

   buf = (char*) malloc(len);

   if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
      perror("sysctl");
      free(buf);
      return -1;
   }

   for (char *ptr = buf; ptr < buf + len; ptr += ifm->ifm_msglen) {
      ifm = (struct if_msghdr *) ptr;
      if (ifm->ifm_type = RTM_IFINFO) {
         count++;
      }
   }

   free(buf);
   return count;
}

void eth_get_device_name(int index, char**name)
{
   int mib[6];
   size_t len;
   char *buf;
   struct if_msghdr *ifm;
  
   // create a sysctl message for getting nic information
   mib[0] = CTL_NET;
   mib[1] = AF_ROUTE;
   mib[2] = 0;
   mib[3] = AF_LINK;
   mib[4] = NET_RT_IFLIST;
   mib[5] = 0;

   if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0 ) {
      perror("sysctl");
      return;
   }
   buf = (char*) malloc(len);
   if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
      perror("sysctl");
      free(buf);
      return;
   }
   

   int count = 0;
   for (char*ptr = buf; ptr < buf + len; ptr+=ifm->ifm_msglen) {
      ifm = (struct if_msghdr*) ptr;
      if (ifm->ifm_type == RTM_IFINFO) {
         if (count == index-1) {
            struct sockaddr_dl *sdl = (struct sockaddr_dl *) (ifm +1);
            free(buf);
            strncpy(*name, sdl->sdl_data, sdl->sdl_nlen);
            return;
         }
         count++;
      }
   }
   return; 
}

long long eth_get_mac_addr (int index)
{
   int mib[6];
   size_t len;
   char *buf;
   struct if_msghdr *ifm;
  
   // create a sysctl message for getting nic information
   mib[0] = CTL_NET;
   mib[1] = AF_ROUTE;
   mib[2] = 0;
   mib[3] = AF_LINK;
   mib[4] = NET_RT_IFLIST;
   mib[5] = 0;

   if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0 ) {
      perror("sysctl");
      return -1;
   }
   buf = (char*) malloc(len);
   if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
      perror("sysctl");
      free(buf);
      return -1;
   }
   

   int count = 0;
   for (char*ptr = buf; ptr < buf + len; ptr+=ifm->ifm_msglen) {
      ifm = (struct if_msghdr*) ptr;
      if (ifm->ifm_type == RTM_IFINFO) {
         if (count == index-1) {
            struct sockaddr_dl *sdl = (struct sockaddr_dl *) (ifm +1);
            if (sdl->sdl_alen == 6) {
               uint64_t mac = 0;
               memcpy(&mac, LLADDR(sdl), 6);
               mac = convert_network_to_host_order(mac);
               free(buf);
               return (long long) (mac >> 16);
            }
         }
         count++;
      }
   }
   return 0; 
}



#endif

