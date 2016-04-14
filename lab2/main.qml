import QtQuick 2.6
import QtQuick.Window 2.2


Window {
    id: win
    visible: true
    height: 400
    width: 600
    //Name: Nigel Gulden, Justin Broughton
    //Lab: 2 Splash screen
    //Blkjak
Item{
    id: window
    anchors.fill: parent

    Dialog{
        id:dialog2
        color: "green"
        height: 300
        width:500

        x: 50
        y: 50


        textbox.textcolor: "yellow"
        textbox.color: "transparent"
        textbox.textfont.pointSize: 20
        textbox.textstring: "hello from justin and nigel"
        textbox.width: 300
        textbox.height: 200
        textbox.anchors.top: dialog2.top
        textbox.anchors.horizontalCenter: dialog2.horizontalCenter

        button.onButtonClicked: win.close()
        button.color: "blue"
        button.onHoverStart: button.color = "yellow"
        button.onHoverFinish: button.color = "blue"
        button.buttonText.text:  "goodbye"
        button.buttonText.font.pointSize: 12
        button.height: 100
        button.width: 200
        button.anchors.top: textbox.bottom
        button.anchors.horizontalCenter: textbox.horizontalCenter
        button.z: 9
        button.radius: 20
        button.border.width: 3
        button.border.color: "black"
    }

    Dialog{
        id:dialog
        color: "red"
        width:500
        height: 300
        x: 50
        y: 50


        textbox.textcolor: "blue"
        textbox.color: "transparent"
        textbox.textfont.pointSize: 20
        textbox.textstring: "Our project will be a GUI for \n blackjack"
        textbox.width: 300
        textbox.height: 200
        textbox.anchors.top: dialog.top
        textbox.anchors.horizontalCenter: dialog.horizontalCenter


        button.onButtonClicked: dialog.visible = false
        button.color: "blue"
        button.onHoverStart: button.color = "yellow"
        button.onHoverFinish: button.color = "blue"
        button.buttonText.text:  "okay"
        button.buttonText.font.pointSize: 12
        button.height: 100
        button.width: 200
        button.anchors.top: textbox.bottom
        button.anchors.horizontalCenter: textbox.horizontalCenter
        button.z: 10
        button.radius: 20
        button.border.width: 3
        button.border.color: "black"
    }





}

}
