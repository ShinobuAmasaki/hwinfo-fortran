#ifdef __cplusplus
extern "C" {
#endif

int eth_get_num_devices(void);

void eth_get_device_name(int index);

long long eth_get_mac_addr(int index, char**name);

#ifdef __cplusplus
}
#endif