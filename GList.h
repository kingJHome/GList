typedef enum{ATOM,LIST}ElemTag;			//ATOM==0:原子;LIST==1:字表

typedef struct GLNode{
	ElemTag tag;					//原子或表结点
	union{							//原子结构和表结点的联合部分
		int atom;
		struct GLNode *hp;
	}ptr;
	struct GLNode *tp;
}*GList,GLNode;

typedef union{
	int atom;
	GList hp;
}GListUnion;

typedef void (*_Visit)(int);

//创建空的广义表
void InitGList(GList *l);

//有s表示的表数据创建表
void CreateGList(GList *l,char *s);

//销毁广义表
void DestroyGList(GList l);

//复制广义表
void CopyGList(GList *t,GList l);

//求广义表的长度
int GListLength(GList l);

//求广义表的深度
int GListDepth(GList l);

//判断广义表是否为空
int GListEmpty(GList l);

//取广义表的头
GListUnion getHead(GList l);

//取广义表的尾
GList getTail(GList l);

//向广义表的插入元素作为表头
void InsertFirst_GL(GList l,int e);

//删除广义表的第一个元素
void DeleteFirst_GL(GList l,int *e);

//遍历广义表
void Traverse_GL(GList l);
