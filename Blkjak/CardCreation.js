var component;

function createCardObject()
{
    component = Qt.createComponent("Card.qml")
    if (component.status === Component.Ready || component.status === Component.Error)
        finishCreation();
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation()
{
    if (component.status === Component.Ready)
    {
        var card = component.createObject(bigwrapper,
                                           {
                                               width: window.width/7 ,
                                               height: window.width/5
                                           });

        if (card === null)
            console.log("Error creating card");
    }
    else if (component.status === Component.Error)
        console.log("Error loading component:", component.errorString());
    return card;
}
