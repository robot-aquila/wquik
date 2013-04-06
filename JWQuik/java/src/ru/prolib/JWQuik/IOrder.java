package ru.prolib.JWQuik;

public interface IOrder extends INativeResource {
	public long getQty();
	public long getDate();
	public long getTime();
	public long getActivationTime();
	public long getWithdrawTime();
	public long getExpiry();
	public double getAccruedInt();
	public double getYield();
	public long getUID();
	public String getUserId();
	public String getAccount();
	public String getBrokerRef();
	public String getClientCode();
	public String getFirmId();

	public long getTransId();
	public double getNumber();
	public String getClassCode();
	public String getSecCode();
	public double getPrice();
	public long getBalance();
	public double getValue();
	public boolean isSell();
	public long getStatus();
}
