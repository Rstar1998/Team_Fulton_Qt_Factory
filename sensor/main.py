import paho.mqtt.client as mqtt  # Use mqtt client for connection
import json
import time
import random
import datetime

# Define the MQTT broker address and port
broker_address = "localhost"
broker_port = 1883

# Define the topic
topic = "factory/sensors/environment"


def generate_sensor_data():
    """Generate simulated sensor data for temperature, humidity, and air quality index."""
    data = {
        "temperature": round(random.uniform(15, 30), 2),  # Temperature in °C
        "humidity": round(random.uniform(30, 70), 2),    # Humidity in %
        "air_quality_index": random.randint(0, 500),     # AQI
        "timestamp": datetime.datetime.now().isoformat() # ISO 8601 timestamp
    }
    return data


def on_connect(client, userdata, flags, rc):
    """Callback function executed when connected to the broker."""
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print(f"Failed to connect, return code {rc}")


# Create an MQTT client instance
client = mqtt.Client()

# Set the on_connect callback function
client.on_connect = on_connect

# Connect to the MQTT broker
client.connect(broker_address, broker_port)

# Start the client loop (background network processing)
client.loop_start()

try:
    while True:

        message = generate_sensor_data()

        # Convert the message to JSON format
        payload = json.dumps(message)

        # Publish the message
        client.publish(topic, payload)

        print(f"Published message on topic '{topic}': {payload}")

        # Wait for 1 seconds before sending the next message
        time.sleep(1)

except KeyboardInterrupt:
    # Exit cleanly on Ctrl+C
    client.loop_stop()
    client.disconnect()
    print("Exiting program...")