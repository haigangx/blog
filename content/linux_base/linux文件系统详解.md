# Linux文件系统详解

Linux的文件系统要从Ext2讲起

操作系统管理文件除了要管理文件内容外，还需要管理文件的属性，如文件的rwx权限和文件属性(拥有者、群组、时间等)。文件系统通常会将这两部分内容保存到不同的区块，权限与属性放到inode中，实际文件内容则放到data block区块中。另外，还有一个超级区块(superblock)会记录整个文件系统的整体信息，包括inode和block的总量、使用量、剩余量等

每个inode与block都有编号，这三者的意义简略说明如下：

- superblock：记录此filesystem的整体信息，包括inode/block的总量、使用量、剩余量，以及文件系统的格式与相关信息
- inode：记录文件的属性，一个文件占用一个inode，同时记录此文件的数据所在的block号码
- block：实际记录文件的内容，若文件太大时，会占用多个block

superblock


[linux文件系统详解](https://blog.csdn.net/yuexiaxiaoxi27172319/article/details/45241923)

[鸟哥linux私房菜-认识Linux文件系统](https://wizardforcel.gitbooks.io/vbird-linux-basic-4e/content/59.html)