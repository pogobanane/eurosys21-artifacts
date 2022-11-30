#!/bin/bash
qemu-system-x86_64 \
  -initrd data/nginx.cpio \
  -kernel images//unikraft+mimalloc.kernel \
  -m 1024 \
  -cpu host \
  -enable-kvm \
  -netdev bridge,id=en0,br=virbr0 \
  -device virtio-net-pci,netdev=en0 \
  -append "netdev.ipv4_addr=172.44.0.2 netdev.ipv4_gw_addr=172.44.0.1 netdev.ipv4_subnet_mask=255.255.255.0 -- " \
  -nographic                                  

