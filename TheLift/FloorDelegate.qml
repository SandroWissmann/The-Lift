import QtQuick 2.15
import QtQuick.Layouts 2.15

Item {
    Rectangle {
        id: floorRect
        anchors.fill: parent
        border.color: "black"
        color: "yellow"

        ColumnLayout {
            Text {
                height: floorRect.height / 2
                Layout.fillWidth: true
                text: name
            }
            Text {
                height: floorRect.height / 2
                Layout.fillWidth: true
                text: person == undefined ? "" : person
            }
        }
    }
}
