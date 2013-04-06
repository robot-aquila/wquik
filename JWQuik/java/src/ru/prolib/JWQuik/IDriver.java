package ru.prolib.JWQuik;

public interface IDriver extends INativeResource {
	public void setAsyncMode() throws DriverException;
	public void setSyncMode() throws DriverException;
	public boolean isSyncMode();
	public boolean isAsyncMode();
	public void connect(String path) throws DriverException;
	public void disconnect() throws DriverException;
	public boolean isQuikConnected() throws DriverException;
	public boolean isDllConnected() throws DriverException;
	public ITransactionResult sendSyncTransaction(String str) throws DriverException;
	public void sendAsyncTransaction(String str) throws DriverException;
}
