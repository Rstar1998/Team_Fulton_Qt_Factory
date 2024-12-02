#include "mqttmanager.h"
#include <QDebug>

MqttManager::MqttManager(QObject *parent)
    : QObject(parent), m_client(new QMqttClient(this)),
    m_temperature(0.0), m_humidity(0.0), m_airQualityIndex(0)
{
    connect(m_client, &QMqttClient::messageReceived,
            this, &MqttManager::onMessageReceived);
}

void MqttManager::connectToHost(const QString &host, int port)
{
    qDebug() << "MqttManager::connectToHost";
    m_client->setHostname(host);
    m_client->setPort(port);
    m_client->connectToHost();

    // Subscribe to topic
     qDebug() << "MqttManager::connectToHost::m_client->state";
    qDebug() << m_client->state();

    if (m_client->state() == QMqttClient::Connected) {
        auto subscription = m_client->subscribe(QMqttTopicFilter("factory/sensors/environment"));
        if (!subscription) {
            qDebug() << "Could not subscribe to topic";
        }
    }
}

void MqttManager::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    QJsonDocument doc = QJsonDocument::fromJson(message);
    QJsonObject jsonObj = doc.object();

    qDebug() << "MqttManager::onMessageReceived";

    // Update values
    m_temperature = jsonObj["temperature"].toDouble();
    m_humidity = jsonObj["humidity"].toDouble();
    m_airQualityIndex = jsonObj["air_quality_index"].toInt();

    // Emit change signals
    emit temperatureChanged();
    emit humidityChanged();
    emit airQualityIndexChanged();

    qDebug() << "Received: Temp=" << m_temperature
             << "Humidity=" << m_humidity
             << "AQI=" << m_airQualityIndex;
}
