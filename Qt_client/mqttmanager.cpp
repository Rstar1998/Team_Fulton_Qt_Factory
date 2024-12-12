#include "mqttmanager.h"
#include <QDebug>

MqttManager::MqttManager(QObject *parent)
    : QObject(parent),
    m_client(new QMqttClient(this)),
    m_temperature(0.0),
    m_humidity(0.0),
    m_airQualityIndex(0)
{
    // Connect MQTT client signals
    connect(m_client, &QMqttClient::messageReceived,
            this, &MqttManager::onMessageReceived);

    connect(m_client, &QMqttClient::stateChanged,
            this, &MqttManager::onStateChanged);
}

void MqttManager::connectToHost(const QString &host, int port)
{
    qDebug() << "Attempting to connect to MQTT broker:" << host << ":" << port;

    m_client->setHostname(host);
    m_client->setPort(port);
    m_client->connectToHost();
}

void MqttManager::disconnectFromHost()
{
    m_client->disconnectFromHost();
}

void MqttManager::onStateChanged(QMqttClient::ClientState state)
{
    qDebug() << "MQTT Client State Changed:" << state;

    switch(state) {
    case QMqttClient::Disconnected:
        qDebug() << "Disconnected from MQTT broker";
        break;
    case QMqttClient::Connecting:
        qDebug() << "Connecting to MQTT broker...";
        break;
    case QMqttClient::Connected:
        qDebug() << "Connected to MQTT broker";
        // Subscribe to topic when connected
        auto subscription = m_client->subscribe(QMqttTopicFilter("factory/sensors/environment"), 1);
        if (!subscription) {
            qDebug() << "Could not subscribe to topic";
        }
        break;
    }

    emit connectionStatusChanged();
}

void MqttManager::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    qDebug() << "Message received on topic:" << topic;

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON parse error:" << parseError.errorString();
        return;
    }

    if (!doc.isObject()) {
        qDebug() << "Received JSON is not an object";
        return;
    }

    QJsonObject jsonObj = doc.object();

    // Safely extract values with default fallbacks
    m_temperature = jsonObj.value("temperature").toDouble(m_temperature);
    m_humidity = jsonObj.value("humidity").toDouble(m_humidity);
    m_airQualityIndex = jsonObj.value("air_quality_index").toInt(m_airQualityIndex);

    // Emit change signals
    emit temperatureChanged();
    emit humidityChanged();
    emit airQualityIndexChanged();

    qDebug() << "Received: Temp=" << m_temperature
             << "Humidity=" << m_humidity
             << "AQI=" << m_airQualityIndex;
}
