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

Item {
    id: root

    property int floorCount
    property int currenFloor

    property alias peopleInLift: peopleInLiftText.text
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

            Text {
                anchors.fill:parent
                id: peopleInLiftText
            }
        }
    }
}
