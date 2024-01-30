#ifdef IB

#include <stdio.h>
#include <infiniband/verbs.h>
#include <infiniband/arch.h>

int ib_get_num_devices(void)
{
   int num;
   struct ibv_device **dev_list;

   dev_list = ibv_get_device_list(&num);

   if (!dev_list) {
      perror("Failure: ibv_get_device_list");
      return 0;
   }
   return num;
}

unsigned long long ib_get_guid(void)
{
   unsigned long long ans;

   struct ibv_device **list;
   
   list = ibv_get_device_list(NULL);
   if (!list) {
      perror("Failure: ibv_get_device_list");
      return 0;
   }

   struct ibv_device *ib_dev = list[0];
   ans = ntohll(ibv_get_device_guid(ib_dev));

   return ans; 
}
#endif 
