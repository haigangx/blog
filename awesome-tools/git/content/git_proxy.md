# 为git设置代理

git clone有两种形式：

- HTTP形式：
  ```
  git clone https://github.com/owner/git.git
  ```

- SSH形式：
  ```
  git clone git@github.com:owner/git.git
  ```

两种方式要分别设置代理：

- HTTP形式：

  走HTTP代理：
  ```
  git config --global http.proxy "http://127.0.0.1:8080"
  git config --global https.proxy "http://127.0.0.1:8080"
  ```

  走sock5代理：
  ```
  git config --global http.proxy "socks5://127.0.0.1:1080"
  git config --global https.proxy "socks5://127.0.0.1:1080"
  ```

  取消设置：
  ```
  git config --global --unset http.proxy
  git config --global --unset https.proxy
  ```
- SSH形式：

  修改`~/.ssh/config`文件(不存在则新建)：
  ```
  # 必须是 github.com
  Host github.com
    HostName github.com
    User git
    # 走 HTTP 代理
    # ProxyCommand socat - PROXY:127.0.0.1:%h:%p,proxyport=8080
    # 走 socks5 代理（如 Shadowsocks）
    # ProxyCommand nc -v -x 127.0.0.1:1080 %h %p
  ```
