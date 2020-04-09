| ���� | Ч�� |
| --- | --- |
| `ssh -D 7001 -fTNnC root@129.226.69.149` | sock5�������ض˿�7001������ת����Զ�̷�����129.226.69.149ת����ȥ |
| `ssh -CqTnN -L 0.0.0.0:8443:192.168.1.2:443  user@192.168.1.3` | �������������������8443�˿ڣ�ͨ��192.168.1.3ת����192.168.1.2:443 |
| `ssh -CqTnN -R 0.0.0.0:8443:192.168.1.2:443  user@202.115.8.1` | �������������������202.115.8.1���˿ڣ�8443��ת������������ 192.168.1.2:443 |
| `python -m SimpleHTTPServer 8000` | ����python����һ���򵥵ı��ط�����,rootΪ��������Ŀ¼ |
| <code>history \| awk '{a[$2]++}END{for(i in a){print a[i] " " i}}' \| sort -rn \| head</code> | �г��ʹ�õ�ʮ������ |
| <code>netstat -n \| awk '/^tcp/ {++tt[$NF]} END {for (a in tt) print a, tt[a]}'</code> | �г���������״̬��ESTABLISHED/TIME_WAIT/FIN_WAIT1/FIN_WAIT2 |
| `sshfs name@server:/path/to/folder /path/to/mount/point` | ʹ��ssh����Զ���ļ�Ŀ¼������ |
| <code>ps aux \| sort -nk +4 \| tail</code> | ��ʾǰʮ�����еĽ��̲����ڴ�ʹ�������� |
| `while sleep 1;do tput sc;tput cup 0 $(($(tput cols)-29));date;tput rc;done&` | �ն����Ͻ���ʾʱ�� |
| <code>wget -qO - "http://www.tarball.com/tarball.gz" \| tar zxvf -</code> | �������ϵ�ѹ���ļ��н��һ���ļ��У������Ᵽ���м��ļ� |
| `python -c "import test.pystone;print(test.pystone.pystones())"` | ���ܲ��ԣ��������������� |
| `dd if=/dev/zero of=/dev/null bs=1M count=32768` | ���ܲ��ԣ������ڴ���� |
| `mount /path/to/file.iso /mnt/cdrom -oloop` | Linux�¹���һ��iso�ļ� |
| `ssh -t hostA ssh hostB` | ͨ������Aֱ��ssh������B |
| `wget -r -l1 --no-parent -nH -nd -P/tmp -A".gif,.jpg" http://example.com/images` | ����һ����վ������ͼƬ |
| <code>lsof -P -i -n \| cut -f 1 -d " " \| uniq \| tail -n +2</code> | ��ʾ��ǰ����ʹ������Ľ��� |
| `:w !sudo tee > /dev/null %` | vim�б���һ��û��Ȩ�޵��ļ� |
| **grep** |  |
| `grep -i "the" demo_file` | �ļ��в����ַ��� |
| `grep -r "ramesh" *` | ��һ���ļ����µݹ���Ұ����ַ���"ramesh"���ļ� |
| `grep -A 3 -i "the" demo_file` | ����ɹ�ƥ������Լ�֮������� |
| **�ļ�����** |  |
| `find . -iname *.c` | ���ҵ�ǰĿ¼����.c��β���ļ������Դ�Сд |
| `find . -type f -newermt "2010-01-01" ! -newermt "2010-06-01"` | �������ڷ�Χ�����ļ� |
| <code>find / -size +500M -print0 \| xargs -0 du -m \| sort -nr</code> | ����500M���ϵĴ��ļ������ļ���С������� |
| `find -iname "MyProgram.c" -exec md5sum {} \` | ���ҵ����ļ�ִ��ĳ������ |
| `find ~ -empty` | ���Ҽ�Ŀ¼�µĿ��ļ� |
| **�������** |  |
| `apt install xxx` | ��װ��� |
| `apt update && apt upgrade` | ����ϵͳ |
| `apt remove xxx` | ж����� |
| `dpkg -i xxx.deb` | ��װ������� |
| `dpkg --list` | �г�����װ������� |
| `dpkg --status package_name` | ȷ���Ƿ�װ��һ������� |
| `apt-cache show package_name` | ��ʾ����װ���������Ϣ |
| `dpkg --search file_name` | ���Ұ�װ��ĳ���ļ�������� |
| **��ѹ�����** |  |
| `tar cvf archive_name.tar dirname/` | ����һ���µ�tar�ļ� |
| `tar xvf archive_name.tar` | ��ѹtar�ļ� |
| `tar tvf archive_name.tar` | �鿴tar�ļ� |
| `tar -xvJf archine_name.tar.xz` | ��ѹtar.xz�ļ� |
| `xz -z test.tar` | ��tar��ѹ��Ϊxz�ļ� |
| `gzip test.txt` | ����һ��*.gz��ѹ���ļ� |
| `gzip -d test.txt.gz` | ��ѹ*.gz�ļ� |
| `gzip -l test.txt.gz` | ��ʾѹ������ |
| `tar zxvf test.tar.gz -C dir/` | ��ѹ*.tar.gz�ļ���ָ���ļ��� |
| `bzip2 test.txt` | ����*.bz2ѹ���ļ� |
| `bzip2 -d test.txt.gz` | ��ѹ*.bz2�ļ� |
| <code>objdump -x xxx.so \| grep NEEDED</code> | linux�鿴�����Ŀ� |
| <code>objdump -x ��ִ�г����� \| grep NEEDED</code> | �鿴��ִ�г��������Ŀ� |
| `ldd xxx.so` | �鿴ȱ�ٵĿ� |


| ���� | ˵�� |
| --- | --- |
| exit                | �˳���ǰ��½ |
| env                 | ��ʾ�������� |
| echo $SHELL         | ��ʾ����ʹ��ʲô SHELL |
| bash                | ʹ�� bash���� exit ���� |
| which bash          | ���� $PATH�������ĸ������Ӧ���� bash |
| whereis bash        | ������ִ�У�ͷ�ļ��Ͱ�����Ϣ��λ�ã�ʹ��ϵͳ�ڽ����ݿ� |
| whatis bash         | �鿴ĳ������Ľ��ͣ�һ�仰���������Ǹ�ʲô�� |
| clear               | �����Ļ���� |
| reset               | �����նˣ����㲻С�� cat ��һ�������ƣ��ն�״̬�ҵ�ʱʹ�ã� |


## Ŀ¼����

| ���� | ˵�� |
| --- | --- |
| pushd {dirname}     | Ŀ¼ѹջ��������Ŀ¼ |
| popd                | ����������ջ����Ŀ¼ |
| dirs -v             | �г���ǰĿ¼ջ |
| cd -                | �ص�֮ǰ��Ŀ¼ |
| cd -{N}             | �л���Ŀ¼ջ�еĵ� N��Ŀ¼������ cd -2 ���л����ڶ��� |


## �ļ�����

| ���� | ˵�� |
| --- | --- |
| ls                  | ��ʾ��ǰĿ¼���ݣ�����ɽ�Ŀ¼����ls {dir} ��ʾָ��Ŀ¼ |
| ls -l               | �б�ʽ��ʾĿ¼���ݣ������ļ����ڣ���С��Ȩ�޵���Ϣ |
| ls -1               | �б�ʽ��ʾĿ¼���ݣ�ֻ��ʾ�ļ����ƣ����ź��������� 1 |
| ls -a               | ��ʾ�����ļ���Ŀ¼�����������ļ���.��ͷ���ļ�/Ŀ¼���� |
| ln -s {fn} {link}   | ��ָ���ļ�����һ�������� |
| cp {src} {dest}     | �����ļ���cp -r dir1 dir2 ���Եݹ鿽����Ŀ¼�� |
| rm {fn}             | ɾ���ļ���rm -r �ݹ�ɾ��Ŀ¼��rm -f ǿ��ɾ�� |
| mv {src} {dest}     | �ƶ��ļ������ dest ��Ŀ¼�����ƶ������ļ����򸲸� |
| touch {fn}          | �������߸���һ���ƶ��ļ� |
| cat {fn}            | ����ļ�ԭʼ���� |
| any_cmd > {fn}      | ִ�������������׼����ض���ָ���ļ� |
| more {fn}           | ������ʾĳ�ļ����ݣ��ո�ҳ��q �˳� |
| less {fn}           | ���߼���� more�����������q �˳� |
| head {fn}           | ��ʾ�ļ�ͷ�����У����� head -3 abc.txt ��ʾͷ���� |
| tail {fn}           | ��ʾ�ļ�β�����У����� tail -3 abc.txt ��ʾβ������ |
| tail -f {fn}        | ������ʾ�ļ�β�����ݣ������ڼ����־ |
| nano {fn}           | ʹ�� nano �༭���༭�ļ� |
| vim {fn}            | ʹ�� vim �༭�ļ� |
| diff {f1} {f2}      | �Ƚ������ļ������� |
| wc {fn}             | ͳ���ļ��ж����У����ٸ����� |
| chmod 644 {fn}      | �޸��ļ�Ȩ��Ϊ 644�����Խ� -R ��Ŀ¼ѭ����Ȩ�� |
| chgrp group {fn}    | �޸��ļ��������û��� |
| chown user1 {fn}    | �޸��ļ�������Ϊ user1, chown user1:group1 fn �����޸��� |
| file {fn}           | ����ļ������ͺͱ��� |
| basename {fn}       | �鿴�ļ������֣�������·���� |
| dirname {fn}        | �鿴�ļ���·�������������֣� |
| grep {pat} {fn}     | ���ļ��в��ҳ��ֹ� pat ������ |
| grep -r {pat} .     | �ڵ�ǰĿ¼�µݹ�������г��ֹ� pat ���ļ����� |
| stat {fn}           | ��ʾ�ļ�����ϸ��Ϣ |



## �û�����

| ���� | ˵�� |
| --- | --- |
| whoami              | ��ʾ�ҵ��û��� |
| who                 | ��ʾ�ѵ�½�û���Ϣ��w / who / users �������в�ͬ |
| w                   | ��ʾ�ѵ�½�û���Ϣ��w / who / users �������в�ͬ |
| users               | ��ʾ�ѵ�½�û���Ϣ��w / who / users �������в�ͬ |
| passwd              | �޸����룬passwd {user} �������� root �޸ı������� |
| finger {user}       | ��ʾĳ�û���Ϣ������ id, ����, ��½״̬�� |
| adduser {user}      | ����û� |
| deluser {user}      | ɾ���û� |
| su                  | �л��� root �û� |
| su -                | �л��� root �û�����½��ִ�е�½�ű��� |
| su {user}           | �л���ĳ�û� |
| su -{user}          | �л���ĳ�û�����½��ִ�е�½�ű��� |
| id {user}           | �鿴�û��� uid��gid �Լ����������û��� |
| id -u {user}        | ��ӡ�û� uid |
| id -g {user}        | ��ӡ�û� gid |
| write {user}        | ��ĳ�û�����һ����Ϣ |
| last                | ��ʾ����û���½�б� |
| last {user}         | ��ʾ��½��¼ |
| lastb               | ��ʾʧ�ܵ�½��¼ |
| lastlog             | ��ʾ�����û��������½��¼ |
| sudo {command}      | �� root Ȩ��ִ��ĳ���� |

## ���̹���

| ���� | ˵�� |
| --- | --- |
| ps                        | �鿴��ǰ�Ự���� |
| ps ax                     | �鿴���н��̣����� ps -e |
| ps aux                    | �鿴���н�����ϸ��Ϣ������ ps -ef |
| ps auxww                  | �鿴���н��̣�������ʾ���̵������������� |
| ps -u {user}              | �鿴ĳ�û����� |
| ps axjf                   | �г������� |
| ps xjf -u {user}          | �г�ĳ�û��Ľ����� |
| ps -eo pid,user,command   | ���û�ָ���ĸ�ʽ�鿴���� |
| ps aux | grep httpd       | �鿴��Ϊ httpd �����н��� |
| ps --ppid {pid}           | �鿴������Ϊ pid �����н��� |
| pstree                    | �����г����н��̣�pstree Ĭ��һ�㲻�����谲װ |
| pstree {user}             | �������г�ĳ�û��Ľ��� |
| pstree -u                 | �����г����н����Լ������û� |
| pgrep {procname}          | ��������ƥ��Ľ��̵� pid������ pgrep apache2 |
| kill {pid}                | �������� |
| kill -9 {pid}             | ǿ�ƽ������̣�9/SIGKILL ��ǿ�Ʋ��ɲ�������ź� |
| kill -KILL {pid}          | ǿ��ִ�н��̣�kill -9 ������һ��д�� |
| kill -l                   | �鿴�����ź� |
| kill -l TERM              | �鿴 TERM �źŵı�� |
| killall {procname}        | �����ƽ������н��� |
| pkill {procname}          | �����ƽ������̣��������⻹�������������� |
| top                       | �鿴���Ծ�Ľ��� |
| top -u {user}             | �鿴ĳ�û����Ծ�Ľ��� |
| any_command &             | �ں�̨����ĳ���Ҳ���� CTRL+Z ����ǰ���̹ҵ���̨ |
| jobs                      | �鿴���к�̨���̣�jobs�� |
| bg                        | �鿴��̨���̣����л���ȥ |
| fg                        | �л���̨���̵�ǰ̨ |
| fg {job}                  | �л��ض���̨���̵�ǰ̨ |
| trap cmd sig1 sig2        | �ڽű��������źŴ������� |
| trap "" sig1 sig2         | �ڽű�������ĳ�ź� |
| trap - sig1 sig2          | �ָ�Ĭ���źŴ�����Ϊ |
| nohup {command}           | ��������ĳ���������˳���½������������ |
| nohup {command} &         | �ں�̨��������ĳ���� |
| disown {PID|JID}          | �����̴Ӻ�̨�����б�jobs���Ƴ� |
| wait                      | �ȴ����к�̨����������� |

## �������SSH / ϵͳ��Ϣ / ����

| ���� | ˵�� |
| --- | --- |
| ssh user@host             | ���û� user ��½��Զ������ host |
| ssh -p {port} user@host   | ָ���˿ڵ�½���� |
| ssh-copy-id user@host     | ������� ssh key ��Զ�������������ظ��������� |
| scp {fn} user@host:path   | �����ļ���Զ������ |
| scp user@host:path dest   | ��Զ�����������ļ����� |
| scp -P {port} ...         | ָ���˿�Զ�̿����ļ� |
| uname -a                  | �鿴�ں˰汾����Ϣ |
| man {help}                | �鿴���� |
| man -k {keyword}          | �鿴��Щ�����ĵ�������˸ùؼ��� |
| info {help}               | �鿴 info pages���� man ��ǿ�İ���ϵͳ |
| uptime                    | �鿴ϵͳ����ʱ�� |
| date                      | ��ʾ���� |
| cal                       | ��ʾ���� |
| vmstat                    | ��ʾ�ڴ�� CPU ʹ����� |
| vmstat 10                 | ÿ 10 ���ӡһ���ڴ�� CPU�����CTRL+C �˳� |
| free                      | ��ʾ�ڴ�ͽ�����ʹ����� |
| df                        | ��ʾ����ʹ����� |
| du                        | ��ʾ��ǰĿ¼ռ�ã�du . --max-depth=2 ����ָ����� |
| uname                     | ��ʾϵͳ�汾�� |
| hostname                  | ��ʾ�������� |
| showkey -a                | �鿴�ն˷��͵İ������� |
| ping {host}               | ping Զ����������ʾ�����CTRL+C �˳� |
| ping -c N {host}          | ping Զ������ N �� |
| traceroute {host}         | ���·����ͨ��� |
| mtr {host}                | �߼��汾 traceroute |
| host {domain}             | DNS ��ѯ��{domain} ǰ��ɼ� -a �鿴��ϸ��Ϣ |
| whois {domain}            | ȡ������ whois ��Ϣ |
| dig {domain}              | ȡ������ dns ��Ϣ |
| route -n                  | �鿴·�ɱ� |
| netstat -a                | �г����ж˿� |
| netstat -an               | �鿴����������Ϣ������������ |
| netstat -anp              | �鿴����������Ϣ������������Ϣ����Ҫ sudo�� |
| netstat -l                | �鿴���м����Ķ˿� |
| netstat -t                | �鿴���� TCP ���� |
| netstat -lntu             | ��ʾ�������ڼ����� TCP �� UDP ��Ϣ |
| netstat -lntup            | ��ʾ�������ڼ����� socket ��������Ϣ |
| netstat -i                | ��ʾ������Ϣ |
| netstat -rn               | ��ʾ��ǰϵͳ·�ɱ�ͬ route -n |
| ss -an                    | �� netstat -an �����ٸ���ϸ |
| ss -s                     | ͳ�� TCP �� established, wait �� |
| wget {url}                | �����ļ����ɼ� --no-check-certificate ���� ssl ��֤ |
| wget -qO- {url}           | �����ļ����������׼����������棩 |
| curl -sL {url}            | ͬ wget -qO- {url} û�� wget ��ʱ��ʹ�� |
| sz {file}                 | �����ļ����նˣ�zmodem Э�� |
| rz                        | �����ն˷��͹������ļ� |
