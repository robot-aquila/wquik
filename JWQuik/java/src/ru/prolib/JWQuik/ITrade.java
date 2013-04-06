package ru.prolib.JWQuik;

public interface ITrade extends INativeResource {
	public long getDate();
	public long getSettleDate();
	public long getTime();
	public boolean isMarginal();
	public double getAccruedInt();
	public double getYield();
	public double getTsCommission();
	public double getClearingCenterCommission();
	public double getExchangeCommission();
	public double getTradingSystemCommission();
	public double getPrice2();
	public double getRepoRate();
	public double getRepoValue();
	public double getRepo2Value();
	public double getAccruedInt2();
	public long getRepoTerm();
	public double getStartDiscount();
	public double getLowerDiscount();
	public double getUpperDiscount();
	public long getBlockSecurities();
	public String getCurrency();
	public String getSettleCurrency();
	public String getSettleCode();
	public String getAccount();
	public String getBrokerRef();
	public String getClientCode();
	public String getUserId();
	public String getFirmId();
	public String getPartnerFirmId();
	public String getExchangeCode();
	public String getStationId();

	public double getNumber();
	public double getOrderNumber();
	public String getClassCode();
	public String getSecCode();
	public double getPrice();
	public long getQty();
	public boolean isSell();
	public double getValue();
}
