import ru.prolib.aquila.jddesvr.*;
import java.text.*;
import java.util.*;

public class runme
{
	static ServiceHandler handler1;
	static ServiceHandler handler2;
	static Server server;
	
	static {
	  /*
		Runtime.getRuntime().addShutdownHook(new Thread() {
			public void run() {
				try {
					System.out.println("Exit thread started: " + Thread.currentThread().getId());
				if ( service.isStarted() ) {
					service.stop();
				}
	    		service.delete();
	    		handler.delete();
	    		System.gc();
	    		System.runFinalization();
	    		jddesvr.winPostQuitMessage();
	    		System.out.println("finalization finished");
	    		} catch ( Exception e ) {
	    			System.out.println("Exception " + e.getMessage());
	    		}
	    	}
	    });
	*/
	}
  
	public static void main(String[] args) throws Exception {
		Object monitor = new Object();
		handler1 = new MyCallback("TEST", monitor);
		handler2 = new MyCallback("FOO", monitor);
		server = new Server();
		server.start();
		synchronized ( monitor ) {
			server.registerService(handler1);
			server.registerService(handler2);
			monitor.wait();
		}
		server.unregisterService(handler2);
		server.unregisterService(handler1);
		System.out.println("main: finished");
	}
}

class MyCallback extends ServiceHandler {
	private Format formatter;
	private Object monitor;
	
	public MyCallback(String serviceName, Object monitor) {
		super(serviceName);
		formatter = new SimpleDateFormat("hh:mm:ss.SSSS");
		this.monitor = monitor;
	}

	public boolean onConnect(String topic) {
		System.out.println("tid=" + Thread.currentThread().getId()
				+ " onConnect topic=" + topic);
		return true;
	}
	
	public void onConnectConfirm(String topic) {
		System.out.println("tid=" + Thread.currentThread().getId()
				+ " onConnectConfirm topic=" + topic);
	}
	
	public void onData(Table table) {
		System.out.println("tid=" + Thread.currentThread().getId()
				+ " onData topic=" + table.getTopic()
				+ " item=" + table.getItem());
		String time = formatter.format(new Date());
		//System.out.println(time);
		
		for ( int row = 0; row < table.getRows(); row ++ ) {
			for ( int col = 0; col < table.getCols(); col ++ ) {
				ICell cell = table.getCell(row, col);
				//System.out.println(cell.asString());
				System.out.print("r" + row + "c" + col + "t=");
				if ( cell.isBlank() ) {
					System.out.print("blk");
				} else if ( cell.isBoolean() ) {
					System.out.print("boo,val=" + (cell.asBoolean() ? "Y" : "N"));
				} else if ( cell.isError() ) {
					System.out.print("err");
				} else if ( cell.isFloat() ) {
					System.out.print("flt,val=" + cell.asFloat());
				} else if ( cell.isInteger() ) {
					System.out.print("int,val=" + cell.asInteger());
				} else if ( cell.isSkip() ) {
					System.out.print("skp");
				} else if ( cell.isString() ) {
					System.out.print("str,val=" + cell.asString());
				} else {
					System.out.print("UNK");
				}
				
				cell.asBoolean();
				cell.asFloat();
				cell.asInteger();
				cell.asString();
				
				//cell.delete();
				
				System.out.print("; ");
			}
			System.out.print("\n");
		}
		//table.delete();
		//System.out.print("-\n");
	}

	public void onDisconnect() {
		synchronized ( monitor ) {
			monitor.notifyAll();
		}
		System.out.println("tid=" + Thread.currentThread().getId()
				+ " onDisconnect");
	}
	
	public void onRegister() {
		System.out.println("tid=" + Thread.currentThread().getId()
				+ " onRegister");
	}
	
	public void onUnregister() {
		System.out.println("tid=" + Thread.currentThread().getId()
				+ " onUnregister");
	}
}
