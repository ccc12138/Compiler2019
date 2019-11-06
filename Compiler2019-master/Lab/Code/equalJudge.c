#include "semantic.h"

bool typeEqual(Type ltype, Type rtype){
	// ERRORRRRRRRRRRRRRRRRRRR: For struct?
	// TO IMPLMENT
	if(ltype==NULL&&rtype==NULL){
		return true;
	}
	if(ltype==NULL||rtype==NULL){
		return false;
	}
	if(ltype->kind!=rtype->kind){
		return false;
	}
	if(ltype->kind==rtype->kind){
		switch(ltype->kind){
		case BASIC:
			return ltype->u.basic==rtype->u.basic?true:false;
		case ARRAY:
			return typeEqual(ltype->u.array.elem,rtype->u.array.elem);
		case STRUCTURE:
			return structEqual(ltype->u.structure,rtype->u.structure);
		case FUNCTION:
			printErr("typeEqual: Function");
			break;
		default://impossible to reach here
			printErr("typeEqual: switch");
		}
	}
	else{
		printErr("typeEqual: kind");
	}
	return true;
}

bool structEqual(FieldList lstruct, FieldList rstruct){
	if(lstruct==NULL&&rstruct==NULL)
		return true;
	if(lstruct==NULL||rstruct==NULL)
		return false;
	while(lstruct!=NULL&&rstruct!=NULL){
		if(!typeEqual(lstruct->type,rstruct->type))
			return false;
		if(strcmp(lstruct->name,rstruct->name)!=0)
			return false;
		lstruct=lstruct->tail;
		rstruct=rstruct->tail;
	}
	return true;
}

