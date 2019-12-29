# vmware网络连接模式——桥接、NAT、仅主机模式

| Mode      | VM->Host | VM<-Host | VM1<->VM2 | VM->Net/LAN | VM<-Net/LAN |
|-----------|----------|----------|-----------|-------------|-------------|
| Host-only | + | + | + | - | - |
| Internal | - | - | + | - | - |
| Bridged | + | + | + | + | + |
| NAT | + | Port forward | - | + | Port forward |
| NATservice | + | Port forward | + | + | Port forward |

[vmware网络连接模式——桥接、NAT、仅主机模式](https://blog.51cto.com/sharemi/1790733)
