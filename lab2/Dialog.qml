import QtQuick 2.0

Rectangle {
    id:background
    property alias button: b1

    property alias textbox: t1

    TextRect{
        id: t1

    }
    Button{id: b1



    }
    MouseArea{
        anchors.fill: background
        drag.target: background
        drag.axis: Drag.XAndYAxis
        drag.minimumX: 0
        drag.minimumY: 0
    }
}
