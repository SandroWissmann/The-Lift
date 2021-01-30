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
