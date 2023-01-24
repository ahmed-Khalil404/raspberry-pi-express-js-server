// library SPI et de de carte ds

#include <Wire.h>
// library de base de software console arduino 
// library de protocol i2c

// Initiation des port CE,CSN pour la connection wifi 
  
// Adresse q'on va utiliser pour savoir envoyer a qui

//Adresse utiliser dans le GYRO
#define slave1 0x48

// Adresse de capteur de temperature 1ére adresse valable

#include "DHT.h"
#include "PubSubClient.h" // Connect and publish to the MQTT broker
#include "WiFi.h" // Enables the ESP32 to connect to the local network (via WiFi)
#include <dht11.h>
#define DHT11PIN 4 // broche DATA -> broche 4
 
dht11 dht;

// WiFi
const char* ssid = "iPhoneM";// Your personal network SSID
const char* wifi_password = "12344321"; 
const char* mqtt_server = "172.20.10.9";  // IP of the MQTT broker

const char* humidity_topic = "humidity";
const char* temperature_topic = "temperature";
const char* gyro_topic = "gyro";
const char* mqtt_username = "pi"; // MQTT username
const char* mqtt_password = "root"; // MQTT password
const char* clientID = "clientAr"; // MQTT client ID

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient); 


// Custom function to connet to the MQTT broker via WiFi
void connect_MQTT(){
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
}

const int MPU_ADDR=0x68;
int16_t accelerometer_x, accelerometer_y, accelerometer_z;
char tmp_str[40]; // temporary variable used in convert function
 char* convert_int16_to_str(int16_t i)
 { // converts int16 to string. Mo reover, resulting strings will have the same length in the debug monitor.
    sprintf(tmp_str, "%6d", i); 
   return tmp_str;
 }
// Les variable de changement brusque des axe x,y,z


// Fonction de convertissement statique les valeur de type int en un chaine de charactere
 
void setup() {


Serial.begin(9600);

// Configuration i2c de la capture de temperature 
  Wire.begin(); 
  Wire.beginTransmission(slave1);
  Wire.write(0xAC); //entree dans le config
  Wire.write(0);  //set for continious loop
  Wire.beginTransmission(slave1);
  Wire.write(0xEE); 
  Wire.endTransmission(); 



         //This sets the module as transmitter


 Wire.begin();
  Wire.beginTransmission (MPU_ADDR); // Commencé la transmission de la composant de gyroscope
  Wire.write (0x6B);// Registre PWR_MGMT_1 de configuraton initiation                
  Wire.write (0);// set to zero (wakes up the MPU-6050)
  Wire.endTransmission (true);
  connect_MQTT();
}



void loop()
{

  Serial.setTimeout(2000);
  
  dht.read(DHT11PIN);
 
  Serial.print("Humidité (%): ");
  Serial.println((float)dht.humidity);
  
 

  // MQTT can only transmit strings
  String hs="Hum: "+String((float)dht.humidity)+" % ";
 
  //Recuperation des données depuis le premiére esclave dans notre systeme le capteur de temperature 
  Wire.beginTransmission(slave1); 
  Wire.write(0xAA); //lire le valeur de la tempereture
  Wire.endTransmission(); 
  Wire.requestFrom(slave1,2);
  int first=Wire.read(); 
  int second=Wire.read(); 
  float temp=first;

    Wire.beginTransmission (MPU_ADDR);
  Wire.write (0x3B); // starting with register 0x3B (ACCEL_XOUT_H) MPU-6000 and MPU-6050 Register Map and Desc riptions Revision 4.2, p.40]
  Wire.endTransmission (false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom (MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
 

  //Lecture des données de gyro depuis les registre implementer
  accelerometer_x = Wire.read ()<<8 |  Wire.read (); //reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)                              
  accelerometer_y = Wire.read ()<<8 | Wire.read (); //reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)                                                      
  accelerometer_z = Wire.read ()<<8 | Wire.read (); //reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
 
 //Verification de la bonne fonctionnement de gyro sur le console arduio 
                                       
  
Serial.print("ax = "); Serial.print (convert_int16_to_str(accelerometer_x));
Serial.print(" |aY = "); Serial.print (convert_int16_to_str(accelerometer_y));
Serial.print(" |aZ = "); Serial.print (convert_int16_to_str(accelerometer_z));
Serial.println("\n");
Serial.println(temp);


if (client.publish(gyro_topic, String((float)dht.humidity).c_str())) {
    Serial.println("Humidity have been send!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("humidity failed to send. Reconnecting to MQTT Broker and trying again");
    
  }


if (client.publish(gyro_topic, String(temp).c_str())) {
    Serial.println("Temperature sent!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Temperature failed to send. Reconnecting to MQTT Broker and trying again");
    
  }



  if (client.publish(gyro_topic, String(convert_int16_to_str(accelerometer_x)).c_str())) {
    Serial.println("gyro sent x!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Gyro failed to send. Reconnecting to MQTT Broker and trying again");
    
  }

 if (client.publish(gyro_topic, String(convert_int16_to_str(accelerometer_y)).c_str())) {
    Serial.println("gyro sent y!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Gyro failed to send. Reconnecting to MQTT Broker and trying again");
    
  }
  


  if (client.publish(gyro_topic, String(convert_int16_to_str(accelerometer_z)).c_str())) {
    Serial.println("gyro sent z!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Gyro failed to send. Reconnecting to MQTT Broker and trying again");
   
  }
  

delay(7000);
  // PUBLISH to the MQTT Broker (topic = Humidity, defined at the beginning)
  
  //client.disconnect();  // disconnect from the MQTT broker
  // print new values every 1 Minute
  
//Envoie de text d'initiation des données 
 
//Envoie de text de la temperature

 

}
