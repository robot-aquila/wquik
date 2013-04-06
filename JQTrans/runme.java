import ru.prolib.aquila.JQTrans.*;

public class runme extends JQTransHandler {
	
	public static void main(String[] args) throws Exception {
		new runme().run();
	}
	
	public void run() throws Exception {
		System.out.println("Starting...");
		JQTransServer server = new JQTransServer(this);
		System.out.println("Created");
		try {
			server.connect("C:\\quik\\finam\\quik5");
		} catch ( Exception e ) {
			System.out.println("Exception on connect: " + e);
			return;
		}
		System.out.println("Connected");
		try {
			server.send("TRANS_ID=1; CLASSCODE=EQBR; ACTION=KILL_ALL_ORDERS; CLIENT_CODE=Q6;");
			System.out.println("Sent");
		} catch ( Exception e ) {
			System.out.println("Exception on transaction: " + e);
		}
		server.disconnect();
		System.out.println("Disconnected");
	}
	
	public runme() {
		super();
	}
	
	public void OnConnectionStatus(int connEvent, int errCode, String errMsg) {
		System.out.println("OnConnectionStatus: " + connEvent
				+ " errCode=" + errCode
				+ " errMsg=" + errMsg);
	}
	
	public void OnTransactionReply(int resultCode, int errCode, int replyCode,
			int transId, double orderId, String replyMsg)
	{
		System.out.println("OnTransactionReply: trans=" + transId
				+ " msg=" + replyMsg);
	}

}