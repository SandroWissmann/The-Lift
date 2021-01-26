import QtQuick 2.15
import QtQuick.Layouts 2.15

Item {
    id: root
    required property string peopleWithDestinations
    required property int row

    Rectangle {
        id: floorRect
        anchors.fill: parent
        border.color: "black"
        color: "yellow"

        ColumnLayout {
            Text {
                id: displayText
                height: floorRect.height / 2
                Layout.fillWidth: true
                text: root.peopleWithDestinations
            }
        }
    }
}
