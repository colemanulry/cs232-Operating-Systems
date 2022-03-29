/*
 * Server Side
 * Author: Coleman Ulry
 * Date: 4/24/21
 * Resources used: https://www.infoworld.com/article/2853780/socket-programming-for-scalable-systems.html
 * and https://docs.oracle.com/javase/tutorial/networking/sockets/readingWriting.html
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.io.PrintWriter;
import java.time.format.DateTimeFormatter;
import java.time.LocalDateTime;

public class CipherServer extends Thread {

  // instance variables
  private ServerSocket serverSocket;
  private int port;
  private boolean current = false;

  // constructor
  public CipherServer(int port) {
    this.port = port;
  }

  public void startServer() {
    try {
      // create port
      serverSocket = new ServerSocket(port);
      this.start();

    } catch (IOException exc) {
      exc.printStackTrace();
    }
  }

  public void stopServer() {
    current = false;
    this.interrupt();
  }

  @Override
  public void run() {
    current = true;
    while (current) {
      try {
        System.out.println("\nListening for connection...");

        // accept incoming connection
        Socket socket = serverSocket.accept();

        CipherText ct = new CipherText(socket);
        ct.start();

      } catch (IOException exc) {
        exc.printStackTrace();
      }
    }
  }

  public static void main(String[] args) {

    // convert argument to integer
    int port = Integer.parseInt(args[0]);

    System.out.println("\nServer successfully started on port " + port);

    CipherServer server = new CipherServer(port);

    server.startServer();

    System.out.println("\nServer has started...");

  }
}

class CipherText extends Thread {

  private Socket socket;

  CipherText(Socket socket) {
    this.socket = socket;

    // reference: https://www.javatpoint.com/java-get-current-date
    // display date and client's IP Address
    DateTimeFormatter dt = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
    LocalDateTime now = LocalDateTime.now();
    System.out.println("\n ** Connection started at: " + dt.format(now));

    String currentIPAddr = socket.getLocalAddress().getHostAddress();
    System.out.println(" ** From IP Address: " + currentIPAddr);

  }

  public static String process(String text, int rotation) {

    String cipheredText = "";
    char alpha;

    // reference:
    // https://javahungry.blogspot.com/2019/02/caesar-cipher-program-in-java.html
    // loop through each char
    for (int i = 0; i < text.length(); i++) {

      // return that char
      alpha = text.charAt(i);

      // lower case
      if (alpha >= 'a' & alpha <= 'z') {

        alpha = (char) ((alpha + rotation));

        // check out of bounds condition
        if (alpha > 'z') {

          alpha = (char) (alpha + 'a' - 'z' - 1);

        }

        // append new char to final text var
        cipheredText += alpha;

        // upper case
      } else if (alpha >= 'A' & alpha <= 'Z') {

        alpha = (char) ((alpha + rotation));

        // check out of bounds condition
        if (alpha > 'Z') {

          alpha = (char) (alpha + 'A' - 'Z' - 1);

        }

        // append new char to final text var
        cipheredText += alpha;

      } else {

        // if not a character, just return it
        cipheredText += alpha;

      }
    }

    return cipheredText;
  }

  @Override
  public void run() {

    try {

      // create input and output streams
      BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
      PrintWriter out = new PrintWriter(socket.getOutputStream());

      // get the first input as rotation amount
      String rotation;
      rotation = in.readLine();

      // make sure rotation is in the range 0 to 25
      if (Integer.parseInt(rotation) < 0 | Integer.parseInt(rotation) > 25) {

        // error message
        System.out.println("\n ** ERROR: enter an integer in the range 0 to 25 ** \n");

        // close connections
        in.close();
        out.close();
        socket.close();

        // terminate
        System.exit(1);

      } else {

        // send rotation amount back to client
        out.println(rotation);
        out.flush();

      }

      String cipheredText;

      String line = in.readLine();
      while (line != null) {

        // call process function to rotate the line
        cipheredText = process(line, Integer.parseInt(rotation));

        // print out result
        out.println("Ciphered: " + cipheredText);
        out.flush();

        line = in.readLine();
      }

      // close connections
      in.close();
      out.close();
      socket.close();

      System.out.println("\nConnection has closed... See you soon!");

    } catch (Exception exc) {
      exc.printStackTrace();
    }
  }
}