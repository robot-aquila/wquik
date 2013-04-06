package ru.prolib.JWQuik;

public interface ITransactionResult {
	public long getReplyCode();
	public long getTransId();
	public double getOrderNumber();
	public String getResultMessage();
}
