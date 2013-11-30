
#include <os.h>
#include <core/file.h>
#include <runtime/alloc.h>
#include <runtime/libc.h>
#include <core/filesystem.h>
#include <module.h>

/* Inclusion de la liste des modules */
#include "modules.conf"
	
Module::Module(){

}

Module::~Module(){

}
		
void Module::initLink(){
	int i=0;
	ModLink* mod;
	while (module_builder[i] != 0){
		mod=new ModLink(module_builder[i]->module_name);
		i=i++;
	}
}

File* Module::createDevice(char* name,char* module,u32 flag){
	int i=0;
	File* fp;
	while (module_builder[i] != 0){
		if (!strcmp(module_builder[i]->module_name,module)){
			
			if (module_builder[i]->module_type==MODULE_DEVICE){
				fp=module_builder[i]->drive(name,flag,NULL);
				return fp;
			}
		}
		
		i=i++;
	}
	return NULL;
}

File* Module::mount(char* dev,char* dir,char* module,u32 flag){
	File* fdev=fsm.path(dev);
	if (fdev==NULL)
		return NULL;
	int i=0;
	File* fp;
	while (module_builder[i] != 0){
		if (!strcmp(module_builder[i]->module_name,module)){
			fp=module_builder[i]->drive(dir,flag,fdev);
			if (module_builder[i]->module_type==MODULE_FILESYSTEM && fp!=NULL){
				fsm.addFile("/mnt/",fp);
				fp->setType(TYPE_DIRECTORY);
				return fp;
			}
			else
				return NULL;
		}
		
		i=i++;
	}
	return NULL;
}

File* Module::install(char* dir,char* module,u32 flag,char* dev){
	File* fdev=fsm.path(dev);
	if (fdev==NULL)
		return NULL;
	int i=0;
	File* fp;
	while (module_builder[i] != 0){
		if (!strcmp(module_builder[i]->module_name,module)){
			if (module_builder[i]->module_type==MODULE_FILESYSTEM){
				return module_builder[i]->drive(dir,flag,fdev);
			}
		}
		
		i=i++;
	}
	return NULL;
}
