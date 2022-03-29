/*
 * Client Side
 * Author: Coleman Ulry
 * Date: 4/24/21
 * Resources used: https://www.infoworld.com/article/2853780/socket-programming-for-scalable-systems.html
 * and https://docs.oracle.com/javase/tutorial/networking/sockets/readingWriting.html
 */

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;
import java.io.PrintWriter;

public class CipherClient {
   public static void main(String[] args) {

      // welcome message
      System.out.println("\n -- WELCOME TO THE CAESAR CIPHER -- \n");

      // set command line arguments to variables
      String server = args[0];
      int port = Integer.parseInt(args[1]); // convert to integer

      try {

         // connect to server
         Socket socket = new Socket(server, port);

         // obtain input and output streams
         PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
         BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
         BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));

         // get rotation from user
         System.out.println("Enter a rotation amount: ");
         String input;

         while ((input = stdIn.readLine()) != null) {

            // check exit condition
            if (input.equals("quit")) {
               System.out.println("\n -- QUITTING CAESAR CIPHER -- \n");
               break;
            }

            // send server the input
            out.println(input);

            // print out result from server
            System.out.println(in.readLine() + "\n");

            // display prompt
            System.out.println("Enter a text, or 'quit' to exit: ");
         }

         // close streams
         in.close();
         out.close();
         socket.close();

         // exit program
         System.exit(0);

      } catch (Exception exc) {
         exc.printStackTrace();
      }
   }
}