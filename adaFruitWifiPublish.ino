

/************************** Configuration ***********************************/

// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"


/************************ Example Starts Here *******************************/


// set up the feed
AdafruitIO_Feed *humedad = io.feed("humedad");
AdafruitIO_Feed *temp = io.feed("sensor-de-temp");

// Instance of Sensor DHT
DHT dht(DHTPin, DHTTipo);

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");
  

  // connect to io.adafruit.com
  io.connect();

  Serial.println("DHT Sensor");

  // Init DHT Sensor
  dht.begin();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // Read the temp and humidity of the DHT Sensor
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  // Error Read
  if(isnan(t) || isnan(h)){

    Serial.println("Lectura erronea");
    return;
  }
  
  Serial.println("Humedad: ");
  Serial.println(h);
  Serial.println("%\t");
  Serial.println("Temperatura: ");
  Serial.println(t);
  Serial.println(" C ");

  // Publish in Adafruit
  temp->save(t);
  humedad->save(h);

  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);

}
