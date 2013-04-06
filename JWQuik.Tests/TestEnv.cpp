#include "TestEnv.h"

JavaVM* TestEnv::jvm = 0;
JNIEnv* TestEnv::env = 0;
JavaVMInitArgs TestEnv::vm_args;
JavaVMOption TestEnv::options[1];

bool TestEnv::init() {
	options[0].optionString = "-Djava.class.path=JWQuik.jar";
	vm_args.version = 0x00010002;
	vm_args.options = options;
	vm_args.nOptions = 1;
	vm_args.ignoreUnrecognized = JNI_TRUE;
	jint res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
	if ( res < 0 ) {
		printf("Can't create Java VM\n");
		return false;
	}
	return true;
}

void TestEnv::free() {
	jvm->DestroyJavaVM();
}

JNIEnv* TestEnv::getEnv() {
	return env;
}
