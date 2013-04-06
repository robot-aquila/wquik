#pragma once
#include <jni.h>

class TestEnv {
	static JavaVM *jvm;
	static JNIEnv *env;
	static JavaVMInitArgs vm_args;
	static JavaVMOption options[1];
public:
	static bool init();
	static void free();
	static JNIEnv* getEnv();
};
