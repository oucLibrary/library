# 这里是数据库的demo

[TOC]

##DbDemo类
###属性
|属性名|数据类型|作用|
|:--------|:---------|:---------|
|id |int |主键，作为唯一标识|
|a|char[50]|作为demo数据值|

###方法
|方法名|参数|返回值|作用|
|:------|:------|:------|:------|
|DbDemo|无|DbDemo|默认构造函数|
|DbDemo|int,string|DbDemo|带参数的构造函数，用于实例化|
|GetId|无|int|获取id值|
|SetId|int|void|设置id|
|GetA|无|string|获取a的值|
|SetA|string|void|设置a的值|

##DbDemoFileOperate类
###属性
|属性名|数据类型|作用|
|:--------|:---------|:---------|
|file |fstream|记录文件操作位置|
|fileName|string|记录缓存文件的文件名|
|<font color=#ff0000>tmp_sto</font>|char *|查询结果|
|aim|char *|存储结果|
|<font color=#ff0000>currid</font>|int|当前操作的id|
|<font color=#ff0000>colnum</font>|int|列数|
|<font color=#ff0000>count</font>|int|记录条数|
|<font color=#ff0000>col</font>|vector&lt;col&gt;|每列的起始位置|

###方法
|方法名|参数|返回值|作用|
|:------|:------|:------|:------|
|DbDemoFileOperate|无|DbDemoFileOperate|默认构造函数|
|DbDemoFileOperate|char *|DbDemoFileOperate|带参数的构造函数,参数为要打开文件的文件名|
|FileWrite|char*,int(-1),bool( false)|void|添加一条数据,此时参数中的id值为无效值，将由程序自动生成|
|<font color=#ff0000>Query</font>|void|char\*,int,char\*|查询函数，第一个char\*为查询目标，int为查询目标行数，第二个char\*为查询的文件|
|PrintFile|int,int|DbDemo*|输出第n页的数据，第一个int为页码数，第二个int为每页展示的信息数目|
|GetPageCount|int|int|获取页码总数，int为每页展示所需的信息条数,bool代表操作是否针对缓存文件|
|GetCount|无|int|获取数据总条数|
|<font color=#ff0000>Order</font>|int|void|文件排序，int表示排序的列|
|Getbyid|bool|int|根据id查询，查询到返回true|
|Gettmp_sto|无|char *|将查询结果tmp_sto返回|
|Changebyid|int,char *|bool|修改id为int参数的数据，修改为char *的数值,成功返回true，失败返回false|
|Deletbyid|int|bool|删除id为int参数的数据，成功返回true，失败返回false|
|Getfile_num|无|int|获取该文件记录条数|
|<font color=#ff0000>Getbynum</font>|int|bool|查询第int参数个记录，如果参数超出最大文件记录条数则返回false|
|<font color=#ff0000>Getsiz</font>|int|int|返回第int列的数据长度,若大于列数则返回0|
|<font color=#ff0000>Getst</font>|int|int|返回第int列的起始相对位置，若大于列数则返回-1|
|GetcurrId|无|int|返回当前记录id|
|reOpen|无|无|重新打开一次文件，保证写入|
|Setfile_num（私有）|int|void|设置文件的记录条数|
|SetcurrId（私有）|int|void|重设当前自增id|