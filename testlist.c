#include "GList.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
	GList header;
	
	CreateGList(&header,"(11,12,(13))");
	Traverse_GL(header);

	return 0;
}
