%module(directors="1") JQTrans
%include "std_string.i"

%{
#include "aquila/qtrans/QTransStruct.h"
#include "aquila/jqtrans/JQTransHandler.h"
#include "aquila/jqtrans/JQTransServer.h"
%}

%typemap(out) std::string
%{  // BEG typemap(out) std::string marker
  size_t $1_len = $1.length();
  wchar_t *$1_dst = new wchar_t[$1_len];
  MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, $1.c_str(), $1_len, $1_dst, $1_len);
  $result = jenv->NewString((jchar*)$1_dst, $1_len);
  delete [] $1_dst;
  // END typemap(out) std::string marker %}
  
%typemap(directorin,descriptor="Ljava/lang/String;") std::string 
%{  // BEG typemap(directorin,descriptor="Ljava/lang/String;") std::string
  size_t $1_len = $1.length();
  wchar_t *$1_dst = new wchar_t[$1_len];
  MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, $1.c_str(), $1_len, $1_dst, $1_len);
  $input = jenv->NewString((jchar*)$1_dst, $1_len);
  delete [] $1_dst;
  // END typemap(directorin,descriptor="Ljava/lang/String;") std::string %}
  
  
%pragma(java) jniclasscode=%{
  static {
	String arch = System.getProperty("os.arch");
	if ( ! "x86".equals(arch) ) {
		System.err.println("JQTrans supports only x86 architecture because no 64-bit version of TRANS2QUIK.dll.");
		System.exit(1);
	}
    try {
        System.loadLibrary("JQTrans");
    } catch ( UnsatisfiedLinkError e ) {
      System.err.println("Native code library failed to load. \n" + e);
      System.exit(1);
    }
  }
%}

%feature("director") JQTransHandler; 
%typemap(throws, throws="Exception") std::exception, exception {
    jclass exClass = jenv->FindClass("java/lang/Exception");
    if (exClass)
        jenv->ThrowNew(exClass, $1.what());
    return $null;
}

%include "aquila/qtrans/QTransStruct.h"
%include "aquila/jqtrans/JQTransHandler.h"
%include "aquila/jqtrans/JQTransServer.h"

