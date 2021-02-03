
/* The Lift
 * Copyright (C) 2021  Sandro Wißmann
 *
 * The Lift is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Lift is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with The Lift If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: https://github.com/SandroWissmann/The-Lift
 */
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 2.15

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("the Lift")

    property alias floorModel: floorListView.model

    property int floorCount: root.floorModel.rowCount()
    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height

    ColumnLayout {
        RowLayout {
            ListView {
                id: floorListView
                width: root.width / 2
                height: root.height - toggleLift.height
                Layout.fillHeight: true
                Layout.margins: 0
                clip: true

                verticalLayoutDirection: ListView.BottomToTop

                contentHeight: root.height
                contentWidth: root.width / 2

                delegate: FloorDelegate {
                    height: floorListView.height / root.floorCount
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
                peopleInLift: backend.peopleInLift
            }
        }
        RowLayout {
            Label {
                text: "Simulation on/off"
            }
            Switch {
                id: toggleLift

                onPositionChanged: {
                    if (position == 1.0) {
                        backend.liftStarted = true
                    } else if (position == 0.0) {
                        backend.liftStarted = false
                    }
                }
            }
        }
    }
}
