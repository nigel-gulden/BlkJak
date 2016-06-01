import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Window 2.2
import QtQml.Models 2.2

//extension for c++ integration
import MyExt 1.0
import Qt.labs.settings 1.0

ApplicationWindow {

    id: window
    visible: true
    width: 1024
    height: 768

    //window title
    title: qsTr("BlkJak")

    //saves current bankroll when program exited
    onClosing:
    {
        settings_global.bankroll = game.getBankroll()
    }

    //bankroll and wager ints
    Settings
    {
        id: settings_global
        property int bankroll:0
        property int wager: 0
    }

    //input splash
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

        //box to input bankroll
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
                //once bankroll inputted, parses to int, sends to game logic
                //and saves to settings
                onAccepted:
                {
                    var money = parseInt(text)
                    settings_global.bankroll = money
                    game.setBankroll(settings_global.bankroll)
                    dialog.visible = false
                    bigwrapper.startGame()
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

        //button in splash
        Button
        {
            id: no
            text: "no"
            visible: false
            anchors.bottom: dialog.bottom
            anchors.right: dialog.button.left

            //when clicked, makes button transparent, asks how much you want to spend
            //and starts game
            onClicked:
            {
                dialog.textbox.textstring = "How much do you wanna\nspend today?"
                dialog.button.visible = false
                visible = false
                bankinputbg.visible = true
            }
        }

        //when splash button is clicked...
        button.onButtonClicked:
        {
            //if it hasn't been clicked before...
            if(step === 0)
            {
                //if there's no saved money, asks if you want to use leftover bank
                if(settings_global.bankroll > 0)
                {
                    dialog.textbox.textstring = "You still got some money left\nWanna use that up first?"
                    button.buttonText.text = "Yes!"
                    no.visible = true
                }
                //if there's no money in bank, asks how much to put in bank
                else
                {
                    dialog.textbox.textstring = "How much do you wanna\nspend today?"
                    button.visible = false
                    bankinputbg.visible = true
                }
            }

            //if it's been clicked before, set the bankroll as settings and starts game
            if(step === 1)
            {
                game.setBankroll(settings_global.bankroll)
                dialog.visible = false
                bigwrapper.startGame()
            }
            step++
        }
    }

    //game wrapper
    Rectangle
    {
        id:bigwrapper
        anchors.fill:parent
        color: "blue"

        //clears hands, makes wager button visible, and all others transparent,
        //and sets up textboxes
        function startGame()
        {
            playerhand.clear()
            dealerhand.clear()
            wagerButton.visible = true
            inputmsg.visible = true
            overDialog.visible = false
            banktotal.text = "Bank: " + game.getBankroll()
            inputwager.visible = true
            wagertotal.visible = false
        }
        function gameOver()
        {
            hitButton.visible = false
            stayButton.visible = false
            overDialog.visible = true
        }

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
            var r
            var s
            var address
            if(i === -1)
            {
                r = game.getDealerCardAt(1).GetRank()
                s = game.getDealerCardAt(1).GetSuit()
                address = "cardimg/back.png"
            }
            else
            {
                r = game.getDealerCardAt(i).GetRank()
                s = game.getDealerCardAt(i).GetSuit()
                address = "cardimg/" + (s*13 + r) + ".png"
            }
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
                    anchors.topMargin: 15
                    anchors.top: playerbank.top
                    anchors.leftMargin: 50
                    anchors.left: playerbank.horizontalCenter

                    anchors.right: playerbank.right

                    font.pixelSize: playerbank.height/3
                    visible: false
                }
                Text
                {
                    id: inputmsg
                    height: playerbank.height/3
                    anchors.top: playerbank.top
                    anchors.left: playerbank.left

                    anchors.right: playerbank.horizontalCenter
                    font.pixelSize: playerbank.height/3
                    text: "Input wager: "
                    visible: false
                }


                Text
                {
                    id: wagertotal

                    height: playerbank.height/3
                    anchors.top: playerbank.top
                    anchors.left: playerbank.left
                    anchors.right: playerbank.right
                    font.pixelSize: playerbank.height/3

                    visible: false
                }

                Text
                {
                    id: banktotal
                    height: playerbank.height/3
                    anchors.bottom: playerbank.bottom
                    anchors.left: playerbank.left
                    anchors.right: playerbank.right
                    font.pixelSize: playerbank.height/3
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
                id: wagerButton
                property int w: 0
                text: "Wager"
                anchors.centerIn: buttonbar
                visible: false
                onClicked:
                {
                    var wager = parseInt(inputwager.text)
                    settings_global.wager = wager

                    game.Wager(settings_global.wager)
                    dealbutton.visible = true
                    wagerButton.visible = false
                    inputwager.visible = false
                    inputmsg.visible = false
                    wagertotal.visible = true
                    wagertotal.text = "Wager: " + game.getPot()
                    banktotal.text = "Bank: " + game.getBankroll()
                }
            }

            Button
            {
                id: dealbutton
                text: "Deal"
                anchors.centerIn: buttonbar
                property bool twentyone: false
                visible: false
                onClicked:
                {
                    game.dealIn()
                    bigwrapper.appendPlayerModel(0)
                    bigwrapper.appendPlayerModel(1)
                    bigwrapper.appendDealerModel(0)
                    bigwrapper.appendDealerModel(-1)
                    dealbutton.visible = false
                    hitButton.visible = true
                    stayButton.visible = true

                    twentyone = game.Check21()

                    onTwentyoneChanged:
                    {
                        if(twentyone === true)
                        {
                            console.log("21!")
                            game.Win21()
                            overDialog.textbox.textstring = "Twenty one!\nplay again?"
                            bigwrapper.gameOver()
                        }
                    }

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
                        bigwrapper.gameOver()
                        overDialog.textbox.textstring = "Bust\nplay again?"
                    }
                }

                onTwentyoneChanged:
                {
                    if(twentyone === true)
                    {
                        console.log("21!")
                        game.Win()
                        overDialog.textbox.textstring = "You win!\nplay again?"
                        bigwrapper.gameOver()
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
                        overDialog.textbox.textstring = "Dealer wins\nplay again?"
                        bigwrapper.gameOver()
                    }
                    else if(game.getDealerTotal() === game.getPlayerTotal())
                    {
                        console.log("Tie!")
                        game.Tie()
                        overDialog.textbox.textstring = "Tie game\nplay again?"
                        bigwrapper.gameOver()
                    }
                    else
                    {
                        console.log("You win!")
                        game.Win()
                        overDialog.textbox.textstring = "You win!\nplay again?"
                        bigwrapper.gameOver()
                    }
                }

            }
        }

    }

    Dialog{
        id: overDialog
        color: "green"
        height: 300
        width: 500
        x: 234
        y: 262

        border.color: "black"
        border.width: 8
        radius: 20

        textbox.textcolor: "yellow"
        textbox.color: "transparent"
        textbox.textfont.pointSize: 20

        textbox.width: 500
        textbox.height: 100
        textbox.anchors.top: overDialog.top
        textbox.anchors.horizontalCenter: overDialog.horizontalCenter
        visible: false

        Rectangle
        {
            id: overButtonBar
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 100
            color: "transparent"
            Button
            {
                id: yesButton
                text: "Yes"
                anchors.leftMargin: 70
                anchors.left: parent.left
                onClicked:
                {
                    bigwrapper.startGame()
                }
            }
            Button
            {
                id: noButton
                text: "No"
                anchors.rightMargin: 70
                anchors.right: parent.right
                onClicked: Qt.quit();
            }
        }
    }

    menuBar: MenuBar
    {
    id: menubar
        Menu
        {
            title: qsTr("File")
            MenuItem
            {
                text: qsTr("New Game")
                onTriggered:
                {
                    bigwrapper.startGame()

                }
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();

            }
        }
    }

}
