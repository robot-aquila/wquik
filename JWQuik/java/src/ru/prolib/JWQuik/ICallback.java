package ru.prolib.JWQuik;

public interface ICallback {
	public void onConnectionStatus(long eventId, long errCode, String message);
	public void onTransactionReply
		(long result, long errCode, ITransactionResult tr);
	public void onOrderStatus(long mode, IOrder order);
	public void onTradeStatus(long mode, ITrade trade);
}
