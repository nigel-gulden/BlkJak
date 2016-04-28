import QtQuick 2.0
import MyExt 1.0
Rectangle
{
    id: card

    property alias imgsrc: cardimg.source
    property alias rank: carddata.m_rank
    property alias suit: carddata.m_suit
    property alias cardC: carddata
    visible: true

    Image
    {
        id:cardimg
        anchors.fill: parent
        fillMode: Image.Stretch

    }
    CardC
    {
        id: carddata
        m_rank: -1
        m_suit: -1


    }
    function setCardC(c)
    {
        card.cardC.Copy(c)

    }

}
