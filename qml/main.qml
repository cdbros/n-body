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
            focus: true

            Component.onCompleted: {
                simulation.setWidth(width)
                simulation.setHeight(height)
            }
        }

        Rectangle {
            id: configPanel
            Layout.preferredWidth: parent.width * .30
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "red";
        }
    }
}
