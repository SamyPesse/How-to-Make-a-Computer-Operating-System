#ifndef OS_H
#define OS_H

#include <config.h>
#include <kernel.h>


typedef File* (*device_driver)	(char* name,u32 flag,File* dev);

struct module_class{
	int					module_type;
	char*			module_name;
	char*			class_name;
	device_driver	drive;
};




/*
 *	Module Macro
 */
#define MODULE_DEVICE		0
#define MODULE_FILESYSTEM	1
#define module(name,type,classe,mknod)	module_class classe##_module={type,\
																name, \
																#classe, \
																(device_driver)mknod};	

#define import_module(classe) 	extern module_class  classe##_module

#define run_module_builder	module_class* module_builder[]=
#define build_module(classe) 	&classe##_module
#define end_module() 		NULL

#define std_buildin_module	void Module::init()
#define	run_module(n,m,f) createDevice(#m,#n,f);

/*
 *	Asm Macro
 */
#define asm 		__asm__
#define asmv 		__asm__ __volatile__



#endif
