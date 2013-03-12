package es.deusto.weblab.client.experiment.plugins.java;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;



public class WriteEthernetPHP {
    public static void main(String[] args) throws Exception {
        URL yahoo = new URL("http://localhost/read.php");
        URLConnection yc = yahoo.openConnection();
        BufferedReader in = new BufferedReader(
                                new InputStreamReader(
                                yc.getInputStream()));
        String inputLine;

        while ((inputLine = in.readLine()) != null) 
            System.out.println(inputLine);
        in.close();
    }
}