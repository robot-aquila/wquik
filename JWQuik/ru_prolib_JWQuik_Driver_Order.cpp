#include "wquik/ITransactionDriver.h"
#include "jwquik/JWQuik.h"
#include "jwquik/ru_prolib_JWQuik_Driver_Order.h"

using namespace wquik;

namespace jwquik {

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_Driver_00024Order_init
	(JNIEnv * env, jobject obj)
{
	JWQUIK_ORDER_INIT(JWQUIK_VOID);
	JWQUIK_ORDER_TEST(JWQUIK_VOID);
	order->grab();
}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_Driver_00024Order_release
	(JNIEnv * env, jobject obj)
{
	JWQUIK_ORDER_INIT(JWQUIK_VOID);
	if ( order != 0 ) {
		order->drop();
		env->SetLongField(obj, fld, 0);
	}
}

JWQUIK_ORDER_GETTER(getQty, jlong, 0);
JWQUIK_ORDER_GETTER(getDate, jlong, 0);
JWQUIK_ORDER_GETTER(getTime, jlong, 0);
JWQUIK_ORDER_GETTER(getActivationTime, jlong, 0);
JWQUIK_ORDER_GETTER(getWithdrawTime, jlong, 0);
JWQUIK_ORDER_GETTER(getExpiry, jlong, 0);
JWQUIK_ORDER_GETTER(getAccruedInt, jdouble, 0);
JWQUIK_ORDER_GETTER(getYield, jdouble, 0);
JWQUIK_ORDER_GETTER(getUID, jlong, 0);
JWQUIK_ORDER_GETTER_STR(getUserId);
JWQUIK_ORDER_GETTER_STR(getAccount);
JWQUIK_ORDER_GETTER_STR(getBrokerRef);
JWQUIK_ORDER_GETTER_STR(getClientCode);
JWQUIK_ORDER_GETTER_STR(getFirmId);
JWQUIK_ORDER_GETTER(getTransId, jlong, 0);
JWQUIK_ORDER_GETTER(getNumber, jdouble, 0);
JWQUIK_ORDER_GETTER_STR(getClassCode);
JWQUIK_ORDER_GETTER_STR(getSecCode);
JWQUIK_ORDER_GETTER(getPrice, jdouble, 0);
JWQUIK_ORDER_GETTER(getBalance, jlong, 0);
JWQUIK_ORDER_GETTER(getValue, jdouble, 0);

JWQUIK_ORDER_FNPROTO(isSell, jboolean) {
	JWQUIK_ORDER_INITTEST(JNI_FALSE);
	return (JWQUIK_ORDER_CALL(isSell)() ? JNI_TRUE : JNI_FALSE);
}

JWQUIK_ORDER_GETTER(getStatus, jlong, 0);

} // end namespace jwquik
