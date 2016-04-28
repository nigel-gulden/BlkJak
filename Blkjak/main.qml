import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Window 2.2
import QtQml.Models 2.2
import "CardCreation.js" as CardCreator
import MyExt 1.0
import Qt.labs.settings 1.0

ApplicationWindow {

    id: window
    visible: true
    width: 1024
    height: 768
    title: qsTr("BlkJak")
    onClosing:
    {
        settings_global.bankroll = game.getBankroll()
    }

    Settings
    {
        id: settings_global
        property int bankroll:0

    }

    Dialog{
        id:dialog
        color: "green"
        height: 300
        width:500
        property alias bank: bankinputbg

        x: 234
        y: 262
        z: 1
        border.color: "black"
        border.width: 8
        radius: 20

        textbox.textcolor: "yellow"
        textbox.color: "transparent"
        textbox.textfont.pointSize: 20
        textbox.textstring: "Welcome to BlkJak!"
        textbox.width: 500
        textbox.height: 100
        textbox.anchors.top: dialog.top
        textbox.anchors.horizontalCenter: dialog.horizontalCenter

        Rectangle
        {
            id: bankinputbg
            property alias input: bankinputfield
            height: 50
            x: 100
            y: 100
            width: 300
            visible: false
            TextInput{
                id: bankinputfield
                font.pixelSize: 50
                anchors.fill: bankinputbg
                onAccepted:
                {
                    var money = parseInt(text)
                    console.log(money)
                    settings_global.bankroll = money
                    game.setBankroll(settings_global.bankroll)
                    dialog.visible = false
                }

            }
        }



        button.color: "blue"
        button.onHoverStart: button.color = "yellow"
        button.onHoverFinish: button.color = "blue"
        button.buttonText.text:  "Hello!"
        button.buttonText.font.pointSize: 12
        button.height: 70
        button.width: 200
        button.anchors.top: bank.bottom
        button.anchors.horizontalCenter: textbox.horizontalCenter
        button.z: 1
        button.radius: 20
        button.border.width: 3
        button.border.color: "black"
        property int step: 0

        Button
        {
            id: no
            text: "no"
            visible: false
            anchors.bottom: dialog.bottom
            anchors.right: dialog.button.left
            onClicked:
            {
                dialog.textbox.textstring = "How much do you wanna\nspend today?"
                dialog.button.visible = false
                visible = false
                bankinputbg.visible = true
            }
        }

        button.onButtonClicked:
        {
            if(step === 0)
            {
                if(settings_global.bankroll > 0)
                {
                    dialog.textbox.textstring = "You still got some money left\nWanna use that up first?"
                    button.buttonText.text = "Yes!"
                    no.visible = true

                }
                else
                {
                    dialog.textbox.textstring = "How much do you wanna\nspend today?"
                    button.visible = false
                    bankinputbg.visible = true
                }

            }
            if(step === 1)
            {
                game.setBankroll(settings_global.bankroll)
                dialog.visible = false
            }
            step++

        }
    }


    Rectangle
    {
        id:bigwrapper
        anchors.fill:parent
        color: "blue"

        function appendPlayerModel( i)
        {
            var r = game.getPlayerCardAt(i).GetRank()
            var s = game.getPlayerCardAt(i).GetSuit()
            var address = "cardimg/" + (s*13 + r) + ".png"
            playerhand.append({clr: "red",
                                  prank: r,
                                  psuit: s,
                              img: address});
        }
        function appendDealerModel( i)
        {
            var r = game.getDealerCardAt(i).GetRank()
            var s = game.getDealerCardAt(i).GetSuit()
            var address = "cardimg/" + (s*13 + r) + ".png"
            dealerhand.append({clr: "red",
                                  drank: r,
                                  dsuit: s,
                              img: address});
        }


        ListModel
        {
            id: playerhand

        }


        Rectangle
        {
            id:playerbg
            width: bigwrapper.width
            height: bigwrapper.width/7
            color: "green"
            anchors.bottom: buttonbar.top

            anchors.horizontalCenterOffset: -200
            ListView
            {
                id: playerview
                anchors.right: playerbg.right
                anchors.top: playerbg.top
                anchors.bottom: playerbg.bottom
                anchors.left: playerbg.horizontalCenter

                model: playerhand
                orientation: Qt.Horizontal
                layoutDirection: Qt.LeftToRight

                delegate: playerhandDelegate
                spacing: -height*5/14

            }
            Rectangle
            {
                id: playerbank
                anchors.rightMargin: 15
                anchors.right: playerview.left
                anchors.left: playerbg.left
                anchors.top: playerbg.top
                anchors.bottom: playerbg.bottom


                TextInput
                {
                    id: inputwager
                    height: playerbank.height/3
                    anchors.top: playerbank.top
                    anchors.left: playerbank.left
                    anchors.right: playerbank.right
                    font.pixelSize: 70

                }
            }
        }
        ListModel
        {
            id: dealerhand

        }
        Rectangle
        {
            id:dealerbg
            width: bigwrapper.width
            height: bigwrapper.width/7
            color: "green"
            anchors.top: bigwrapper.top
            ListView
            {
                id: dealerview
                anchors.fill: dealerbg
                model: dealerhand
                orientation: Qt.Horizontal
                layoutDirection: Qt.LeftToRight

                delegate: dealerhandDelegate
                spacing: -height*5/14

            }

        }
        Component
        {
            id:dealerhandDelegate
            Card{
                property int cardcount
                height: playerview.height
                width: playerview.height*5/7
                color: clr


                rank: drank
                suit: dsuit
                imgsrc: img

                MouseArea
                {
                    property bool hoverd: false
                    hoverEnabled: true
                    anchors.fill: parent
                    onPressed: console.log(rank + " " + suit)

                }
            }
        }

        Component
        {
            id:playerhandDelegate

            Card{

                height: playerview.height
                width: playerview.height*5/7



                color: clr
                rank: prank
                suit: psuit
                imgsrc: img



                MouseArea
                {
                    property bool hoverd: false
                    hoverEnabled: true
                    anchors.fill: parent
                    onPressed: console.log(rank + " " + suit)
                    onHoveredChanged:
                    {
                        if(hoverd)
                        {
                            parent.y = parent.y+20
                            hoverd = !hoverd
                        }
                        else
                        {
                            parent.y = parent.y-20
                            hoverd = !hoverd
                        }
                    }
                }
            }

        }

        Rectangle
        {
            id:buttonbar
            width: parent.width
            height: parent.height/12

            color: "black"

            anchors.bottom: parent.bottom

            Button
            {
                id: dealbutton
                text: "Deal"
                anchors.centerIn: buttonbar

                onClicked:
                {




                    bigwrapper.appendPlayerModel(0)
                    bigwrapper.appendPlayerModel(1)
                    bigwrapper.appendDealerModel(0)
                    bigwrapper.appendDealerModel(1)
                    dealbutton.visible = false
                    hitButton.visible = true
                    stayButton.visible = true
                    console.log(game.getBankroll())
                    inputwager.text = game.getBankroll()

                }



            }
            Button
            {
                id: hitButton
                text: "Hit"
                anchors.left: dealbutton.right
                anchors.leftMargin: 30
                anchors.verticalCenter: buttonbar.verticalCenter
                visible: false
                property bool bust: false
                property bool twentyone: false

                onClicked:
                {

                    game.HitPlayer()
                    bigwrapper.appendPlayerModel(game.getPlayerCardCount()-1)
                    bust = game.CheckBust()
                    twentyone = game.Check21()

                }
                onBustChanged:
                {
                    if(bust == true)
                    {
                        console.log("lose")
                        hitButton.visible = false
                        stayButton.visible = false
                    }
                }
                onTwentyoneChanged:
                {
                    if(twentyone === true)
                    {
                        console.log("21!")
                        hitButton.visible = false
                        stayButton.visible = false
                    }


                }
            }
            Button
            {
                id: stayButton
                text: "Stay"
                anchors.right: dealbutton.left
                anchors.rightMargin: 30
                anchors.verticalCenter: buttonbar.verticalCenter
                visible: false
                property bool dealerbust
                onClicked:
                {
                    hitButton.visible = false
                    stayButton.visible = false
                    dealerbust = game.DealerHand()

                    dealerhand.clear()
                    for(var i = 0; i < game.getDealerCardCount(); i++)
                    {
                        bigwrapper.appendDealerModel(i)
                    }
                    if(dealerbust == false && game.getDealerTotal() > game.getPlayerTotal())
                    {
                        console.log("Dealer wins")
                    }
                    else if(game.getDealerTotal() === game.getPlayerTotal())
                    {
                        console.log("Tie!")
                    }
                    else
                    {
                        console.log("You win!")
                    }
                }

            }
        }

    }

    menuBar: MenuBar {
    id: menubar
        Menu
        {
            title: qsTr("File")
            MenuItem
            {
                text: qsTr("New Game")
                onTriggered:
                {
                    game.dealIn();
                }
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();

            }
        }
    }

}
