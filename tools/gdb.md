# GDB���Թ���

## 1. ������GDB����

ʹ��gdb���ԣ�����ʱҪ��-gѡ���ʹ��-O���Ż�

### 1.1 ��������

| ���� | ��д | ����˵�� |
| :--- | :--- | :------- |
| list | l | ��ʾ����Դ���� |
| break n | b n | �ڵ�n�����öϵ� |
| break if | b if | ������ĳ������ʱֹͣ |
| delete n | d n | ɾ���ϵ� |
| disable |  | ���öϵ� |
| enable |  | ���öϵ� |
| info | i | ��������״̬�����磺i break��ʾ����Щ�ϵ� |
| run | r | ��ʼ���г��� |
| display | disp | ���ٲ鿴ĳ��������ÿ��ͣ��������ʾ��ֵ |
| print | p | ��ӡ�ڲ�����ֵ |
| watch |  | ���ӱ����¾�ֵ�仯 |
| step | s | ��һ�� |
| next | n | ��һ����� |
| continue | c | �������г���ֱ��������һ���ϵ� |
| finish |  | ������ǰ���� |
| set var name = v |  | ���ñ�����ֵ |
| backtrace | bt | �鿴��ջ |
| start |  | ��ʼִ�г�����main�����ĵ�һ�����ǰͣ�� |
| frame | f | �鿴ջ֡ |
| quit | q | �뿪gdb |
| edit |  | ��gdb�н��б༭ |
| whatis |  | �鿴���������� |
| search |  | ����Դ�ļ��е��ı� |
| file |  | װ����Ҫ���Եĳ��� |
| kill |  | ��ֹ���ڵ��Եĳ��� |


### 1.2 gdb���Զ����

1. �����з�������Ȼ���ҵ�Ŀ���ӽ��̵�PID���ٽ��丽��(attach)��gdb������
  ```
  attach <pid>
  ```

2. ������ѡ��`follow-work-mode`
  `follow-fork-mode`ѡ����������ѡ�������ִ��forkϵͳ����֮���Ǽ������Ը����̻��ǵ����ӽ��̣�������gdb֮��ͨ��������������ã�
  ```
  set follow-fork-mode child  //�����ӽ���
  set follow-fork-mode parent //���Ը�����
  ```
3. ������ѡ��`detach-on-fork`
  `detach-on-fork`ѡ��ָʾgdb��fork�����ĳ������ʱ���ǶϿ�(detach)��һ�����̵ĵ��Ի��ǽ���gdb����
  ```
  set detach-on-fork [on|off]
  ```
  - on����ʾ�Ͽ���һ������
  - off��gdb�����Ƹ����̺��ӽ��̡���follow-frok-modeָ���Ľ��̱�����ʱ����һ�����̴�����ͣ(suspended)״̬

### 1.3. gdb���Զ��߳�

gdb��һ������ɸ������̳߳���ĵ��ԣ�

- info threads����ʽ��ǰ�ɵ��Ե������̡߳�gdb��Ϊÿ���̷߳���һ��ID�����ǿ���ʹ�����ID��������Ӧ���̣߳�IDǰ��*�ŵ��߳��ǵ�ǰ�����Ե��߳�

- thread ID������Ŀ��IDָ�����߳�

- set scheduler-locking [off|on|step]�����Զ��̳߳���ʱ��Ĭ�ϳ��˱����Ե��߳���ִ���⣬�����߳�Ҳ�ڼ���ִ�С�ͨ������������ֻ�ñ����Ե��߳����У�

  ����������scheduler-locking��ֵ��
  - off�����������κ��̣߳��������̶߳����Լ���ִ��
  - on��ʾֻ�е�ǰ�����̻߳����ִ��
  - step��ʾ�ڵ���ִ��ʱ������next��һ�����������(����ʵ��һ�����öϵ�Ȼ��continue����Ϊ)���⣬ֻ�е�ǰ�߳�ִ��

���Խ��̳غ��̳߳س���ʱ�������Ƚ����еĽ��̸������̸߳���������1���Թ۲�����߼��Ƿ���ȷ��Ȼ�������ӽ��̺��̵߳��������Ե��Խ��̻��̵߳�ͬ���Ƿ���ȷ

### 1.4. ����core dump

core dump�ֽк���ת��, ���������й����з����쳣, �����쳣�˳�ʱ, �ɲ���ϵͳ�ѳ���ǰ���ڴ�״���洢��һ��core�ļ���, ��core dump. (linux������ڴ�Խ����յ�SIGSEGV�źţ�Ȼ��ͻ�core dump)

#### 1.4.1 ���segment fault������core dump�Ŀ���ԭ��

- �ڴ����Խ��

  - ����ʹ�ô�����±꣬�����������Խ��

  - �����ַ���ʱ�������ַ������������ж��ַ����Ƿ�����������ַ���û��������ʹ�ý�����

  - ʹ��strcpy, strcat, sprintf, strcmp, strcasecmp���ַ���������������Ŀ���ַ�����/д����Ӧ��ʹ��strncpy, strlcpy, strncat, strlcat, snprintf, strncmp, strncasecmp�Ⱥ�����ֹ��дԽ�硣

- ���̳߳���ʹ�����̲߳���ȫ�ĺ���

- ���̶߳�д������δ�������������ڻᱻ����߳�ͬʱ���ʵ�ȫ�����ݣ�Ӧ��ע�����������������������core dump

- �Ƿ�ָ��

  - ʹ�ÿ�ָ��

  - ����ʹ��ָ��ת����һ��ָ��һ���ڴ��ָ�룬����ȷ������ڴ�ԭ�Ⱦͷ���Ϊĳ�ֽṹ�����ͣ��������ֽṹ�����͵����飬����Ҫ����ת��Ϊ���ֽṹ�����͵�ָ�룬��Ӧ�ý�����ڴ濽����һ�����ֽṹ�������У��ٷ�������ṹ�����͡�������Ϊ�������ڴ�Ŀ�ʼ��ַ���ǰ������ֽṹ�����Ͷ���ģ���ô������ʱ�ͺ�������Ϊbus error��core dump.

- ��ջ���.��Ҫʹ�ô�ľֲ���������Ϊ�ֲ�������������ջ�ϣ�������������ɶ�ջ������ƻ�ϵͳ��ջ�Ͷѽṹ�����³���Ī������Ĵ���

#### 1.4.2 ���ò���ϵͳʹ�����core�ļ�

����ͨ��ulimit����鿴һ��ϵͳ�Ƿ�����֧����dump core�Ĺ��ܡ�ͨ��ulimit -c��ulimit -a�����Բ鿴core file��С��������������Ϊ0�����ʾϵͳ�ر���dump core������ͨ��ulimit -c unlimited���򿪡� **�������˶δ��󣬵�û��core dump������������ϵͳ��ֹcore�ļ������ɡ�**

�������:
```
$ulimit -c unlimited������ֻ�Ե�ǰshell������Ч��
```
����~/.bashr*���������룺 ulimit -c unlimited ��һ�����ݣ�

�鿴ϵͳ�Ƿ��ֹcore�ļ����ɣ�

```
\# ulimit -c

0

$ ulimit -a

core file size          (blocks, -c) 0

data seg size           (kbytes, -d) unlimited

file size               (blocks, -f) unlimited
```

#### 1.4.3 ��gdb�鿴core�ļ�

����core dump֮��, ��gdb���в鿴core�ļ�������, �Զ�λ�ļ�������core dump����.

```
gdb [exec file]  \[ core file]
```

��: 

```
gdb ./test test.core
```

#### 1.4.4 ʹ��core�ļ���λcore dumpλ��

��ʹ������ gdb [exec file]  \[ core file]�鿴core�ļ���Ȼ������where���gdb�ͻ����coredump��λ�á�


### 1.5. ���Ժ�

���Ժ���Ҫgcc�ڱ���ʱ����`-ggdb3`������Ȼ�����ʹ�������gdb������������鿴�꣺

- info macro���鿴���������Щ�ļ������ã��Լ��궨����ʲô����
- macro���鿴��չ��������

### 1.6. Դ�ļ�

��ʱ��ʹ��gdb������ʾ�Ҳ���Դ�ļ�����ʱ����Ҫע�����㣺

- ����ʱ�Ƿ��-g�����Լ�����debug��Ϣ
- Դ��·���Ƿ�������ȷ������ʹ��gdb��`directory`����������Դ�ļ���Ŀ¼

### 1.7. �����ϵ�

```
break [where] if [condition]
```

### 1.8. �����в���

������Եĳ�������ʱ��Ҫ�����в����������ַ������ã�

- gdb�����е�`-args`����
- gdb������`set args`����

### 1.9. x����

����������鿴�ڴ�

### 1.10. command����

command������Խ�һ��gdb�����������ϵ㵽��ʱ���Զ�ִ��command�����gdb����

### 1.11. ���Խű�

�ŵ㣺

- �Լ�����һЩ�������������ӡSTL�����е�����
- ����ÿ�δ�gdb��Ҫ���´�һ�ζϵ�

ʹ�÷�����

һ�������ַ�����https://blog.csdn.net/cnsword/article/details/16337031

���õĵ��Խű��Ƽ���

- �鿴STL������http://www.yolinux.com/TUTORIALS/src/dbinit_stl_views-1.03.txt
- gdb init��https://github.com/gdbinit/Gdbinit/blob/master/gdbinit

�ο���

[gdb��Ӧ��֪���ļ������Է���](https://coolshell.cn/articles/3643.html)

[ʹ��gdb���Զ���̳���](https://www.ibm.com/developerworks/cn/linux/l-cn-gdbmp/index.html)

## 2. ͼ��������

### 2.1 gdb�Դ���tui

```
gdb --tui a.out
```

�������ʹ�÷����ο�[�ò���](https://blog.csdn.net/xu415/article/details/19021759)

### 2.2 ���������ʾ���Խ���---gdbgui

[Github��Ŀ��ַ](https://github.com/cs01/gdbgui)

#### 2.2.1 ��װ��

```
curl https://raw.githubusercontent.com/cs01/pipx/master/get-pipx.py | python3

pipx install gdbgui
```

#### 2.2.2 ʹ�ã�

```
gdbgui -p 10001 -r "a.out"
```
-p �ƶ��˿ں� -r ��ʾԶ��remote����

����֮��Ϳ����ڱ�����������Է���������

[�ο��̳�](https://blog.csdn.net/songchuwang1868/article/details/86132281)

## 3. ��������

- �鿴vector����

```
*(YOURVECTOR._M_impl._M_start)@(YOURVECTOR.size())
```