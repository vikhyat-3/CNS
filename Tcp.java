package org.tcp;
import java.net.*;
import java.io.*;
public class tcpServer {
public static void main(String[] args)
{
  try
  {
    ServerSocket se = new ServerSocket(1537);
    System.out.println("Server waiting");
    Socket server = se.accept();
    System.out.println("Connection established");
    BufferedReader k = new BufferedReader (new InputStreamReader(server.getInputStream()));
    String filename = k.readLine();
    FileReader f = null;
    BufferedReader ff = null;
    DataOutputStream sendToClient = new DataOutputStream(server.getOutputStream());
    File file = new File(filename);
    if(file.exists())
    {
      sendToClient.writeBytes("Yes\n");
      f = new FileReader(filename);
      ff = new BufferedReader(f);
      String string;
      while((string = ff.readLine())!=null)
        sendToClient.writeBytes(string+"\n");
    }
    else
    {
      sendToClient.writeBytes("No\n");
    }
    server.close();
    k.close();
    sendToClient.close();
    f.close();
    ff.close();
    se.close();
    }
    catch(Exception ex) {}
  }
}
Client
package org.tcp;
import java.net.*;
import java.io.*;
public class tcpClient {
public static void main(String[] args)
{
  try
  {
    Socket client = new Socket("localhost", 1537);
    BufferedReader k = new BufferedReader(new InputStreamReader(System.in));
    System.out.println("Enter file location:");
    String filename = k.readLine();
    DataOutputStream sendToServer = new DataOutputStream(client.getOutputStream());
    sendToServer.writeBytes(filename+"\n");
    BufferedReader i = new BufferedReader(new InputStreamReader(client.getInputStream()));
    String string = i.readLine();
    if(string.equals("Yes"))
    {
      while((string=i.readLine())!=null)
        System.out.println(string);
    }
    else
      System.out.println("File not found");
    k.close();
    client.close();
    sendToServer.close();
    i.close();
  }
  catch(Exception ex) {}
  }
}
