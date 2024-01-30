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

#endif
end module hwinfo_ib_m


