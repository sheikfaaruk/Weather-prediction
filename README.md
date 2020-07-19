# weatherprediction
#IOT #ML
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::  
TEMPERATURE:
#Temperature is a degree of hotness or coldness the can be measured using a thermometer. 
#It's also a measure of how fast the atoms and molecules of a substance are moving. 
#Temperature is measured in degrees on the Fahrenheit, Celsius, and Kelvin scales.


HUMIDITY:
#Humidity is the concentration of water vapour present in the air. 
#Water vapour, the gaseous state of water, is generally invisible to the human eye.
#Humidity indicates the likelihood for precipitation, dew, or fog to be present. 
#The amount of water vapour needed to achieve saturation increases as the temperature increases. 
#As the temperature of a parcel of air decreases it will eventually reach the saturation point without adding or losing water mass. 
#The amount of water vapour contained within a parcel of air can vary significantly.

ALSOLUTE PRESSURE and RELATIVE PRESSURE:
#Absolute barometric pressure is the actual atmospheric air pressure at a particular location that profoundly depends upon the location altitude. 
#Relative or sea level pressure is the corrected barometric pressure calculated for the sea or zero level, and usually used to refer atmospheric conditions.

PRECIPTATION:
#Precipitation is rain, snow, sleet, or hail — any kind of weather condition where something's falling from the sky. 
#IT has to do with things falling down, and not just from the sky.
#It's also what happens in chemical reactions when a solid settles to the bottom of a solution

DEW POINT IN TEMPERATURE:
#Dew point is the temperature to which air must be cooled to become saturated with water vapor. 
#When further cooled, the airborne water vapor will condense to form liquid water (dew). 
#When air cools to its dew point through contact with a surface that is colder than the air, water will condense on the surface.

RAIN:
#water that falls in drops from clouds in the sky.
#weather in which there is a lot of rain : rainy weather.
#large amounts of rain that fall at a particular time of year.

Thinks to need
#DHT11,
#BMP180,
#Rain sensor,
#ESP8266,
#jumper wires.


#IOT Live Weather Station Monitoring Using NodemCU ESP8266
This post is all about IoT based Live Weather Station Monitoring Using NodemCU ESP8266. We will interface DHT11 Humidity & Temperature Sensor, BMP180 Barometric Pressure Sensor, and FC37 Rain Sensor with NodeMCU ESP8266-12E Wifi Module. We will measure humidity, temperature, Barometric pressure, and rainfall and upload the data to a web server.


#Using IOT modules to collect the data save as .csv file format in Thingspeak.com .And using that dataset to find the prediction the weather in it . 
Prediction is performed using neural nets with backpropagation. 
Library: Keras.
