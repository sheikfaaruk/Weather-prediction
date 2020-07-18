#include <DHT.h>  // HEADER FILES 
#include <ESP8266WiFi.h>
#include <SFE_BMP180.h>
#include <SPI.h>
#include <Wire.h>
#define DHTPIN 0
DHT dht(DHTPIN, DHT11);
SFE_BMP180 pressure;
int sensorPin = A0;
int sensorValue2 = 0;  // variable to store the value coming from sensor Rain sensor
#define ALTITUDE 80.0 // Altitude of SparkFun's HQ in Boulder, CO. in meters
String apiKey = "ENTER UR APIKEY HERE";//  Enter your Write API key from ThingSpeak

const char *ssid =  "ERROR"; // replace with your wifi ssid and wpa2 key
const char *pass =  "NOPASSWORD";
const char* server = "api.thingspeak.com";

#define DHTPIN 0 //pin where the dht11 is connected
WiFiClient client;
//--------------------------------------SET UP----------------------------------------------
void setup()
{
  Serial.begin(115200); // open serial port, set the baud rate to 9600 bps
  delay(10);
  dht.begin();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
    {
  delay(500);
  Serial.print(".");
    }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("REBOOT");

  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin())
  {
    Serial.println("BMP180 init success");
  }
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail\n\n");
  }
}
//---------------------------------------LOOP FUNCTION-------------------------------------
void loop()
{
//--------------------------------------DHT11--------------------------------
      float h = dht.readHumidity();
      float t = dht.readTemperature();
	  
	     if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
				             Serial.print("Temperature: ");
                     Serial.print(t);
                     Serial.print(" degrees Celcius, Humidity: ");
                     Serial.print(h);
                     Serial.println("%. Send to Thingspeak.");
//--- extra---- you can measure dew point with the temperature and the humidity
  
		     double gamma = log(h/100) + ((17.62*t) / (243.5+t));
	             double dp = 243.5*gamma / (17.62-gamma);
	             Serial.print("Dew point:        ");
		     Serial.print(dp);
		     Serial.print(" degrees Celsius ");
		     Serial.println();
//--------------------------------------RAIN---------------------------------
  
      const int sensorMin = 150; //0;     // sensor minimum
      const int sensorMax = 440; //1024;  // sensor maximum
   
      delay(500);
      sensorValue2 = analogRead(sensorPin);
      sensorValue2 = constrain(sensorValue2, 150, 440); //150, 400
      sensorValue2 = map(sensorValue2, sensorMin, sensorMax, 0, 1023);  //150, 440
      Serial.print("Rain value:       ");
      Serial.println(sensorValue2);
      Serial.println();
      delay(100);
      Serial.println("Rain===============================");
//---------------------------------BMP180-------------------------------
	    char status;
      double T,P,p0,a;
      status = pressure.startTemperature();
      if (status != 0)
      {
      // Wait for the measurement to complete:
      delay(status);

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          // Print out the measurement:
          Serial.print("absolute pressure: ");
          Serial.print(P,2);
          Serial.print(" mb, ");
          Serial.print(P*0.0295333727,2);
          Serial.println(" inHg");
  
          p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
          Serial.print("relative (sea-level) pressure: ");
          Serial.print(p0,2);
          Serial.print(" mb, ");
          Serial.print(p0*0.0295333727,2);
          Serial.println(" inHg");
         
          a = pressure.altitude(P,p0);
          Serial.print("computed altitude: ");
          Serial.print(a,0);
          Serial.print(" meters, ");
          Serial.print(a*3.28084,0);
          Serial.println(" feet");
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }


//-------------------------------------------------ThingSpeak-------------------------------
              
      if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
           {  
                            
              String postStr = apiKey;
              postStr +="&field1=";
              postStr += String(t);//temperature
              postStr +="&field2=";
              postStr += String(h);//humidity
              postStr += "&field3=";
	      postStr += String(dp);//dew point
	      postStr += "&field4=";
	      postStr += String(P*0.0295333727,2);//absolute pressure
	      postStr += "&field5=";
	      postStr += String(p0*0.0295333727,2);//relative pressure
	      postStr += "&field6=";
	      postStr += String(a,0);//altitudE
	      postStr +="&field7=";
	      postStr += String(sensorValue2);//rain
	      postStr += "\r\n\r\n\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                            
                        }
      client.stop();
      Serial.println("Waiting...");
      Serial.println("");
      Serial.println("***************************************************");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(5000);
  }
