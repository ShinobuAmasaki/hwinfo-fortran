# hwinfo-fortran
Hardware information access from Fortran.

The module hwinfo-fortran provides access to hardware information on Fortran using OS APIs.

This module works on Linux, FreeBSD and macOS.
To support Windows is in the works.

## Build

Add below in `fpm.toml` of your project:

```toml
hwinfo-fortran = { git = "https://github.com/shinobuamasaki/hwinfo-fortran"}
```

Supported compilers are below:

- GNU Compiler Collection (`gcc`, `g++`, `gfortran`)

## Feature

### Ethernet

Currently, it is possible to obtain the MAC address of a network interface card (NIC) using Fortran. 

```fortran
use :: hwinfo_m

do i = 1, eth_get_num_devices()
   print '(a, a, z12.12)', eth_get_device_name(i), ": MAC_addr=",  eth_get_mac_addr(i)
end do
```

- `eth_get_num_device()` returns a number of NICs.
- `eth_get_device_name(i)` returns the name of the `i`-th NIC.
- `eth_get_mac_addr(i)` returns the MAC address of the `i`-th NIC in type `integer(int64)`.

### Infiniband

If you build by specifying `-DIB` for `--flag` and `--c-flag` and `-libverbs` for `--link-flag`,
you can use the infiniband module.

The infiniband module currently allows you to obtain the GUID of the host channel adapter(HCA).
