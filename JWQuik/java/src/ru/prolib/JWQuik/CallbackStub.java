package ru.prolib.JWQuik;

public class CallbackStub implements ICallback,INativeResource {

	static {
		System.loadLibrary("JWQuik");
	}

	private long descriptor;
	
	public CallbackStub(long descriptor) {
		this.descriptor = descriptor;
		init();
	}
	
	private native void init();
	private native void release();

	@Override
	public native void onConnectionStatus
		(long eventId, long errCode, String message);
	@Override
	public native void onOrderStatus(long mode, IOrder order);
	@Override
	public native void onTradeStatus(long mode, ITrade trade);
	@Override
	public native void onTransactionReply
		(long result, long errCode, ITransactionResult tr);

	@Override
	public void free() {
		release();
	}
	
	protected void finalize() throws Throwable {
		release();
		super.finalize();
	}

}
