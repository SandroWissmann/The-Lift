import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 2.15

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("the Lift")

    property alias floorModel: floorListView.model
    //property int floorCount: root.floorModel.rowCount()
    property int floorCount: 7

    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height

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

            delegate: FloorDelegate {
                height: root.height / root.floorCount
                width: root.width / 2
            }
        }
        ElevatorShaft {
            objectName: "elevatorShaftObject"
            id: elevatorShaft
            Layout.fillHeight: true
            width: root.width / 2
            floorCount: root.floorCount
            currenFloor: backend.liftFloor
        }
    }
}
