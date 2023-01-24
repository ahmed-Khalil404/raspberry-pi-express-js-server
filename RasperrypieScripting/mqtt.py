import paho.mqtt.client as mqtt

MQTT_ADDRESS = '172.20.10.9'
MQTT_USER = 'pi'
MQTT_PASSWORD = 'root'
MQTT_TOPIC = 'gyro'


def on_connect(client, userdata, flags, rc):

    client.subscribe(MQTT_TOPIC)


def on_message(client, userdata, msg):
    characters = [chr(ascii) for ascii in msg.payload] # Convert ASCII to char
    chars_joined =''.join(characters) # Join chars to a string
    #received_message = chars_joined.split(",")     # Split string by comma
    print(chars_joined);
    #print(str(msg.payload));
    a = str(chars_joined)
    f = open('mqtt.txt', 'a+')
    f.write(a+"\n")
    
    

def main():
    mqtt_client = mqtt.Client()
    mqtt_client.username_pw_set(MQTT_USER, MQTT_PASSWORD)
    mqtt_client.on_connect = on_connect
    mqtt_client.on_message = on_message

    mqtt_client.connect(MQTT_ADDRESS, 1883)
    mqtt_client.loop_forever()
    

if __name__ == '__main__':
    main()

