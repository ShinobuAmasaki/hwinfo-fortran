module hwinfo_m
   use :: hwinfo_ib_m
   use :: hwinfo_ethernet_m
   implicit none
   private

#ifdef IB
   public :: ib_get_guid
   public :: ib_get_num_devices
#endif

   public :: eth_get_num_devices
   public :: eth_get_device_name
   public :: eth_get_mac_addr

contains

end module hwinfo_m
