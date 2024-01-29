#ifdef __linux__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define MAX_INTERFACES 16 

int eth_get_num_devices(void)
{
   struct ifreq ifreqs[MAX_INTERFACES];
   struct ifconf ifconf;
   int socket_fd;

   // Open socket
   socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
   if (socket_fd == -1) {
      perror("socket");
      return -1;
   }

   // Get the information of network devices
   ifconf.ifc_buf = (char*) ifreqs;
   ifconf.ifc_len = sizeof(ifreqs);

   if (ioctl(socket_fd, SIOCGIFCONF, &ifconf) == -1) {
      perror("ioctl");
      close(socket_fd);
      return -1;
   }

   int num_interfaces = ifconf.ifc_len / sizeof(struct ifreq);

   close(socket_fd);
   return num_interfaces;
}

void eth_get_device_name(int index, char**name)
{
   struct ifreq ifreqs[MAX_INTERFACES];
   struct ifconf ifconf;
   int socket_fd;

   // Open socket
   socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
   if (socket_fd == -1) {
      perror("socket");
      return -1;
   }

   // Get the information of network devices
   ifconf.ifc_buf = (char*) ifreqs;
   ifconf.ifc_len = sizeof(ifreqs);

   if (ioctl(socket_fd, SIOCGIFCONF, &ifconf) == -1) {
      perror("ioctl");
      close(socket_fd);
      return -1;
   }

   strcpy(*name, ifreqs[index-1].ifr_name);

   close(socket_fd);
   return;
}

long long eth_get_mac_addr(int index)
{
   unsigned long long mac_addr = 0;
   struct ifreq ifr;
   int socket_fd;
   char* name;

   name = (char*) malloc(sizeof(char)*64);

   // Open socket
   socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
   if (socket_fd == -1) {
      perror("socket");
      return -1;
   }

   eth_get_device_name(index, &name);

   strncpy(ifr.ifr_name, name, IF_NAMESIZE-1);

   free(name);

   if (ioctl(socket_fd, SIOCGIFHWADDR, &ifr) == -1) {
      perror("ioctl");
      close(socket_fd);
      return -1;
   }

   for (int i = 0; i < 6; ++i){
      mac_addr <<= 8;
      mac_addr |= (unsigned char) ifr.ifr_hwaddr.sa_data[i];
   }

   close(socket_fd);
   return mac_addr;
}
#endif