import QtQuick 2.15

Item {
    id: root

    property int floorCount
    property int currenFloor
    Rectangle {
        id: shaftRect
        width: root.width
        height: root.height
        border.color: "black"
        color: "white"

        Rectangle {
            id: elevatorRect
            height: shaftRect.height / root.floorCount
            width: shaftRect.width

            border.color: "black"
            color: "red"
            x: shaftRect.x
            y: shaftRect.y + height * (root.floorCount - currenFloor - 1)

            Behavior on y {

                NumberAnimation {
                    duration: 500
                    easing.type: Easing.InOutQuad
                }
            }
        }

        property bool up: true
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (root.currenFloor == root.floorCount - 1) {
                    shaftRect.up = false
                }
                if (root.currenFloor == 0) {
                    shaftRect.up = true
                }
                if (shaftRect.up) {
                    ++root.currenFloor
                } else {
                    --root.currenFloor
                }
            }
        }
    }
}
