package ru.prolib.JWQuik;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Main implements ICallback {
	public static Driver d;

	public static void main(String[] args) {
		String str = "ACCOUNT=L01-00000F00; CLIENT_CODE=51815;" +
			" TYPE=L; TRANS_ID=1; CLASSCODE=EQNE; SECCODE=GAZP; " +
			"ACTION=NEW_ORDER; OPERATION=B; QUANTITY=1; PRICE=150.00; ";
		try {		
			d = new Driver(new Main());
			d.connect("C:\\BCS_Work\\QUIK_Junior");
			d.setAsyncMode();
			d.sendAsyncTransaction(str);
		} catch ( DriverException e ) {
			e.printStackTrace();
		}
		
		Runtime.getRuntime().addShutdownHook(new Thread(){
			public void run(){
				System.out.println("terminating...");
				d.free();
			}
		});
		
		while ( true ) {
			try {
				Thread.sleep(1000);
			} catch ( InterruptedException e ) {
				return;
			}
		}
	}
	
	static public void msg(String text) {
		SimpleDateFormat df = new SimpleDateFormat("HH:mm:ss.SSSS");
		String time = df.format(new Date(System.currentTimeMillis()));
		System.out.println(time + "[" + Thread.currentThread().getId() + "] " + text);
	}
	
	public void onConnectionStatus(long eventId, long errCode, String message) {
		String txt = "connection status: event=" + eventId + " error=" +
			errCode + " msg=" + message;
		msg(txt);
	}
	
	public void onTransactionReply
		(long result, long errCode, ITransactionResult tr)
	{
		String txt = "transaction reply: result=" + result + " error=" +
			errCode + " reply code=" + tr.getReplyCode() + " transID=" +
			tr.getTransId() + " order #=" + tr.getOrderNumber() +
			" msg=" + tr.getResultMessage();
		msg(txt);
	}
	
	public void onOrderStatus(long mode, IOrder order) {
		String txt = "order status: mode=" + mode +
			" account=" + order.getAccount() +
			" accrued int=" + order.getAccruedInt() +
			" act. time=" + order.getActivationTime() +
			" balance=" + order.getBalance() +
			" brok.ref=" + order.getBrokerRef() +
			" class=" + order.getClassCode() +
			" client=" + order.getClientCode() +
			" date=" + order.getDate() +
			" expiry=" + order.getExpiry() +
			" firm id=" + order.getFirmId() +
			" number=" + order.getNumber() +
			" price=" + order.getPrice() +
			" qty=" + order.getQty() +
			" sec=" + order.getSecCode() +
			" status=" + order.getStatus() +
			" time=" + order.getTime() +
			" transID=" + order.getTransId() +
			" UID=" + order.getUID() +
			" user id=" + order.getUserId() +
			" value=" + order.getValue() +
			" with.time=" + order.getWithdrawTime() +
			" yield=" + order.getYield() +
			" is sell=" + (order.isSell() ? "yes" : "no");
		msg(txt);
		order.free();
	}
	
	public void onTradeStatus(long mode, ITrade trade) {
		System.out.println("[" + Thread.currentThread().getId() + "] onTradeStatus");
		
		trade.free();
	}

}
