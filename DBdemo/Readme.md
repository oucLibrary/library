# 这里是数据库的demo

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
|filetp |File *|记录文件指针所在位置|
|tempFileName|string|记录缓存文件的文件名|

###方法
|方法名|参数|返回值|作用|
|:------|:------|:------|:------|
|DbDemoFileOperate|无|DbDemoFileOperate|默认构造函数|
|DbDemoFileOperate|string|DbDemoFileOperate|带参数的构造函数,string为要打开文件的文件名|
|FileWrite|DbDemo|void|添加一条数据,此时参数中的id值为无效值，将由程序自动生成|
|QueryById|int,bool|void|根据id查询，bool变量表示是否为对缓存文件的二次搜索|
|QueryByA|string,bool|void|根据a查询，bool变量表示是否为对缓存文件的二次搜索|
|PrintFile|int,int,bool|DbDemo*|输出第n页的数据，第一个int为页码数，第二个int为每页展示的信息数目，bool表示是否输出缓存文件的数据|
|GetPageCount|int,bool|int|获取页码总数，int为每页展示所需的信息条数,bool代表操作是否针对缓存文件|
|GetCount|bool|int|获取数据总条数，bool表示是否为对缓存文件的操作|
|OrderById|bool|void|对缓存文件进行文件排序，bool表示升降序|
|OrderByA|bool|void|对缓存文件进行文件排序，bool表示升降序|