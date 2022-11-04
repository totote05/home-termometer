#include <ESP8266WiFi.h>
#include <DHT.h>

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN D5
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11
 
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println();

  dht.begin();

  WiFi.begin("", "");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
    // Esperamos 5 segundos entre medidas
  delay(5000);
 
  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);
 
  Serial.print("Temp ");
  Serial.print(t);
  Serial.print("°/");
  Serial.print(hic);
  Serial.print("° (st) - ");
  Serial.print("Hum ");
  Serial.print(h);
  Serial.println("%");
}