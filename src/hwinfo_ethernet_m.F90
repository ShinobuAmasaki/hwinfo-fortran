module hwinfo_ethernet_m
   use, intrinsic :: iso_c_binding
   use :: unsigned_m
   implicit none
   private

   public :: eth_get_mac_addr_char

   public :: eth_get_num_devices
   interface
      function eth_get_num_devices() bind(c, name="eth_get_num_devices")
         import c_int32_t
         implicit none
         integer(c_int32_t) :: eth_get_num_devices
      end function
   end interface 
   
   public :: eth_get_device_name
   interface
      subroutine c_eth_get_device_name(index, name) bind(c, name='eth_get_device_name')
         import c_ptr, c_int32_t
         implicit none
         integer(c_int32_t), intent(in), value :: index
         type(c_ptr), intent(out) :: name
      end subroutine c_eth_get_device_name
   end interface

   public :: eth_get_mac_addr
   interface
      function eth_get_mac_addr(index) bind(c, name='eth_get_mac_addr')
         import c_int64_t, c_int32_t
         implicit none
         integer(c_int32_t), intent(in), value :: index
         integer(c_int64_t) :: eth_get_mac_addr
      end function eth_get_mac_addr
   end interface
         
   

contains

   function eth_get_device_name(index) result(name)
      use, intrinsic :: iso_fortran_env
      implicit none
      integer(int32),intent(in) :: index
      character(:), allocatable :: name

      character(64), target :: buf
      type(c_ptr) :: cptr

      buf = ''

      cptr = c_loc(buf)

      call c_eth_get_device_name(index, cptr)

      name = trim(buf)
   end function eth_get_device_name


   function eth_get_mac_addr_char(index, delimiter) result(res)
      use, intrinsic :: iso_fortran_env, only: int64
      implicit none
      integer, intent(in) :: index
      character(:),allocatable :: res
      character(*), optional, intent(in) :: delimiter 
      character :: delim
      
      integer :: i
      character(12) :: buf
      character(17) :: cache


      integer(int64) :: addr

      addr = eth_get_mac_addr(index)

      write(buf, '(z12.12)') addr

      if(present(delimiter)) then
         delim = delimiter(1:1)
      else
         delim = ':'
      endif

      cache = buf(1:2)
      do i = 3, 12, 2
         cache = trim(cache)//delim//buf(i:i+1)
      end do

      res = cache

   end function eth_get_mac_addr_char

end module 
