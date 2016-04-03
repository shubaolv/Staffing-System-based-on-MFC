# Staffing-System-based-on-MFC
在Windows平台下利用VS2012和MySQL开发的一款员工管理软件，支持员工信息和业绩的批量及单独导入，能查询指定时间段指定员工及其所有直接间接分管下属的业绩总和，在统计员工工资业绩上提供了便利。</br>
对于给定的员工信息的文件要实现批量的导入，并提供单独录入的功能；在查询部分根据员工关系抽象出一个员工的树形图，并利用MySQL数据库读入对应员工指定的时间段的业绩，遍历树形员工信息图，并求取业绩和返回给图形界面。熟悉了VS2012集成开发环境，锻炼了将数据结构知识迁移到实际问题中的能力，并提高了对MySQL数据库的使用能力。
何大伯员工管理系统使用说明
Author：Shubao Lv
Date:2016-1-27 08:27
Tools：mysql-5.1-27  vs2012  
OS：Microsoft Windows [版本 10.0.10586]
前台文件组成：
			☆☆☆新员工录入：需要输入员工的个人姓名，员工号，发展他的人的姓名，员工号，以及他属于发展人的A区或B区，
							输入后点击确定输入，在员工号一栏显示”插入成功！“表示新员工加入成功
						
			☆☆☆员工个人信息查询：需要输入工的个人姓名，员工号，点击确定输入，即可显示发展他的人的姓名，员工号，以
								及他属于发展人的A区或B区本功能可以在查询员工录入是否成功时用到！
			
			☆☆☆员工业绩查询：输入员工姓名、员工号、以及查询的起止时间（1000年~9999年之间都可以查询）点击确定查询即
							可查本身以及A区和B区的总业绩
			
			☆☆☆员工业绩录入：输入员工姓名、员工号、以及业绩的时间（1000年~9999年之间都可以查询）和业绩，输入后点击
							确定输入，在员工号一栏显示
						”插入成功！“表示业绩加入成功。（插入的业绩计入到其旗下最底层的人身上）
			
			☆☆☆员工业绩录入到自身：输入员工姓名、员工号、以及业绩的时间（1000年~9999年之间都可以查询）和业绩，输入
								后点击确定输入，在员工号一栏显示”插入成功！“表示业绩加入成功。（插入的业绩计入到其本人身上）
			
			☆☆☆特别说明：由于时间匆忙加之水平有限，本系统对于用户输入错误的情况处理较少，请输入时一定要保证输入的正确性。
						 另外，在插入界面中，如果已经有“插入成功！”的返回字样，请不要再点击确定，应该重新输入你要再次输入
						 的数据，否则会造成数据库难以挽回的错误！！！
Mysql数据库文件：
				用户：root 密码：root 数据库：employee
				表格：users,works;

mysql> use employee;
Database changed

mysql> select * from users;
+------+------+-------------+-----------+-----------+</br>
| name | id   | father_name | father_id | father_ab |
+------+------+-------------+-----------+-----------+
| 我   | 001  | root        | 000       | A         |
| 张   | 002  | 我          | 001       | A         |
| 赵   | 008  | 我          | 001       | B         |
| 郑   | 009  | 我          | 001       | B         |
| 王   | 003  | 张          | 002       | A         |
| 李   | 004  | 王          | 003       | A         |
| 周   | 005  | 李          | 004       | A         |
| 吕   | 010  | 赵          | 008       | A         |
| 何   | 011  | 赵          | 008       | B         |
| 施   | 012  | 何          | 011       | A         |
| 蒋   | 013  | 施          | 012       | A         |
| 沈   | 014  | 施          | 012       | B         |
| 孙   | 006  | 王          | 003       | B         |
| 钱   | 007  | 孙          | 006       | A         |
+------+------+-------------+-----------+-----------+
14 rows in set (0.09 sec)

mysql> desc users;
+-------------+-------------+------+-----+---------+-------+
| Field       | Type        | Null | Key | Default | Extra |
+-------------+-------------+------+-----+---------+-------+
| name        | varchar(20) | YES  |     | NULL    |       |
| id          | varchar(20) | YES  |     | NULL    |       |
| father_name | varchar(20) | YES  |     | NULL    |       |
| father_id   | varchar(20) | YES  |     | NULL    |       |
| father_ab   | varchar(20) | YES  |     | NULL    |       |
+-------------+-------------+------+-----+---------+-------+
5 rows in set (0.01 sec)

mysql> desc works;
+-------+-------------+------+-----+---------+-------+
| Field | Type        | Null | Key | Default | Extra |
+-------+-------------+------+-----+---------+-------+
| id    | varchar(30) | YES  |     | NULL    |       |
| time  | date        | YES  |     | NULL    |       |
| sum   | int(11)     | YES  |     | NULL    |       |
+-------+-------------+------+-----+---------+-------+
3 rows in set (0.02 sec)

如果.exe文件运行不成功，请安装vs自己运行编译代码
mysql数据库安装目录：C:\Program Files\MySQL
// ============================================================================================================================
vs2012访问链接数据库

工具：vs2012，mysql5.0
操作系统：win64位
首先，打开vs2012新建一个c++工程（空工程就好，自己在源文件中添加一个cpp文件，用于写连接的代码），如下图所示：
 
设置一些引用文件的环境变量，点击项目->属性->vc++目录
然后“include目录”（包含目录）那把“C:\ProgramFiles\MySQL\MySQL Server 5.5\include”给加进来 
再然后“lib目录”（库目录）那里把“C:\ProgramFiles\MySQL\MySQL Server 5.0\lib”和“C:\ProgramFiles\MySQL\MySQL Server 5.0\lib\debug”
也一起加进来。以上三个文件在mysql 的安装目录下（默认在C:\ProgramFiles，或有不同）
解释一下以上三个文件的作用：
在访问数据库时要调用mysql的头文件，在其安装目录的include文件夹里；
在编译和连接时：（转）lib是编译时需要的，dll是运行时需要的。 如果要完成源代码的编译，有lib就够了。 
如果也使动态连接的程序运行起来，有dll就够    了。 在开发和调试阶段，当然最好都有。 一般的动态库
程序有lib文件和dll文件。lib文件是必须在编译期就连接到应用程序中的，而dll     文件是运行期才会被
调用的。如果有dll文件，那么对应的lib文件一般是一些索引信息，具体的实现在dll文件中。如果只有lib文件，
那么这个lib文件是静态编译出来的，索引和实现都在其中。静态编译的lib文件有好处：给用户安装时就不需要
再挂动态库了。但也有缺    点，就是导致应用程序比较大，而且失去了动态库的灵活性，在版本升级时，同时要发布新的应用程序才行。 
1. 编译是通过静态链接库（lib）去找到接口的。
2. #pragma comment (lib, "libmysql.lib")
    #pragma comment (lib, "mysqlclient.lib")

基本上做完以后的工作就可以连接mysql数据库了！
测试代码如下：
'''
[cpp] view plain copy
#include <stdio.h>  
#include <string.h>  
#include <algorithm>  
#include <iostream>  
#include "winsock.h"  
#include "mysql.h"  
using namespace std;  
#pragma comment (lib, "libmysql.lib")  
#pragma comment (lib, "mysqlclient.lib")  
  
int main()  
{  
    //connectionparams  
    char *host = "localhost";  
    char *user = "root";//mysql的用户名  
    char *pass = "123456";//你的mysql服务器密码  
    char *db = "MySql";  
    unsigned int port = 3306; //server port  
    MYSQL *sock;  
    sock=mysql_init(0);  
    if(sock &&mysql_real_connect(sock,host,user,pass,db,0,NULL,0))  
    {  
        cout<<"connect mysqlsucceed!"<<endl;  
    }  
    else  
    {  
        cout<<"I'm sorry to tell you that you wrong!"<<endl;  
    }  
    getchar();  
    //input 1 or 2 or 3  
    return 0;  
}  
'''
如果是32位操作系统以上步骤就足够了。我的电脑是64位，vs2012和mysql都是64位的，因此要修改一下项目的默认设置，否则会出现：
error LNK2019: 无法解析的外部符号 _mysql_real_connect@32，该符号在函数 _main 中被引用
error LNK2019: 无法解析的外部符号 _mysql_query@8，该符号在函数 _main 中被引用
error LNK2019: 无法解析的外部符号 _mysql_init@4，该符号在函数 _main 中被引用
error LNK2019: 无法解析的外部符号 _mysql_close@4，该符号在函数 _main 中被引用
等无法解析外部符号的错误。
点击项目->属性->配置管理器
活动解决方案平台，下拉选新建，出现一个新的对号框，在键入选择新平台中选择X64

然后重新编译就OK了
