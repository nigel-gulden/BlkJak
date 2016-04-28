import QtQuick 2.0

Rectangle{
    id: t_rect

    property string textstring: t_text.text

    property color textcolor: t_text.color
    property alias textfont: t_text.font
    onTextstringChanged: t_text.text = textstring
    onTextcolorChanged: t_text.color = textcolor



    Text{
        id: t_text
        anchors.horizontalCenter: t_rect.horizontalCenter
        anchors.verticalCenter: t_rect.verticalCenter

    }
}
