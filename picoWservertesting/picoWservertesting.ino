/*
Thanks to michael from hackclub.
*/


#include <WiFi.h>

// Replace with your desired network credentials
const char* ssid = "";
const char* password = "";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.setHostname("PicoW2");
  Serial.printf("Connecting to '%s' with '%s'\n", ssid, password);
  WiFi.begin(ssid, password);

/*
  // Start the access point
  Serial.print("Starting PiFli");
  if (WiFi.softAP(ssid, password)) {
    Serial.println("Access Point Started");
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    Serial.println("Failed to start AP");
    digitalWrite(LED_BUILTIN, HIGH);
     delay(100);                       // wait for a second
     digitalWrite(LED_BUILTIN, LOW);
    while (true);

  }
*/

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // Start the server
  server.begin();
  digitalWrite(LED_BUILTIN, LOW);  


  Serial.printf("Connecting to '%s' with '%s'\n", ssid, password);


}


void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // Web Page Content
            client.println("<!DOCTYPE html><html>");
            client.println("<head>");
            client.println("<title>Testing</title>");
            client.println("<style>");
            client.println("body { font-family: Arial, sans-serif; background-color: #f0f0f0; text-align: center; padding: 50px; }");
            client.println("h1 { color: #333; }");
            client.println("</style>");
            client.println("</head>");
            client.println("<body><h1>Welcome!</h1></body>");
            client.println("<body><h1>Pico Web Portal</h1></body>");
            client.println("<body><h2>Authorized Access ONLY</h2></body>");
            client.println("<p>Input 1</p>");
            client.println("<input type=\"range\" min=\"1\" max=\"100\" value=\"50\" class=\"slider\" id=\"cameractrl\">");
            client.println("<p>Input 2</p>");
            client.println("<input type=\"range\" min=\"1\" max=\"100\" value=\"50\" class=\"slider\" id=\"accesoryctrl\">");
            client.println("</html>");
            
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}