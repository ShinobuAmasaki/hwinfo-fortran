program main
   use :: hwinfo_m
   use :: unsigned_m 
   implicit none
   
   type(uint64) :: ans 

   print *, ib_get_num_devices()

   ans = ib_get_guid()
   print '(z16.16)', ans%u64

end program main