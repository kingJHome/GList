#include "GList.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void serverGListChar(GList *l,GList parent,char *s){
	size_t slen = strlen(s),
		   pos = 0;
	
	if(s[pos]=='('){
		GList temp = (GList)malloc(sizeof(GLNode));
		if(temp){
			temp->tag = LIST;
			temp->tp = parent;
			*l = temp;
			serverGListChar(&((*l)->ptr.hp),*l,s+1);
		}
	}else if(isdigit(s[pos])){
		for( ; isdigit(s[pos]); ++pos);
		char *atom = strndup(s, pos);
		*l = (GList)malloc(sizeof(GLNode));
		if(atom && *l){
			(*l)->tag = ATOM;
			(*l)->ptr.atom = atoi(atom);
			free(atom);
			if(s[pos] == ','){
				pos += 1;
			}
			serverGListChar(&((*l)->tp),parent,s+pos);
		}
	}else if(s[pos]==')'){
		if(slen > 1){//不是最后一个反括号
			if(s[pos+1]==','){
				pos += 2;
				serverGListChar(&(parent->tp),parent->tp,s+pos);
			}else{
				pos += 1;
				*l = NULL;
				serverGListChar(&(parent->tp),parent->tp,s+pos);
			}
		}else if(slen == 1){//最后一个反括号
			*l = NULL;
		}
	}
}

void myNodeVisit(GList node){
	if(node->tag==ATOM){
		printf("%d", node->ptr.atom);
		if(node->tp){
			printf(",");
		}
	}else if(node->tag==LIST){
		GList childs = node->ptr.hp;

		printf("(");
		for( ; childs; childs = childs->tp){
			myNodeVisit(childs);
		}
		printf(")");
		if(node->tp){
			printf(",");
		}
	}
}

void InitGList(GList *l){
	if( *l == NULL){
		*l = (GList)malloc(sizeof(GLNode));
	}

	if(*l != NULL){
		if((*l)->ptr.hp){
			DestroyGList((*l)->ptr.hp);
		}
		(*l)->tag = LIST;
		(*l)->ptr.hp = NULL;
		(*l)->tp = NULL;
	}
}

void CreateGList(GList *l,char *s){
	size_t slen = strlen(s);

	if(slen>0 && s[0]=='(' && s[slen-1]==')'){
		serverGListChar(l,NULL,s);
	}else{
		*l = NULL;
	}
}

void DestroyGList(GList l){
	if( l ){
		if(l->tp){
			DestroyGList(l->tp);
		}
		if(l->tag==LIST){
			DestroyGList(l->ptr.hp);	
		}
		free(l);
	}
}

void CopyGList(GList *t,GList l){
	if(!l){
		*t = NULL;
	}else{
		*t = (GList)malloc(sizeof(GLNode));
		if( *t ){
			(*t)->tag = l->tag;
			if(l->tag==ATOM){
				(*t)->ptr.atom = l->ptr.atom;
			}else if(l->tag==LIST){
				CopyGList(&((*t)->ptr.hp), l->ptr.hp);
			}
			CopyGList(&((*t)->tp),l->tp);
		}
	}
}

int GListLength(GList l){
	int len = 0;
	
	if(l){
		l = l->ptr.hp;
		while( l ){
			len++;
			l = l->tp;
		}
	}

	return len;
}

int GListDepth(GList l){
	if(!l){
		return 1;
	}else{
		if(l->tag == ATOM){
			return 0;
		}else{
			int max = 0,dep = 0;
			GList pp;

			for(pp = l; pp; pp = pp->tp){
				dep = GListDepth(pp->ptr.hp);
				if(dep > max){
					max = dep;
				}
			}

			return (max + 1);
		}
	}
}

int GListEmpty(GList l){
	int isempty = 0;
	
	if(!l || !l->ptr.hp){
		isempty = 1;
	}

	return isempty;
}

GListUnion getHead(GList l){
	GListUnion result;
	GList temp = l->ptr.hp;

	if(!l || !temp){
		result.hp = NULL;
	}else{
		if(temp->tag==ATOM){
			result.atom = temp->ptr.atom;
		}else if(temp->tag==LIST){
			result.hp = temp->ptr.hp;
		}
	}	

	return result;
}

GList getTail(GList l){
	GList result;

	if(!l || !l->ptr.hp){
		result = NULL;
	}else{
		result = l->ptr.hp->tp;
	}

	return result;
}

void InsertFirst_GL(GList l,int e){
}

void DeleteFirst_GL(GList l,int *e){
}

void Traverse_GL(GList l){
	printf("(");
	if(l && l->ptr.hp){
		GList temp = l->ptr.hp;
		for( ; temp; temp = temp->tp){
			myNodeVisit(temp);
		}
	}
	printf(")\n");	
}
