#ifdef __MACH__
#include <stdio.h>
#include <string.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <net/if_types.h>
#include <ifaddrs.h>
#include <machine/endian.h>

#define be64toh(x) ntohll(x)

uint64_t convert_network_to_host_order(uint64_t val) {
    return be64toh(val);
}

int eth_get_num_devices(void)
{
	struct ifaddrs *ifa_list, *ifa;
	struct sockaddr_dl *sdl;

	if (getifaddrs(&ifa_list) < 0){
		perror("getifaddrs");
		return -1;
	}

	int count = 0;
	for (ifa = ifa_list; ifa; ifa = ifa->ifa_next) {
		sdl = (struct sockaddr_dl*) ifa->ifa_addr;
		if (sdl->sdl_family == AF_LINK && sdl->sdl_type == IFT_ETHER) {
			count++;
		}
	}
	freeifaddrs(ifa_list);
	return count;
}

void eth_get_device_name(int index, char**name)
{
	struct ifaddrs *ifa_list, *ifa;
	struct sockaddr_dl *sdl;
	
	if (getifaddrs(&ifa_list) < 0){
		perror("getifaddrs");
		return;
	}
	int count = 0;
	for (ifa = ifa_list; ifa; ifa = ifa->ifa_next) {
		sdl = (struct sockaddr_dl*) ifa->ifa_addr;
		if (sdl->sdl_family == AF_LINK && sdl->sdl_type == IFT_ETHER) {
			if (count == index -1) {
				memcpy(*name, sdl->sdl_data, sdl->sdl_nlen);
				freeifaddrs(ifa_list);
				return;
			}
			count++;
		}
	}
	freeifaddrs(ifa_list);
	return;
}

long long eth_get_mac_addr(int index, char**name)
{
	struct ifaddrs *ifa_list, *ifa;
	struct sockaddr_dl *sdl;
	
	if (getifaddrs(&ifa_list) < 0){
		perror("getifaddrs");
		return -1;
	}
	int count = 0;
	for (ifa = ifa_list; ifa; ifa = ifa->ifa_next) {
		sdl = (struct sockaddr_dl*) ifa->ifa_addr;
		if (sdl->sdl_family == AF_LINK && sdl->sdl_type == IFT_ETHER) {
			if (count == index -1) {
				uint64_t mac = 0;
				memcpy(&mac, LLADDR(sdl), 6);
				mac = convert_network_to_host_order(mac);
				freeifaddrs(ifa_list);
				return (long long) (mac >> 16);
			}
			count++;
		}
	}
	freeifaddrs(ifa_list);
	return 0;
}

#endif
