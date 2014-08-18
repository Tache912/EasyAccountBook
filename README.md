EasyAccountBook
=====
    
    名称：记账通
    基本要求：建立一个以每笔收入、支出作为唯一对象的记账输入和查询管理系统，可任意添加树状结构的标签，并可对账目根据标签进行统计。
    基本数据格式：
    
    账目
    ｛
        收支类别     整数
        编号            无符号数字
        时间            年 月 日
        金额            无符号数字
        标签            vector<标签*>
    }
    
    class account
    {
        unsigned int    idkey;//编号
        date                  happenDate;//账目产生日期
        unsigned int    integerPart;//金额整数部分
        unsigned int    decimalPart;//金额小数部分
        vector<tag*>   accountTags;//标签
        string                remark;//备注
    ｝; 
    
    class accountBook
    {
        vector<account*>    incomeAccounts;
        vector<account*>    ExpenditureAccounts;
        string accountBookName;
    };
    
    
    标签查询功能：
    例子：
    食品-肉类-鱼肉-龙利柳
       |        |
       |         ---猪肉-排骨
        ---蔬菜-叶菜-生菜
       |        |
       |         ---瓜---黄瓜
       |
        ---水果-西瓜
    
    
    
    
    当添加“龙利柳”标签后，查询“食品”时具有“龙利柳”标签的支出对象命中
    但查询“猪肉”时，添加“龙利柳”标签的支出对象不命中
    
    0.创建标签树：
    TagTable::TagTable();
    创建一棵只有root结点的标签树，所有标签均从root派生，构造函数
    
    1.查询标签：
    bool TagTable::findTag(string Tag_in);
    查询标签树中的标签，如找到则返回true,否则返回false;
    
    2.添加标签：
    bool TagTable::addTag(string parentTag_in, string Tag_in);
    向标签树添加一个标签，当向root结点添加标签时，parentTag为“”【空字符串】
    如果parentTag是不存在的，则返回false
    成功添加结点返回true
    
    3.修改标签：
    bool TagTable::editTag(string Tag_old_in, string Tag_new_in);
    如果Tag_old不存在，返回false
    
    4.删除标签：
    bool TagTable::deleteTag(string Tag_in);
    删除一个标签以及其全部派生的标签，如果标签不存在则返回false
    
    5.查询某标签是否另一标签的派生标签：
    int TagTable::TagBelongTo（string parentTag_in, string Tag_in);
    返回值具有多种情况：parentTag_in不存在返回-1，Tag_in不存在返回-2，或Tag_in不属于parentTag_in返回0，Tag_in属于parentTag_in返回1
    
    标签系统可用哈希查找表实现，标签类的数据结构如下：
    
    TagNode
    {
        string            &tagName;//这是一个引用，当原本的Tag被修改时，这个也会跟着变，一旦引用不能更改引用对象
        int                 &tagHash;
        TageNode    *nextNode;
    };
    
    Tag
    {
        bool            deleteMark;//被删除的Tag该Mark为true
        string          tagName;
        int               tagHash;
        TagNode    *parentTags;
        TagNode    *subTags; 
    };
    
    TagTable
    {
        int      size;
        int      occupation;
        Tag    tag[];//哈希表，至少留一半空位
    };
    
    查找一个Tag时，只需要查找哈希表中是否存在该Tag，以及该Tag没有被标记为deleted
    添加Tag时，要查找该Tag是否已经存在，如果存在，该Tag的parentTag是否和parentTag_in相同，如不同，则是多派生Tag
    如果该Tag不存在，则在parentTag_in上追加一个subTag，并在哈希表中添加该Tag
    删除Tag时，将Tag以及其所有没有其他parent的subTags全部标记成deleted
    查询一个Tag是否另一个parentTag_in的subTag，首先从哈希表中找到这个Tag，然后搜索其整个parentTags树，如果里面存在parentTag_in，则返回1
    
    数据统计函数：
    
    int    totalAmount(vector<account*>  accounts_in);//计算accounts_in的总金额
    vector<account*>    subAccounts(vector<account*> accounts_in, date startDate_in, date endDate_in);//生成accounts_in中从startDate_in到endDate_in的子accounts
    vector<account*>    subAccounts(vector<account*> accounts_in, Tag tag_in)；//生成accounts_in中包含tag_in以及其子标签的子accounts
    vector<account*>    mergeAccounts(vector<account*> accounts_1_in, vector<account*> accounts_2_in);//生成一个包括accounts_1_in和accounts_2_in所有account的新accounts
    vector<account*>    intersectAccounts(vector<account*> accounts_1_in, vector<account*> accounts_2_in);//生成一个只包括accounts_1_in和account_2_in共有的account的新accounts
    vector<account*>    differAccounts(vector<account*> accounts_1_in, vector<account*> accounts_2_in);//生成一个不包括accounts_1_in和account_2_in共有部分但包括其他部分的account的新accounts
    vector<account*>    subtractAccounts(vector<account*> accounts_1_in, vector<account*> accounts_2_in);//生成一个包括accounts_1_in但不包括accounts_1_in和account_2_in共有部分的新accounts
    
    交互命令类型：
    
    构建与编辑标签树的命令：
    
    1.派生标签 父标签 子标签
    其中父标签可以为空，表示从根结点派生的第一代标签，即输入“从 派生 子标签”
    1.1.建立|创建 标签
    直接从根节点创建标签，效果同“从 派生 子标签”
    
    2.查询 标签
    2.1.查询关系 父标签 子标签 | 查询关系 子标签 父标签
    
    3.修改标签名称 旧标签名称 新标签名称
    
    4.显示所有子标签 父标签
    
    5.删除 标签
    这会删除一个存在的标签以及其全部没有其他父标签的子标签
    
    6.绘制标签树 [标签]
    [标签]为可选内容，如没有填写则绘制整个标签树，效果如下：
    
    食品
        肉类
            鱼肉
                龙利柳
            猪肉
                排骨
                瘦肉
                五花肉
                猪手
        蔬菜
            叶菜
                生菜
            瓜
                黄瓜
        水果
            西瓜
    
    7.标签帮助 [命令]
    当不输入[命令]内容时，如显示所有支持的命令，输入[命令]内容后，显示该命令的使用方式和实际例子
    
    构建与编辑账目的命令
    
    1.建立账本 账本名称
    1.1.建立合并账本 新账本名称 账本名称1 账本名称2
    
    2.显示所有账本
    
    3.打开账本 账本名称
    利用存档文件中的命令操作，重新模拟进行一遍就可以生成完全相同的账本
    3.1关闭账本：当打开另一个账本时自动关闭当前账本
    3.2保存账本
    逐条记录全部与构建、修改、删除有关的操作，存成一个文件
    
    4.显示账本名称
    
    5.修改账本名称 旧账本名称 新账本名称
    
    6.收支模式 收入|支出
    
    7.日期 日期值|+|-:
    输入日期值(例如输入20140817),输入“+”号可将当前日期值增加一天
    
    8.记账 金额 标签1 标签2 标签3 ... 标签N
    
    9.备注 备注内容
    
    10.显示账本内容 [日期1 日期2]|[金额1 金额2] [金额降序|金额升序]：（默认按日期升序-金额降序排列，可选择按金额升|降序-日期升序）
    效果如下：
    账本名称：测试账本
    创建日期：2014年8月17日
    最后修改日期：2014年8月17日
    支出部分：
    1.2013年7月1日 15元 龙利柳 超市 无备注
    2.2013年7月2日 20元 面粉 超市 无备注
    ...
    201.2013年12月31日 100元 手机话费 无备注 
    
    11.删除条目 编号
    在当前账本和当前收支模式下删除特定编号的条目
    
    12.显示账本当前状态
    包括账本名称、创建日期、最后修改日期、条目数、收支模式、当前账目日期等多个状态
    
    13.撤销操作
    读取临时存档到上一条操作为止..本操作不被记录
    
    14.导出账本
    导出成直观的文本格式，标签树和所选账本的内容
    
    输出统计数据的命令
    
    1.收入 [日期1 日期2] [标签]
    2.支出 [日期1 日期2] [标签]
    3.收支 [日期1 日期2] 
    如果不带参数，则统计当前账本的全部相应条目并显示统计结果
    
    4.最大收入 [数量] [标签]
    5.最大支出 [数量] [标签]
    如果带参数，则统计并输出前几位的相应条目，否则只显示最大的一项
    
    6.大宗收入 阈值 [标签]
    7.大宗支出 阈值 [标签]
    小于阈值的收入或支出不会显示
