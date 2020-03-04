# ubuntu中代理设置总结

## 1. 全局环境变量

```
$ sudo vi /etc/environment
```

加入：

```
http_proxy=http://myproxy.server.com:8080/
https_proxy=http://myproxy.server.com:8080/
ftp_proxy=http://myproxy.server.com:8080/
no_proxy="localhost,127.0.0.1,localaddress,.localdomain.com"
HTTP_PROXY=http://myproxy.server.com:8080/
HTTPS_PROXY=http://myproxy.server.com:8080/
FTP_PROXY=http://myproxy.server.com:8080/
NO_PROXY="localhost,127.0.0.1,localaddress,.localdomain.com"
```

## 2. gtk3 应用代理

```
gsettings set org.gnome.system.proxy mode 'manual'
gsettings set org.gnome.system.proxy.http host 'myproxy.server.com'
gsettings set org.gnome.system.proxy.http port 8080
```

## 3. apt-get 代理

```
$ sudo vi /etc/apt/apt.conf.d/95proxies
```

新增文件内容：
```
Acquire::http::proxy "http://myproxy.server.com:8080/";
Acquire::ftp::proxy "ftp://myproxy.server.com:8080/";
Acquire::https::proxy "https://myproxy.server.com:8080/";
```

## 4. git 代理

4.1 http 及 https
```
git config --global http.proxy http://myproxy.server.com:8080
git config --global https.proxy https://myproxy.server.com:8080
```

4.2 git://协议代理
```
$ sudo apt-get install socat
$ sudo vi /usr/bin/gitproxy
```

```
--------------------------
#!/bin/bash

PROXY=myproxy.server.com
PROXYPORT=8080
PROXYAUTH=username:password
exec socat STDIO PROXY:$PROXY:$1:$2,proxyport=$PROXYPORT,proxyauth=$PROXYAUTH
--------------------------
```
```
$ sudo chmod +x /usr/bin/gitproxy
$ git config --global core.gitproxy gitproxy
```