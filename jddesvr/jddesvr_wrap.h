/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

#ifndef SWIG_jddesvr_WRAP_H_
#define SWIG_jddesvr_WRAP_H_

class SwigDirector_ServiceHandler : public aquila::jddesvr::ServiceHandler, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_ServiceHandler(JNIEnv *jenv, std::string serviceName);
    virtual ~SwigDirector_ServiceHandler();
    virtual std::string getName();
    virtual bool onConnect(std::string topic);
    virtual void onConnectConfirm(std::string topic);
    virtual bool onRawData(std::string topic, std::string item, char *dataBuffer, int size);
    virtual void onData(aquila::jddesvr::Table *table);
    virtual void onDisconnect(std::string topic);
    virtual void onRegister();
    virtual void onUnregister();
public:
    bool swig_overrides(int n) {
      return (n < 8 ? swig_override[n] : false);
    }
protected:
    bool swig_override[8];
};


#endif
