#include "GList.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
	GList header;
	
	CreateGList(&header,"(11,12,(13,(14,15),(16)))");
	Traverse_GL(header);

	return 0;
}
