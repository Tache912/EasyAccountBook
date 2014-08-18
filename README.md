EasyAccountBook
=====

���ƣ�����ͨ
����Ҫ�󣺽���һ����ÿ�����롢֧����ΪΨһ����ļ�������Ͳ�ѯ����ϵͳ�������������״�ṹ�ı�ǩ�����ɶ���Ŀ���ݱ�ǩ����ͳ�ơ�
�������ݸ�ʽ��

��Ŀ
��
    ��֧���     ����
    ���            �޷�������
    ʱ��            �� �� ��
    ���            �޷�������
    ��ǩ            vector<��ǩ*>
}

class account
{
    unsigned int    idkey;//���
    date                  happenDate;//��Ŀ��������
    unsigned int    integerPart;//�����������
    unsigned int    decimalPart;//���С������
    vector<tag*>   accountTags;//��ǩ
    string                remark;//��ע
��; 

class accountBook
{
    vector<account*>    incomeAccounts;
    vector<account*>    ExpenditureAccounts;
    string accountBookName;
};


��ǩ��ѯ���ܣ�
���ӣ�
ʳƷ-����-����-������
   |        |
   |         ---����-�Ź�
    ---�߲�-Ҷ��-����
   |        |
   |         ---��---�ƹ�
   |
    ---ˮ��-����




����ӡ�����������ǩ�󣬲�ѯ��ʳƷ��ʱ���С�����������ǩ��֧����������
����ѯ�����⡱ʱ����ӡ�����������ǩ��֧����������

0.������ǩ����
TagTable::TagTable();
����һ��ֻ��root���ı�ǩ�������б�ǩ����root���������캯��

1.��ѯ��ǩ��
bool TagTable::findTag(string Tag_in);
��ѯ��ǩ���еı�ǩ�����ҵ��򷵻�true,���򷵻�false;

2.��ӱ�ǩ��
bool TagTable::addTag(string parentTag_in, string Tag_in);
���ǩ�����һ����ǩ������root�����ӱ�ǩʱ��parentTagΪ���������ַ�����
���parentTag�ǲ����ڵģ��򷵻�false
�ɹ���ӽ�㷵��true

3.�޸ı�ǩ��
bool TagTable::editTag(string Tag_old_in, string Tag_new_in);
���Tag_old�����ڣ�����false

4.ɾ����ǩ��
bool TagTable::deleteTag(string Tag_in);
ɾ��һ����ǩ�Լ���ȫ�������ı�ǩ�������ǩ�������򷵻�false

5.��ѯĳ��ǩ�Ƿ���һ��ǩ��������ǩ��
int TagTable::TagBelongTo��string parentTag_in, string Tag_in);
����ֵ���ж��������parentTag_in�����ڷ���-1��Tag_in�����ڷ���-2����Tag_in������parentTag_in����0��Tag_in����parentTag_in����1

��ǩϵͳ���ù�ϣ���ұ�ʵ�֣���ǩ������ݽṹ���£�

TagNode
{
    string            &tagName;//����һ�����ã���ԭ����Tag���޸�ʱ�����Ҳ����ű䣬һ�����ò��ܸ������ö���
    int                 &tagHash;
    TageNode    *nextNode;
};

Tag
{
    bool            deleteMark;//��ɾ����Tag��MarkΪtrue
    string          tagName;
    int               tagHash;
    TagNode    *parentTags;
    TagNode    *subTags; 
};

TagTable
{
    int      size;
    int      occupation;
    Tag    tag[];//��ϣ��������һ���λ
};

����һ��Tagʱ��ֻ��Ҫ���ҹ�ϣ�����Ƿ���ڸ�Tag���Լ���Tagû�б����Ϊdeleted
���Tagʱ��Ҫ���Ҹ�Tag�Ƿ��Ѿ����ڣ�������ڣ���Tag��parentTag�Ƿ��parentTag_in��ͬ���粻ͬ�����Ƕ�����Tag
�����Tag�����ڣ�����parentTag_in��׷��һ��subTag�����ڹ�ϣ������Ӹ�Tag
ɾ��Tagʱ����Tag�Լ�������û������parent��subTagsȫ����ǳ�deleted
��ѯһ��Tag�Ƿ���һ��parentTag_in��subTag�����ȴӹ�ϣ�����ҵ����Tag��Ȼ������������parentTags��������������parentTag_in���򷵻�1

����ͳ�ƺ�����

int    totalAmount(vector<account*>  accounts_in);//����accounts_in���ܽ��
vector<account*>    subAccounts(vector<account*> accounts_in, date startDate_in, date endDate_in);//����accounts_in�д�startDate_in��endDate_in����accounts
vector<account*>    subAccounts(vector<account*> accounts_in, Tag tag_in)��//����accounts_in�а���tag_in�Լ����ӱ�ǩ����accounts
vector<account*>    mergeAccounts(vector<account*> accounts_1_in, vector<account*> accounts_2_in);//����һ������accounts_1_in��accounts_2_in����account����accounts
vector<account*>    intersectAccounts(vector<account*> accounts_1_in, vector<account*> accounts_2_in);//����һ��ֻ����accounts_1_in��account_2_in���е�account����accounts
vector<account*>    differAccounts(vector<account*> accounts_1_in, vector<account*> accounts_2_in);//����һ��������accounts_1_in��account_2_in���в��ֵ������������ֵ�account����accounts
vector<account*>    subtractAccounts(vector<account*> accounts_1_in, vector<account*> accounts_2_in);//����һ������accounts_1_in��������accounts_1_in��account_2_in���в��ֵ���accounts

�����������ͣ�

������༭��ǩ�������

1.������ǩ ����ǩ �ӱ�ǩ
���и���ǩ����Ϊ�գ���ʾ�Ӹ���������ĵ�һ����ǩ�������롰�� ���� �ӱ�ǩ��
1.1.����|���� ��ǩ
ֱ�ӴӸ��ڵ㴴����ǩ��Ч��ͬ���� ���� �ӱ�ǩ��

2.��ѯ ��ǩ
2.1.��ѯ��ϵ ����ǩ �ӱ�ǩ | ��ѯ��ϵ �ӱ�ǩ ����ǩ

3.�޸ı�ǩ���� �ɱ�ǩ���� �±�ǩ����

4.��ʾ�����ӱ�ǩ ����ǩ

5.ɾ�� ��ǩ
���ɾ��һ�����ڵı�ǩ�Լ���ȫ��û����������ǩ���ӱ�ǩ

6.���Ʊ�ǩ�� [��ǩ]
[��ǩ]Ϊ��ѡ���ݣ���û����д�����������ǩ����Ч�����£�

ʳƷ
    ����
        ����
            ������
        ����
            �Ź�
            ����
            �廨��
            ����
    �߲�
        Ҷ��
            ����
        ��
            �ƹ�
    ˮ��
        ����

7.��ǩ���� [����]
��������[����]����ʱ������ʾ����֧�ֵ��������[����]���ݺ���ʾ�������ʹ�÷�ʽ��ʵ������

������༭��Ŀ������

1.�����˱� �˱�����
1.1.�����ϲ��˱� ���˱����� �˱�����1 �˱�����2

2.��ʾ�����˱�

3.���˱� �˱�����
���ô浵�ļ��е��������������ģ�����һ��Ϳ���������ȫ��ͬ���˱�
3.1�ر��˱���������һ���˱�ʱ�Զ��رյ�ǰ�˱�
3.2�����˱�
������¼ȫ���빹�����޸ġ�ɾ���йصĲ��������һ���ļ�

4.��ʾ�˱�����

5.�޸��˱����� ���˱����� ���˱�����

6.��֧ģʽ ����|֧��

7.���� ����ֵ|+|-:
��������ֵ(��������20140817),���롰+���ſɽ���ǰ����ֵ����һ��

8.���� ��� ��ǩ1 ��ǩ2 ��ǩ3 ... ��ǩN

9.��ע ��ע����

10.��ʾ�˱����� [����1 ����2]|[���1 ���2] [����|�������]����Ĭ�ϰ���������-�������У���ѡ�񰴽����|����-��������
Ч�����£�
�˱����ƣ������˱�
�������ڣ�2014��8��17��
����޸����ڣ�2014��8��17��
֧�����֣�
1.2013��7��1�� 15Ԫ ������ ���� �ޱ�ע
2.2013��7��2�� 20Ԫ ��� ���� �ޱ�ע
...
201.2013��12��31�� 100Ԫ �ֻ����� �ޱ�ע 

11.ɾ����Ŀ ���
�ڵ�ǰ�˱��͵�ǰ��֧ģʽ��ɾ���ض���ŵ���Ŀ

12.��ʾ�˱���ǰ״̬
�����˱����ơ��������ڡ�����޸����ڡ���Ŀ������֧ģʽ����ǰ��Ŀ���ڵȶ��״̬

13.��������
��ȡ��ʱ�浵����һ������Ϊֹ..������������¼

14.�����˱�
������ֱ�۵��ı���ʽ����ǩ������ѡ�˱�������

���ͳ�����ݵ�����

1.���� [����1 ����2] [��ǩ]
2.֧�� [����1 ����2] [��ǩ]
3.��֧ [����1 ����2] 
���������������ͳ�Ƶ�ǰ�˱���ȫ����Ӧ��Ŀ����ʾͳ�ƽ��

4.������� [����] [��ǩ]
5.���֧�� [����] [��ǩ]
�������������ͳ�Ʋ����ǰ��λ����Ӧ��Ŀ������ֻ��ʾ����һ��

6.�������� ��ֵ [��ǩ]
7.����֧�� ��ֵ [��ǩ]
С����ֵ�������֧��������ʾ
