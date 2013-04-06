#include "wquik/ITransactionDriver.h"
#include "jwquik/JWQuik.h"
#include "jwquik/ru_prolib_JWQuik_Driver_Trade.h"

using namespace wquik;

namespace jwquik {

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_Driver_00024Trade_init
	(JNIEnv * env, jobject obj)
{
	JWQUIK_TRADE_INIT(JWQUIK_VOID);
	JWQUIK_TRADE_TEST(JWQUIK_VOID);
	trade->grab();
}

JNIEXPORT void JNICALL Java_ru_prolib_JWQuik_Driver_00024Trade_release
	(JNIEnv * env, jobject obj)
{
	JWQUIK_TRADE_INIT(JWQUIK_VOID);
	if ( trade != 0 ) {
		trade->drop();
		env->SetLongField(obj, fld, 0);
	}
}

JWQUIK_TRADE_GETTER(getDate, jlong, 0);
JWQUIK_TRADE_GETTER(getSettleDate, jlong, 0);
JWQUIK_TRADE_GETTER(getTime, jlong, 0);

//JWQUIK_TRADE_GETTER(isMarginal, jboolean, JNI_FALSE);
JWQUIK_TRADE_FNPROTO(isMarginal, jboolean) {
	JWQUIK_TRADE_INITTEST(JNI_FALSE);
	return (JWQUIK_TRADE_CALL(isMarginal)() ? JNI_TRUE : JNI_FALSE);
}

JWQUIK_TRADE_GETTER(getAccruedInt, jdouble, 0);
JWQUIK_TRADE_GETTER(getYield, jdouble, 0);
JWQUIK_TRADE_GETTER(getTsCommission, jdouble, 0);
JWQUIK_TRADE_GETTER(getClearingCenterCommission, jdouble, 0);
JWQUIK_TRADE_GETTER(getExchangeCommission, jdouble, 0);
JWQUIK_TRADE_GETTER(getTradingSystemCommission, jdouble, 0);
JWQUIK_TRADE_GETTER(getPrice2, jdouble, 0);

JWQUIK_TRADE_GETTER(getRepoRate, jdouble, 0);
JWQUIK_TRADE_GETTER(getRepoValue, jdouble, 0);
JWQUIK_TRADE_GETTER(getRepo2Value, jdouble, 0);
JWQUIK_TRADE_GETTER(getAccruedInt2, jdouble, 0);
JWQUIK_TRADE_GETTER(getRepoTerm, jlong, 0);
JWQUIK_TRADE_GETTER(getStartDiscount, jdouble, 0);
JWQUIK_TRADE_GETTER(getLowerDiscount, jdouble, 0);
JWQUIK_TRADE_GETTER(getUpperDiscount, jdouble, 0);
JWQUIK_TRADE_GETTER(getBlockSecurities, jlong, 0);
JWQUIK_TRADE_GETTER_STR(getCurrency);
JWQUIK_TRADE_GETTER_STR(getSettleCurrency);
JWQUIK_TRADE_GETTER_STR(getSettleCode);
JWQUIK_TRADE_GETTER_STR(getAccount);
JWQUIK_TRADE_GETTER_STR(getBrokerRef);
JWQUIK_TRADE_GETTER_STR(getClientCode);
JWQUIK_TRADE_GETTER_STR(getUserId);
JWQUIK_TRADE_GETTER_STR(getFirmId);
JWQUIK_TRADE_GETTER_STR(getPartnerFirmId);
JWQUIK_TRADE_GETTER_STR(getExchangeCode);
JWQUIK_TRADE_GETTER_STR(getStationId);
JWQUIK_TRADE_GETTER(getNumber, jdouble, 0);
JWQUIK_TRADE_GETTER(getOrderNumber, jdouble, 0);
JWQUIK_TRADE_GETTER_STR(getClassCode);
JWQUIK_TRADE_GETTER_STR(getSecCode);
JWQUIK_TRADE_GETTER(getPrice, jdouble, 0);
JWQUIK_TRADE_GETTER(getQty, jlong, 0);

JWQUIK_TRADE_FNPROTO(isSell, jboolean) {
	JWQUIK_TRADE_INITTEST(JNI_FALSE);
	return (JWQUIK_TRADE_CALL(isSell)() ? JNI_TRUE : JNI_FALSE);
}

JWQUIK_TRADE_GETTER(getValue, jdouble, 0);

} // end namespace jwquik
