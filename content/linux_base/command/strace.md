# strace

straceֻ��ͳ�Ʒ������ں�̬�ĳ����쳣��������Ϸ������û�̬����Ҫʹ��[ltrace](command/ltrace.md)

## strace��ʲô��

strace��һ����������ϡ����Ե�Linux�û��ռ����������������������û��ռ���̺��ں˵Ľ���������ϵͳ���á��źŴ��ݡ�����״̬�����

> strace�ĵײ�ʹ���ں˵�ptrace������ʵ���书��

���Ƕ�֪������Linux�У����̲�����ֱ�ӷ���Ӳ���豸�����Խ����ڶ�ȡ�����ļ��������������ݵȲ���ʱ����Ҫ���û�̬ģʽ�л����ں�̬��Ȼ�����ϵͳ�������������в�������strace�����ͨ�����һ�����̲�����ϵͳ���ã����������������ֵ��ִ�����ĵ�ʱ�䡢���ô������ɹ���ʧ�ܵĴ��������˽�һ������

**һ���򵥵�������˵����**

�����и���some_serve�������������ʱ�����鿴��־�����ʱֻ�ܿ������ƺ��ǳ�ʼ����־ʧ�ܣ�������ʲôԭ���µ��أ�

�������

```
./some_server ./conf/some_server.conf
```

�����

```
FATAL: InitLogFile failed
```

��ʱ�����ǿ���ʹ��strace������
```
strace -tt -f ./some_server ./conf/some_server.conf
```
�鿴�����ʱ�����ǿ��Կ������������ǰ�и�openϵͳ���õ���ʧ��:

```
open("/usr/local/apps/some_server/log//server_agent.log", O_RDWR|O_CREAT|O_APPEND|O_LARGEFILE, 0666) = -1 ENOENT (No such file or directory)
```
open���ش�����-1��ϵͳ�����ΪENOENT������ͨ���鿴openϵͳ���õ�man�ֲᣬ�ҵ�ENOENT��Ӧ�Ĵ�����ԭ�򼴿ɽ��������


## strace��ô�ã�

### strace��������ģʽ

- һ����ͨ��������Ҫ���ٵĽ��̣���ʱ��ԭ��������ǰ����strace���ɡ���������Ҫ���� "ls -lh /var/log/messages" ��������ִ�У�����������

  ```
  strace ls -lh /var/log/messages
  ```

- ����һ���Ǹ����Ѿ������еĽ��̣��ڲ��жϽ���ִ�е�����£�������ڸ�� ��ʱ��strace���ݸ�-p pid ѡ��ɡ�

  ```
  //�ȵõ�����Ľ���id
  pidof some_server
  //Ȼ����ٸý���
  strace -p <pid>
  ```
### strace����ѡ��

- -tt ÿ�����ǰ����ʾ���뼶���ʱ��
- -T ��ʾÿ��ϵͳ���û��ѵ�ʱ��
- -v ��ĳЩϵͳ���ã���ӡ�����Ļ����������ļ�stat�ṹ
- -f ׷��Ŀ����̼��������ӽ���
- -e ����Ҫ���ٵ��¼��͸�����Ϊ������ָ��Ҫ���ٵ�ϵͳ��������
- -o ��strace���������д��ָ���ļ�
- -s ��ϵͳ���õ�ĳ���������ַ���ʱ��������ָ�����ȵ����ݣ�Ĭ��32�ֽ�
- -p ָ��Ҫ���ٵĽ���pid��Ҫ���ٶ��pid���ظ����-pѡ���

���磺����nginx��������ʱ����������Щ�ļ���
```
strace -tt -T -f -e trace=file -o /data/log/strace.log -s 1024 ./nginx
```
����`-e trace=file`ָ��ֻ��ʾ���ļ�������ص�ϵͳ���ã����������õ�ѡ��У�

- -e trace=file ���ٺ��ļ�������صĵ���(���������ļ���)
- -e trace=process �ͽ��̹�����صĵ��ã���fork/exec/exit_group
- -e trace=network ������ͨ����صĵ��ã���socket/sendto/connect
- -e trace=signal �źŷ��ͺʹ�����ص��ã���kill/sigaction
- -e trace=desc ���ļ���������ص��ã���write/read/select/epoll
- -e trace=ipc �ͽ��̼�ͨ����ص��ã���shmget

�����������£�����ʹ�������������־͹��ˣ����ʵ����Ҫ���پ����ϵͳ����ʱ��Ҫע��c��͵ײ�ϵͳ���õ�����

> ���磬����֪����������ʹ�õ�fork����������glibc�У�fork����ʵ����ӳ�䵽�˸��ײ��cloneϵͳ���á�����ʹ��straceʱ����ָ��-e trace=clone��������-e trace=fork

## strace���ⶨλ����

### ��λ�����쳣�˳�

���⣺

> �������и�����run.sh�ĳ�פ�ű�������һ���Ӻ����������Ҫ�������

��λ��

���̻�������ʱ��ͨ��ps�����ȡ��pid������õ���pidΪ24298
```
strace -o strace.log -tt -p 24298
```
�鿴strace.log�����������2�п����������ݣ�
```
22:47:42.803937 wait4(-1,  <unfinished ...>
22:47:43.228422 +++ killed by SIGKILL +++
```
���Կ����������Ǳ�����������KILL�ź�ɱ���ġ�ͨ���������֣��ǻ����ϵ�һ����ؽű��ڼ��һ������run.sh�Ľ��̣�������run.sh�Ľ���������2ʱ���ͻ����ɱ��������������¸�run.sh�ű�����ɱ

���̱�ɱ�˳�ʱ��strace�����kill by SIGX(SIGX��ʾ���͸����̵��ź�)����ô�������Լ��˳�ʱ�����ʲô�أ�

������ĳ���test_exitΪ����ʹ��strace�������˳�ʱ�������
```
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
       exit(1);
}
```

ʹ��strace���ٸó���
```
strace -tt -e trace=process -f ./test_exit
```

�����
```
23:07:24.672849 execve("./test_exit", ["./test_exit"], [/* 35 vars */]) = 0
23:07:24.674665 arch_prctl(ARCH_SET_FS, 0x7f1c0eca7740) = 0
23:07:24.675108 exit_group(1)           = ?
23:07:24.675259 +++ exited with 1 +++
```

���Կ����������Լ��˳�ʱ(����exit���������main��������)�����յ��õ�exit_groupϵͳ���ã�����strace�����exited with x(xΪ�˳���)

> exit_group��exit�����ײ��������õ�ϵͳ����

### ��λ�����ڴ��쳣

�и�������������
```
shmget 267264 30097568: Invalid argument
Can not get shm...exit!
```

������־��Ÿ������ǻ�ȡ�����ڴ�ʱ����ͨ��strace�鿴��
```
strace -tt -f -e trace=ipc ./a_mon_svr ../conf/a_mon_svr.conf
```

�����
```
22:46:36.351798 shmget(0x5feb, 12000, 0666) = 0
22:46:36.351939 shmat(0, 0, 0)          = ?
Process 21406 attached
22:46:36.355439 shmget(0x41400, 30097568, 0666) = -1 EINVAL (Invalid argument)
shmget 267264 30097568: Invalid argument
Can not get shm...exit!
```

ͨ��strace�����������֪����shmgetϵͳ���ó����ˣ�errno��EINVAL��Ȼ�����ǾͿ���ͨ���鿴shmget��man�ֲ�ȥ��ѯ����ԭ����

### ���ܷ���

����������shell�ű����ͬ���Ĺ��ܣ�������Ҫ�Ա������ű���ϵͳ���������������ʱ�����

����ʹ��strace��`-c`��`-f`ѡ��ֱ�ͳ��ʱ���ͬʱͳ��ÿ�����̵��ӽ������

[�ο�����](https://www.linuxidc.com/Linux/2018-01/150654.htm)
