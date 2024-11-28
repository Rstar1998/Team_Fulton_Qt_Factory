import paho.mqtt.publish as publish
import json
import time
import random
import time
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


# Publish messages periodically every 3 seconds
while True:

    message = generate_sensor_data()

    # Convert the message to JSON format
    payload = json.dumps(message)

    # Publish the message
    publish.single(topic, payload, hostname=broker_address,port=broker_port)

    print(f"Published message on topic '{topic}': {payload}")

    # Wait for 3 seconds before sending the next message
    time.sleep(1)