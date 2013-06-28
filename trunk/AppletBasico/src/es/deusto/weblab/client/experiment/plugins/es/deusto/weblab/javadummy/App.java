package es.deusto.weblab.client.experiment.plugins.es.deusto.weblab.javadummy;
import java.net.SocketException;
import net.sourceforge.peers.sip.core.useragent.SipListener;
import net.sourceforge.peers.sip.core.useragent.UserAgent;
import net.sourceforge.peers.sip.syntaxencoding.SipUriSyntaxException;
import net.sourceforge.peers.sip.transport.SipRequest;
import net.sourceforge.peers.sip.transport.SipResponse;

public class App implements SipListener, Runnable
{
    public static void main( String[] args )
    {
    	(new Thread(new App())).start();

    }

    public App() {
        try {
            UserAgent userAgent = new UserAgent(this, null, null);
            // start a new call
            userAgent.getUac().invite("sip:1002@192.168.31.167", null);
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (SipUriSyntaxException e) {
            e.printStackTrace();
        }
    }

    @Override public void registering(SipRequest sipRequest) { }
    @Override public void registerSuccessful(SipResponse sipResponse) { }
    @Override public void registerFailed(SipResponse sipResponse) { }
    @Override public void incomingCall(SipRequest sipRequest, SipResponse provResponse) { }
    @Override public void remoteHangup(SipRequest sipRequest) { }
    @Override public void ringing(SipResponse sipResponse) { }
    @Override public void calleePickup(SipResponse sipResponse) { }
    @Override public void error(SipResponse sipResponse) { }

	public void run() {
		// TODO Auto-generated method stub
        System.out.println("Hello from a thread!");

	}
}