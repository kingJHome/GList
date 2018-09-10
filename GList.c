#include "GList.h"

void InitGList(GList l);

void CreateGList(GList l,char *s);

void DestroyGList(GList);

void CopyGList(GList t,GList l);

int GListLength(GList l);

int GListDepth(GList l);

int GListEmpty(GList l);

GListUnion getHead(GList l);

GList getTail(GList l);

void InsertFirst_GL(GList l,int e);

void DeleteFirst_GL(GList l,int *e);

void Traverse_GL(GList l,_Visit vt);
