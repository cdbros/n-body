import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Layouts 1.12
import NBody 1.0

Window {
    readonly property string c_title: qsTr("N Body Simulation")
    readonly property int c_width: 640
    readonly property int c_height: 480
    readonly property double c_gl_width_percent: .70
    readonly property double c_config_width_percent: .30
    readonly property string c_background_color: "#000000"
    readonly property string c_border_color: "#9B9B9B"

    visible: true
    width: c_width
    height: c_height
    color: c_background_color
    title: c_title

    RowLayout {
        width: parent.width
        height: parent.height
        spacing: 0

        SimView {
            id: simulation
            Layout.preferredWidth: parent.width * c_gl_width_percent
            Layout.preferredHeight: parent.height
            focus: true

            onWidthChanged: {
                simulation.width = Layout.preferredWidth
            }

            onHeightChanged: {
                simulation.height = Layout.preferredHeight
            }
        }

        // border
        Rectangle {
            Layout.preferredWidth: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: c_border_color
        }

        Rectangle {
            id: configPanel
            Layout.preferredWidth: parent.width * c_config_width_percent
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: c_background_color
        }
    }
}
