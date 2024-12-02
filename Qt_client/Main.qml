import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

Window {
    visible: true
    width: 800
    height: 600
    title: "Factory Sensor Monitor"

    // Dark background for the entire window
    color: "#121212"

    Component.onCompleted: {
        mqttManager.connectToHost()
    }

    // Center the entire content
    Item {
        anchors.centerIn: parent
        width: Math.min(parent.width * 0.9, 800)
        height: Math.min(parent.height * 0.9, 600)

        ColumnLayout {
            anchors.fill: parent
            spacing: 20

            Label {
                text: "Industrial IoT Sensor Dashboard"
                font.pixelSize: 24
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
                color: "white"
            }

            GridLayout {
                columns: 3
                Layout.fillWidth: true
                Layout.fillHeight: true
                columnSpacing: 20
                rowSpacing: 20

                // Temperature Display
                Rectangle {
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 150
                    color: "#1E1E1E"
                    border.color: "#333333"
                    radius: 10

                    ColumnLayout {
                        anchors.centerIn: parent

                        Label {
                            text: "Temperature"
                            font.pixelSize: 16
                            Layout.alignment: Qt.AlignHCenter
                            color: "#BBBBBB"
                        }

                        Label {
                            text: mqttManager.temperature.toFixed(2) + " °C"
                            font.pixelSize: 24
                            font.bold: true
                            Layout.alignment: Qt.AlignHCenter
                            color: "white"
                        }
                    }
                }

                // Humidity Display
                Rectangle {
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 150
                    color: "#1E1E1E"
                    border.color: "#333333"
                    radius: 10

                    ColumnLayout {
                        anchors.centerIn: parent

                        Label {
                            text: "Humidity"
                            font.pixelSize: 16
                            Layout.alignment: Qt.AlignHCenter
                            color: "#BBBBBB"
                        }

                        Label {
                            text: mqttManager.humidity.toFixed(2) + " %"
                            font.pixelSize: 24
                            font.bold: true
                            Layout.alignment: Qt.AlignHCenter
                            color: "white"
                        }
                    }
                }

                // Air Quality Display
                Rectangle {
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 150
                    color: "#1E1E1E"
                    border.color: "#333333"
                    radius: 10

                    ColumnLayout {
                        anchors.centerIn: parent

                        Label {
                            text: "Air Quality Index"
                            font.pixelSize: 16
                            Layout.alignment: Qt.AlignHCenter
                            color: "#BBBBBB"
                        }

                        Label {
                            text: mqttManager.airQualityIndex
                            font.pixelSize: 24
                            font.bold: true
                            Layout.alignment: Qt.AlignHCenter
                            color: "white"
                        }
                    }
                }
            }
        }
    }
}
