/*
  Web Server
 
 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified January 10 2014
 by Chase Roberts
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:\

 //This has to be unique on you local network (This default will usually work)
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//This can be manually changed, but I prefer to use DHCP
IPAddress ip(0,0,0,0);

//These two are only used when DHCP fails
IPAddress gateway(192,168,1, 1);
IPAddress subnet(255, 255, 0, 0);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
EthernetServer server(8888);
int ledPin = 7;
boolean incoming = 0;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // this check is only needed on the Leonardo:
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  pinMode(ledPin, OUTPUT);
  // start the Ethernet connection:
  Serial.println("Trying to get an IP address using DHCP");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // initialize the ethernet device not using DHCP:
    Ethernet.begin(mac, ip, gateway, subnet);
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  ip = Ethernet.localIP();
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(ip[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
  // start listening for clients
  server.begin();
 
}

void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        
        //reads URL string from $ to first blank space
        if(incoming && c == ' '){ 
          incoming = 0;
        }
        if(c == '$'){ 
          incoming = 1; 
        }
        
        //Checks for the URL string $1 or $2
        if(incoming == 1){
          Serial.println(c);
          
          if(c == '1'){
            Serial.println("ON");
            digitalWrite(ledPin, HIGH);
            incoming = 0;
          }
          if(c == '2'){
            Serial.println("OFF");
            digitalWrite(ledPin, LOW);
            incoming =0;
          }
        }
      
    
     if (c == '\n' && currentLineIsBlank) 
       {
        // send a standard http response header
          //
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the respons
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("Signal Recieved");
          client.println("</html>");
          break;
        }
        if (c == '\n') 
        {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') 
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
  }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
}

