# curl

## 设置代理

`curl -v`可以确定代理是否设置成功

- 1. 传参代理

每次访问都需要写代理参数：

```
curl -x socks5://127.0.0.1:7001 http://www.google.com
```

- 2. 设置配置文件

每次下载都会自动使用代理：

```
vim ~/.curlrc

socks5 = "127.0.0.1:7001"
```

如果临时不需要代理使用以下参数：

```
curl --noproxy "*" http://www.google.com
```
