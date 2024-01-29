program main
   use :: hwinfo_m
   implicit none 

   integer :: i 

   do i = 1, eth_get_num_devices()
      print '(a, a, z12.12)', eth_get_device_name(i), ": MAC_addr=",  eth_get_mac_addr(i)
   end do

end program main
