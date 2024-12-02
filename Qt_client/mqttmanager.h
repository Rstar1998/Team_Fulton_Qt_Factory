#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <QObject>
#include <QMqttClient>
#include <QJsonObject>
#include <QJsonDocument>

class MqttManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(double humidity READ humidity NOTIFY humidityChanged)
    Q_PROPERTY(int airQualityIndex READ airQualityIndex NOTIFY airQualityIndexChanged)

public:
    explicit MqttManager(QObject *parent = nullptr);

    double temperature() const { return m_temperature; }
    double humidity() const { return m_humidity; }
    int airQualityIndex() const { return m_airQualityIndex; }

    Q_INVOKABLE void connectToHost(const QString &host = "localhost", int port = 1883);

signals:
    void temperatureChanged();
    void humidityChanged();
    void airQualityIndexChanged();

private slots:
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);

private:
    QMqttClient *m_client;
    double m_temperature;
    double m_humidity;
    int m_airQualityIndex;
};

#endif // MQTTMANAGER_H


