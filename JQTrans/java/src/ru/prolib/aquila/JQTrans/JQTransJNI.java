/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package ru.prolib.aquila.JQTrans;

public class JQTransJNI {

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

  public final static native void QTransOrderStatus_mode_set(long jarg1, QTransOrderStatus jarg1_, int jarg2);
  public final static native int QTransOrderStatus_mode_get(long jarg1, QTransOrderStatus jarg1_);
  public final static native void QTransOrderStatus_transId_set(long jarg1, QTransOrderStatus jarg1_, long jarg2);
  public final static native long QTransOrderStatus_transId_get(long jarg1, QTransOrderStatus jarg1_);
  public final static native void QTransOrderStatus_orderId_set(long jarg1, QTransOrderStatus jarg1_, long jarg2);
  public final static native long QTransOrderStatus_orderId_get(long jarg1, QTransOrderStatus jarg1_);
  public final static native void QTransOrderStatus_classCode_set(long jarg1, QTransOrderStatus jarg1_, String jarg2);
  public final static native String QTransOrderStatus_classCode_get(long jarg1, QTransOrderStatus jarg1_);
  public final static native void QTransOrderStatus_secCode_set(long jarg1, QTransOrderStatus jarg1_, String jarg2);
  public final static native String QTransOrderStatus_secCode_get(long jarg1, QTransOrderStatus jarg1_);
  public final static native void QTransOrderStatus_price_set(long jarg1, QTransOrderStatus jarg1_, double jarg2);
  public final static native double QTransOrderStatus_price_get(long jarg1, QTransOrderStatus jarg1_);
  public final static native void QTransOrderStatus_balance_set(long jarg1, QTransOrderStatus jarg1_, int jarg2);
  public final static native int QTransOrderStatus_balance_get(long jarg1, QTransOrderStatus jarg1_);
  public final static native void QTransOrderStatus_value_set(long jarg1, QTransOrderStatus jarg1_, double jarg2);
  public final static native double QTransOrderStatus_value_get(long jarg1, QTransOrderStatus jarg1_);
  public final static native void QTransOrderStatus_isSell_set(long jarg1, QTransOrderStatus jarg1_, boolean jarg2);
  public final static native boolean QTransOrderStatus_isSell_get(long jarg1, QTransOrderStatus jarg1_);
  public final static native void QTransOrderStatus_status_set(long jarg1, QTransOrderStatus jarg1_, int jarg2);
  public final static native int QTransOrderStatus_status_get(long jarg1, QTransOrderStatus jarg1_);
  public final static native void QTransOrderStatus_orderDescriptor_set(long jarg1, QTransOrderStatus jarg1_, long jarg2);
  public final static native long QTransOrderStatus_orderDescriptor_get(long jarg1, QTransOrderStatus jarg1_);
  public final static native long new_QTransOrderStatus();
  public final static native void delete_QTransOrderStatus(long jarg1);
  public final static native void QTransTradeStatus_mode_set(long jarg1, QTransTradeStatus jarg1_, int jarg2);
  public final static native int QTransTradeStatus_mode_get(long jarg1, QTransTradeStatus jarg1_);
  public final static native void QTransTradeStatus_id_set(long jarg1, QTransTradeStatus jarg1_, long jarg2);
  public final static native long QTransTradeStatus_id_get(long jarg1, QTransTradeStatus jarg1_);
  public final static native void QTransTradeStatus_orderId_set(long jarg1, QTransTradeStatus jarg1_, long jarg2);
  public final static native long QTransTradeStatus_orderId_get(long jarg1, QTransTradeStatus jarg1_);
  public final static native void QTransTradeStatus_classCode_set(long jarg1, QTransTradeStatus jarg1_, String jarg2);
  public final static native String QTransTradeStatus_classCode_get(long jarg1, QTransTradeStatus jarg1_);
  public final static native void QTransTradeStatus_secCode_set(long jarg1, QTransTradeStatus jarg1_, String jarg2);
  public final static native String QTransTradeStatus_secCode_get(long jarg1, QTransTradeStatus jarg1_);
  public final static native void QTransTradeStatus_price_set(long jarg1, QTransTradeStatus jarg1_, double jarg2);
  public final static native double QTransTradeStatus_price_get(long jarg1, QTransTradeStatus jarg1_);
  public final static native void QTransTradeStatus_qty_set(long jarg1, QTransTradeStatus jarg1_, int jarg2);
  public final static native int QTransTradeStatus_qty_get(long jarg1, QTransTradeStatus jarg1_);
  public final static native void QTransTradeStatus_value_set(long jarg1, QTransTradeStatus jarg1_, double jarg2);
  public final static native double QTransTradeStatus_value_get(long jarg1, QTransTradeStatus jarg1_);
  public final static native void QTransTradeStatus_isSell_set(long jarg1, QTransTradeStatus jarg1_, boolean jarg2);
  public final static native boolean QTransTradeStatus_isSell_get(long jarg1, QTransTradeStatus jarg1_);
  public final static native void QTransTradeStatus_tradeDescriptor_set(long jarg1, QTransTradeStatus jarg1_, long jarg2);
  public final static native long QTransTradeStatus_tradeDescriptor_get(long jarg1, QTransTradeStatus jarg1_);
  public final static native long new_QTransTradeStatus();
  public final static native void delete_QTransTradeStatus(long jarg1);
  public final static native long new_JQTransHandler();
  public final static native void delete_JQTransHandler(long jarg1);
  public final static native void JQTransHandler_OnConnectionStatus(long jarg1, JQTransHandler jarg1_, int jarg2, int jarg3, String jarg4);
  public final static native void JQTransHandler_OnConnectionStatusSwigExplicitJQTransHandler(long jarg1, JQTransHandler jarg1_, int jarg2, int jarg3, String jarg4);
  public final static native void JQTransHandler_OnTransactionReply(long jarg1, JQTransHandler jarg1_, int jarg2, int jarg3, int jarg4, long jarg5, long jarg6, String jarg7);
  public final static native void JQTransHandler_OnTransactionReplySwigExplicitJQTransHandler(long jarg1, JQTransHandler jarg1_, int jarg2, int jarg3, int jarg4, long jarg5, long jarg6, String jarg7);
  public final static native void JQTransHandler_OnOrderStatus(long jarg1, JQTransHandler jarg1_, long jarg2, QTransOrderStatus jarg2_);
  public final static native void JQTransHandler_OnOrderStatusSwigExplicitJQTransHandler(long jarg1, JQTransHandler jarg1_, long jarg2, QTransOrderStatus jarg2_);
  public final static native void JQTransHandler_OnTradeStatus(long jarg1, JQTransHandler jarg1_, long jarg2, QTransTradeStatus jarg2_);
  public final static native void JQTransHandler_OnTradeStatusSwigExplicitJQTransHandler(long jarg1, JQTransHandler jarg1_, long jarg2, QTransTradeStatus jarg2_);
  public final static native void JQTransHandler_director_connect(JQTransHandler obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void JQTransHandler_change_ownership(JQTransHandler obj, long cptr, boolean take_or_release);
  public final static native String TRANS2QUIK_DLL_get();
  public final static native String CURRENT_DLL_get();
  public final static native String replace_mod(String jarg1);
  public final static native long new_JQTransServer(long jarg1, JQTransHandler jarg1_) throws Exception;
  public final static native void JQTransServer_connect(long jarg1, JQTransServer jarg1_, String jarg2) throws Exception;
  public final static native void JQTransServer_disconnect(long jarg1, JQTransServer jarg1_) throws Exception;
  public final static native void JQTransServer_send(long jarg1, JQTransServer jarg1_, String jarg2) throws Exception;
  public final static native boolean JQTransServer_isDllConnected(long jarg1, JQTransServer jarg1_);
  public final static native boolean JQTransServer_isQuikConnected(long jarg1, JQTransServer jarg1_);
  public final static native String JQTransServer_getOrderAccount(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getOrderClientCode(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getOrderFirmId(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native long JQTransServer_getOrderQty(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native long JQTransServer_getOrderDate(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native long JQTransServer_getOrderTime(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native long JQTransServer_getOrderActivationTime(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native long JQTransServer_getOrderWithdrawTime(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native long JQTransServer_getOrderExpiry(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getOrderAccruedInt(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getOrderYield(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native long JQTransServer_getOrderUid(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getOrderUserId(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getOrderBrokerRef(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native long JQTransServer_getTradeDate(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native long JQTransServer_getTradeSettleDate(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native long JQTransServer_getTradeTime(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native boolean JQTransServer_getTradeIsMarginal(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradeAccruedInt(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradeYield(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradeTsCommission(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradeClearingCenterCommission(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradeExchangeCommission(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradeTradingSystemCommission(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradePrice2(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradeRepoRate(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradeRepoValue(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradeRepo2Value(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradeAccruedInt2(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native int JQTransServer_getTradeRepoTerm(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradeStartDiscount(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradeLowerDiscount(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native double JQTransServer_getTradeUpperDiscount(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native boolean JQTransServer_getTradeBlockSecurities(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getTradeCurrency(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getTradeSettleCurrency(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getTradeSettleCode(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getTradeAccount(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getTradeBrokerRef(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getTradeClientCode(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getTradeUserId(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getTradeFirmId(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getTradePartnerFirmId(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getTradeExchangeCode(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native String JQTransServer_getTradeStationId(long jarg1, JQTransServer jarg1_, long jarg2);
  public final static native void delete_JQTransServer(long jarg1);

  public static void SwigDirector_JQTransHandler_OnConnectionStatus(JQTransHandler self, int connEvent, int errCode, String errMsg) {
    self.OnConnectionStatus(connEvent, errCode, errMsg);
  }
  public static void SwigDirector_JQTransHandler_OnTransactionReply(JQTransHandler self, int resultCode, int errCode, int replyCode, long transId, long orderId, String replyMsg) {
    self.OnTransactionReply(resultCode, errCode, replyCode, transId, orderId, replyMsg);
  }
  public static void SwigDirector_JQTransHandler_OnOrderStatus(JQTransHandler self, long status) {
    self.OnOrderStatus(new QTransOrderStatus(status, false));
  }
  public static void SwigDirector_JQTransHandler_OnTradeStatus(JQTransHandler self, long status) {
    self.OnTradeStatus(new QTransTradeStatus(status, false));
  }

  private final static native void swig_module_init();
  static {
    swig_module_init();
  }
}
