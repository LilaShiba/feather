#include <ESP8266WiFi.h>
const char* ssid     = "";
const char* password = "";


char* host = "cyborg-solar.herokuapp.com";
char* url= "/raw_data";


void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
   WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // This will send the request to the server
  client.println(String("GET ") + url + " HTTP/1.1");
  client.print("Host: ");
  client.println("cyborg-solar.herokuapp.com");
  client.println("User-Agent: curl/7.47.0");
  client.println();
  delay(800);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
}
n