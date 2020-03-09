# tmux

<details>
<summary>cheatsheet</summary>

| 操作 | 说明 |
| --- | --- |
| `prefix %` | 左右分屏 |
| `prefix "` | 上下分屏 |

</details>

<details>
<summary>tmux下复制粘贴</summary>

tmux下有两套复制粘贴方法：
- 快捷键单窗口复制
  ```
  鼠标选中后ctrl+shift+c、ctrl+shift+v进行复制粘贴
  ```

- 全屏幕复制
  ```
  1.prefix [ 进入复制模式
  2.移动鼠标到复制起点，按空格键开始复制，移动鼠标使用vim键位
  3.移动鼠标选择复制区域，复制完成按回车键结束复制
  4.prefix ] 粘贴
  ```

</details>

<details>
<summary>linux下打开终端时自动运行tmux</summary>

在`~/.bashrc`或`~/.zshrc`中添加如下配置，需要添加到所有alias语句之前：

- 确保tmux不会嵌套启动

  ```
  # If not running interactively, do not do anything
  [[ $- != *i* ]] && return
  [[ -z "$TMUX" ]] && exec tmux
  ```

- 下面配置尝试只启动一个会话，如果之前启动过会话，会直接attach

  ```
  # TMUX
  if which tmux >/dev/null 2>&1; then
      #if not inside a tmux session, and if no session is started, start a new session
      test -z "$TMUX" && (tmux attach || tmux new-session)
  fi
  ```

- 启动tmux之前先检查tmux是否安装，当前会话退出时会自动连接未关闭会话

  ```
  # TMUX
  if which tmux >/dev/null 2>&1; then
      # if no session is started, start a new session
      test -z ${TMUX} && tmux

      # when quitting tmux, try to attach
      while test -z ${TMUX}; do
          tmux attach || break
      done
  fi
  ```

- 自动连接已存在的会话，否则重开

  ```
  if [[ -z "$TMUX" ]] ;then
      ID="`tmux ls | grep -vm1 attached | cut -d: -f1`" # get the id of a deattached session
      if [[ -z "$ID" ]] ;then # if not available create a new one
          tmux new-session
      else
          tmux attach-session -t "$ID" # if available attach to it
      fi
  fi
  ```

</details>
