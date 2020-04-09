# scp

scp(secure copy)��������Linux�½���Զ���ļ����������scp�Ĵ����Ǽ��ܵģ����Կ��ܻ���΢Ӱ���ٶ�

## scp���������

- -1 ǿ��scpʹ��Э��ssh1
- -2 ǿ��scpʹ��Э��ssh2
- -4 ǿ��scpֻʹ��IPv4Ѱַ
- -6 ǿ��scpֻʹ��IPv6Ѱַ
- -r �ݹ鸴������Ŀ¼
- -C ����ѹ��(��-C��־���ݸ�ssh���Ӷ���ѹ������)
- -p ����ԭ�ļ����޸�ʱ�䣬����ʱ��ͷ���Ȩ��
- -q ����ģʽ������ʾ��������������漰�����Ϣ
- -B ʹ��������ģʽ(��������в�ѯ�ʴ����������)
- -v ��ϸ��ʽ��ʾ�����scp��ssh����ʾ���������̵ĵ�����Ϣ
- -P port ָ�����ݴ����õ��Ķ˿ں�
- -l ����������ٶȣ���λΪkbit/s
- -F ssh_config ָ��һ��ssh�����ļ����˲���ֱ�Ӵ��ݸ�ssh
- -i identity_file ��ָ���ļ��ж�ȡ����ʱʹ�õ���Կ�ļ����˲���ֱ�Ӵ��ݸ�ssh
- -c cipher ��cipher�����ݴ�����м��ܣ����ѡ�ֱ�Ӵ��ݸ�ssh
- -S program ָ�����ܴ���ʱ��ʹ�õĳ��򣬴˳�������ܹ����ssh��ѡ��
- -o ssh_option ͨ��������Ϊssh����ĳ����������

## scpʹ�÷�ʽ��

- Զ���ļ�/Ŀ¼���ص����أ�
  ```
  scp user@host:/val/file.tar.gz /val/file.tar.gz
  scp -r user@host:/val/dir/ /val/dir/
  # ��Զ�˶���ļ����ص�����
  scp user@host:/path/dir/\{foot.txt,bar.txt\} .
  ```

- �����ļ�/Ŀ¼�ϴ���Զ�ˣ�
  ```
  scp /val/file.tar.gz user@host:/val/file.tar.gz
  scp -r /val/dir/ user@host:/val/dir/
  # ������ļ��ϴ���Զ��Ŀ¼
  scp foo.txt bar.txt user@host:/path/dir/
  ```

- ���ļ���һ��Զ���������Ƶ���һ��Զ������
  ```
  scp user1@host1:/path/foo.txt user2@host2:/path/dir/
  ```