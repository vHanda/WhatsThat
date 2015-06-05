
new QWebChannel(qt.webChannelTransport, function(channel) {

    console.log("EEEEE");

    var whatsAppInterface = channel.objects.whatsAppInterface;

    whatsAppInterface.showContactListInvoked.connect(function() {
        showContactList(whatsAppInterface.showContactListCallback);
    });

    whatsAppInterface.hideContactListInvoked.connect(function() {
        showContactList(whatsAppInterface.hideContactListCallback);
    });

    whatsAppInterface.populateChatList.connect(function() {
        var chats = activeChats();
        whatsAppInterface.chatList = chats;
    });

    whatsAppInterface.currentChatChanged.connect(function() {
        selectChat(whatsAppInterface.currentChat)
    });

    whatsAppInterface.populateMessageList.connect(function() {
        var msgs = fetchMessages();
        whatsAppInterface.messageList = msgs;
    });

    /*
    // To make the object known globally, assign it to the window object, i.e.:
    window.foo = channel.objects.foo;

    // Invoke a method:
    foo.myMethod(arg1, arg2, function(returnValue) {
        // This callback will be invoked when myMethod has a return value. Keep in mind that
        // the communication is asynchronous, hence the need for this callback.
        console.log(returnValue);
    });

    // Read a property value, which is cached on the client side:
    console.log(foo.myProperty);

    // Writing a property will instantly update the client side cache.
    // The remote end will be notified about the change asynchronously
    foo.myProperty = "Hello World!";

    // To get notified about remote property changes,
    // simply connect to the corresponding notify signal:
    foo.onMyPropertyChanged.connect(function(newValue) {
        console.log(newValue);
    });

    // One can also access enums that are marked with Q_ENUM:
    console.log(foo.MyEnum.MyEnumerator);
    */
});


// FIXME: Does not work!
function sendMessage(message) {
    // We need to simulate the input, and not just set the text!
    var input = $(".input-container > .input");
    input.textContent = message;

    // This send button does not exist, as it only appears on a keyboard event
    // on the input box
    var sendButton = $("button.icon.btn-icon.icon-send.send-container");
    sendButton.click();
}

function contactList() {
    var names = [];
    var nameElements = $(".chat > .chat-body > .chat-main > .chat-title");
    for (var i = 0; i < nameElements.length; i++) {
        var elem = nameElements[i];
        var name = elem.getAttribute("title");
        if (name)
            names.push(name);
    }

    return names;
}

function showContactList(callBack) {
    var button = $("button.icon.icon-chat");
    button.click();

    var leftDrawer = $("body > div > div.app.two > div:nth-child(2) > span:nth-child(1)").first();
    // Better CSS selector: div.app.two > div[data-reactid] > span[data-reactid*='1.1']
    leftDrawer.on("DOMNodeInsert", callBack);
}

function hideContactList(callBack) {
    var button = $("button.icon.btn-close-drawer");
    button.click();

    var leftDrawer = $("body > div > div.app.two > div:nth-child(2) > span:nth-child(1)").first();
    leftDrawer.on("DOMNodeRemoved", callBack);
}

//
// Messages
//

function fetchMessages() {
    var messages = [];
    var msgElemens = $(".msg");

    var re = new RegExp("\\[([^,]*), (.*)\\]([^:]*):(.*)");
    for (var i = 0; i < msgElemens.length; i++) {
        var msgElem = msgElemens[i];

        var mtext = $("div.message-text", msgElem).text();
        if (mtext) {
            var match = re.exec(mtext);

            if (!match) {
                console.log(match);
                continue;
            }
            var message = {};
            message.date = match[1];
            message.time = match[2];
            message.author = match[3];
            message.text = match[4];

            messages.push(message);
        }
    }

    return messages;
}


//
// Active Chats
//
function activeChats() {
    var chats = [];

    var chatElems = $(".chat");
    for (var i = 0; i < chatElems.length; i++) {
        var chatElem = chatElems[i];

        var chatObj = {};
        chatObj.title = $("div.chat-title", chatElem).text();
        chatObj.id = chatElem.getAttribute("data-reactid");

        var imgElem = $("img.avatar-image", chatElem);
        if (imgElem.length)
            chatObj.avatar = imgElem.attr("src");

        chats.push(chatObj);
    }

    return chats;
}

function selectChat(chatId) {
    var chat = $("[data-reactid='" + chatId + "']");
    chat.click();
}


