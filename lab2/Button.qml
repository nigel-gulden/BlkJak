import QtQuick 2.0

Rectangle{
    id: insideButton

    signal buttonClicked()
    signal hoverStart()
    signal hoverFinish()
    property alias buttonText: b_text


    MouseArea{

        Text{
            id: b_text
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }


        anchors.fill: parent
        onClicked: insideButton.buttonClicked()

        hoverEnabled: true
        onHoveredChanged:
        {
            if(containsMouse)
            {
                parent.hoverStart()
            }
            else
            {
                parent.hoverFinish()
            }
        }

    }
}
