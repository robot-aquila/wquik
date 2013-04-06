package ru.prolib.JWQuik;

public class Driver implements IDriver {
	
	static {
		System.loadLibrary("JWQuik");
	}
	
	private ICallback callback;
	private long descriptor;
	
	public Driver(ICallback cb) throws DriverException {
		descriptor = 0;
		callback = cb;
		init();
	}
	
	public Driver(ICallback cb, long driver) throws DriverException {
		this.descriptor = 0;
		callback = cb;
		init(driver);
	}

	private native void init() throws DriverException;
	private native void init(long driver) throws DriverException;
	private native void release() throws DriverException;
	
	public synchronized native void setAsyncMode() throws DriverException;
	public synchronized native void setSyncMode() throws DriverException;
	public synchronized native boolean isSyncMode();
	public synchronized native boolean isAsyncMode();
	public synchronized native void connect(String path) throws DriverException;
	public synchronized native void disconnect() throws DriverException;
	public synchronized native boolean isQuikConnected() throws DriverException;
	public synchronized native boolean isDllConnected() throws DriverException;
	public synchronized native ITransactionResult sendSyncTransaction
		(String str) throws DriverException;
	public synchronized native void sendAsyncTransaction
		(String str) throws DriverException;

	@Override
	public void free() {
		try {
			release();
		} catch ( DriverException e ) {
			System.out.println("DriverException: " + e.getMessage());
			e.printStackTrace();
		}
	}
	
	protected void finalize() throws Throwable {
		release();
		super.finalize();
	}
	
	public static class Order implements IOrder {
		static {
			System.loadLibrary("JWQuik");
		}

		private long descriptor;
		
		public Order(long descriptor) {
			this.descriptor = descriptor;
			init();
		}
		
		private native void init();
		private native void release();

		public native long getQty();
		public native long getDate();
		public native long getTime();
		public native long getActivationTime();
		public native long getWithdrawTime();
		public native long getExpiry();
		public native double getAccruedInt();
		public native double getYield();
		public native long getUID();
		public native String getUserId();
		public native String getAccount();
		public native String getBrokerRef();
		public native String getClientCode();
		public native String getFirmId();

		public native long getTransId();
		public native double getNumber();
		public native String getClassCode();
		public native String getSecCode();
		public native double getPrice();
		public native long getBalance();
		public native double getValue();
		public native boolean isSell();
		public native long getStatus();
		
		@Override
		public void free() {
			release();
		}
		
		protected void finalize() throws Throwable {
			release();
			super.finalize();
		}

	}
	
	public static class Trade implements ITrade {
		static {
			System.loadLibrary("JWQuik");
		}

		private long descriptor;
		
		public Trade(long descriptor) {
			this.descriptor = descriptor;
			init();
		}
		
		private native void init();
		private native void release();

		public native long getDate();
		public native long getSettleDate();
		public native long getTime();
		public native boolean isMarginal();
		public native double getAccruedInt();
		public native double getYield();
		public native double getTsCommission();
		public native double getClearingCenterCommission();
		public native double getExchangeCommission();
		public native double getTradingSystemCommission();
		public native double getPrice2();
		public native double getRepoRate();
		public native double getRepoValue();
		public native double getRepo2Value();
		public native double getAccruedInt2();
		public native long getRepoTerm();
		public native double getStartDiscount();
		public native double getLowerDiscount();
		public native double getUpperDiscount();
		public native long getBlockSecurities();
		public native String getCurrency();
		public native String getSettleCurrency();
		public native String getSettleCode();
		public native String getAccount();
		public native String getBrokerRef();
		public native String getClientCode();
		public native String getUserId();
		public native String getFirmId();
		public native String getPartnerFirmId();
		public native String getExchangeCode();
		public native String getStationId();

		public native double getNumber();
		public native double getOrderNumber();
		public native String getClassCode();
		public native String getSecCode();
		public native double getPrice();
		public native long getQty();
		public native boolean isSell();
		public native double getValue();
		
		@Override
		public void free() {
			release();
		}
		
		protected void finalize() throws Throwable {
			release();
			super.finalize();
		}

	}
	
	public static class TransactionResult implements ITransactionResult {
		private final long replyCode;
		private final long transId;
		private final double orderNumber;
		private final String message;
		
		public TransactionResult(long code, long id, double num, String msg) {
			replyCode = code;
			transId = id;
			orderNumber = num;
			message = msg;
		}
		
		public long getReplyCode() {
			return replyCode;
		}
		
		public long getTransId() {
			return transId;
		}
		
		public double getOrderNumber() {
			return orderNumber;
		}
		
		public String getResultMessage() {
			return message;
		}
	}

}
