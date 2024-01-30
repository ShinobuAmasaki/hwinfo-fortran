module hwinfo_ib_m
#ifdef IB
   use, intrinsic :: iso_c_binding, only:c_int32_t
   use :: unsigned_m
   implicit none
   private

   public :: ib_get_num_devices
   interface
      function ib_get_num_devices() bind(c, name='ib_get_num_devices')
         import c_int32_t
         implicit none
         integer(c_int32_t) :: ib_get_num_devices
      end function ib_get_num_devices
   end interface

   public :: ib_get_guid
   interface
      function ib_get_guid() bind(c, name='ib_get_guid')
         import uint64
         implicit none
         type(uint64) :: ib_get_guid
      end function
   end interface
   
   public :: ib_get_guid_char

contains

   function ib_get_guid_char(index, delimiter) result(res)
      use :: unsigned_m
      implicit none
      integer, intent(in) :: index
      character(:), allocatable :: res
      character(*), optional, intent(in) :: delimiter

      character :: delim

      integer :: i
      character(16) :: buf
      character(23) :: cache
      type(uint64) :: addr

      addr = ib_get_guid()

      write(buf, '(z16.16)') addr%u64

      if (present(delimiter)) then
         delim = delimiter(1:1)
      else
         delim = ':'
      end if

      cache = buf(1:2)
      do i = 3, len(buf), 2
         cache = trim(cache)//delim//buf(i:i+1)
      end do

      res = cache

   end function ib_get_guid_char

#endif
end module hwinfo_ib_m


