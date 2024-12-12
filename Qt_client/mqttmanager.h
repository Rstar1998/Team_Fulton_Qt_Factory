
#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <QObject>
#include <QMqttClient>
#include <QJsonDocument>
#include <QJsonObject>

class MqttManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(double humidity READ humidity NOTIFY humidityChanged)
    Q_PROPERTY(int airQualityIndex READ airQualityIndex NOTIFY airQualityIndexChanged)

public:
    explicit MqttManager(QObject *parent = nullptr);

    Q_INVOKABLE void connectToHost(const QString &host = "localhost", int port = 1883);
    Q_INVOKABLE void disconnectFromHost();

    double temperature() const { return m_temperature; }
    double humidity() const { return m_humidity; }
    int airQualityIndex() const { return m_airQualityIndex; }

signals:
    void temperatureChanged();
    void humidityChanged();
    void airQualityIndexChanged();
    void connectionStatusChanged();

private slots:
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
    void onStateChanged(QMqttClient::ClientState state);

private:
    QMqttClient *m_client;
    double m_temperature;
    double m_humidity;
    int m_airQualityIndex;
};

#endif // MQTTMANAGER_H
