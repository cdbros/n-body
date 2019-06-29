import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Layouts 1.12
import NBody 1.0

Window {
    visible: true
    width: 640
    height: 480
    color: "#000000"
    title: qsTr("N Body Simulation")

    RowLayout {
        width: parent.width
        height: parent.height

        SimView {
            id: simulation
            Layout.preferredWidth: parent.width * .70
            Layout.preferredHeight: parent.height
            focus: true

            onWidthChanged: {
                simulation.width = Layout.preferredWidth
            }

            onHeightChanged: {
                simulation.height = Layout.preferredHeight
            }
        }

        Rectangle {
            id: border
            Layout.preferredWidth: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#9B9B9B"
        }

        Rectangle {
            id: configPanel
            Layout.preferredWidth: parent.width * .30
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "black";
        }
    }
}
