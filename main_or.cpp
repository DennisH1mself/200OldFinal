#include <Arduino.h>
#define LED_PIN 9
#define SECRET_SSID "DennisNet"
#define SECRET_PASS "dennis_is_a_menace"

#include "WiFiS3.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID; // your network SSID (name)
char pass[] = SECRET_PASS; // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;          // your network key index number (needed only for WEP)

int led = LED_PIN;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

void printWiFiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void setup()
{
  Serial.begin(9600);
  while (!Serial) {}
  pinMode(led, OUTPUT);

  /*if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");
    while (true)
      ;
  }*/

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please upgrade the firmware");
  }

  WiFi.config(IPAddress(192, 48, 56, 2));

  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING)
  {
    Serial.println("Creating access point failed");
    while (true)
      ;
  }

  // delay(10000);
  delay(1000); // Give the WiFi time to connect
  server.begin();
  printWiFiStatus();
}
void loop()
{

  // compare the previous status to the current status
  if (status != WiFi.status())
  {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED)
    {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
    }
    else
    {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }
  }

  WiFiClient client = server.available(); // listen for incoming clients

  if (client)
  {                               // if you get a client,
    Serial.println(" - CLIENT ADDED - "); // print a message out the serial port
    String data = "";      // make a String to hold incoming data from the client
    while (client.connected())
    {                        // loop while the client's connected
      delayMicroseconds(10); // This is required for the Arduino Nano RP2040 Connect - otherwise it will loop so fast that SPI will never be served.
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out to the serial monitor
        data += c;          // add it to the string
        if (data.length() > 4 && data.endsWith("\r\n\r\n"))
        { // if the string is long enough, and ends with a carriage return and line feed
          break;              // the end of the HTTP request has been reached
        }
        int ledBrightness = data.toInt(); // convert the string to an integer
        if (ledBrightness >= 0 && ledBrightness <= 1023)
        { // if the integer is between 0 and 255
          analogWrite(led, ledBrightness); // set the LED brightness
          Serial.print("LED brightness set to: ");
          Serial.println(ledBrightness);
          client.println("HTTP/1.1 200 OK"); // send a response to the client
          client.println("Content-Type: text/html"); // send the content type
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println(" - CLIENT REMOVED - ");
  }
}
