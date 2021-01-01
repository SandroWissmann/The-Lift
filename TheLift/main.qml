import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 2.15

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("the Lift")

    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height

    ListModel {
        id: testModel
        ListElement {
            name: "0"
            person: "1, 2, 3, 4, 5"
        }
        ListElement {
            name: "1"
            person: "4 3 2 1 0"
        }
        ListElement {
            name: "2"
            person: "5 4 3"
        }
        ListElement {
            name: "3"
            person: "1 1 1"
        }
        ListElement {
            name: "4"
            person: "4 3 2"
        }
        ListElement {
            name: "5"
            person: "3 2 1"
        }
        ListElement {
            name: "6"
            person: ""
        }
        ListElement {
            name: "7"
            person: "1 3 4"
        }
    }

    RowLayout {
        ListView {
            id: floorListView
            width: root.width / 2
            height: root.height
            Layout.fillHeight: true
            Layout.margins: 0
            clip: true

            verticalLayoutDirection: ListView.BottomToTop

            contentHeight: root.height
            contentWidth: root.width / 2
            model: testModel

            delegate: FloorDelegate {
                height: root.height / testModel.count
                width: root.width / 2
            }
        }
        ElevatorShaft {
            id: elevatorShaft
            Layout.fillHeight: true
            width: root.width / 2
            floorCount: testModel.count
            currenFloor: 4
        }
    }
}
