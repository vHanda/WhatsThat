
new QWebChannel(qt.webChannelTransport, function(channel) {
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

    onLoad(whatsAppInterface.emitLoaded, whatsAppInterface.emitAuthRequired);

    whatsAppInterface.sendMessage.connect(function(msg){
        setMessage(msg);
        whatsAppInterface.keyboardEventInjected.connect(function(){
            clickSend();
        });
        whatsAppInterface.jsInjectKeyboardEvent();
    });
});


function setMessage(message) {
    var input = $(".input-container > .input");
    input.append(message);
}

function clickSend() {
    var sendButton = $("button.icon.btn-icon.icon-send.send-container");
    if (sendButton.length == 0) {
        setTimeout(clickSend, 100);
        return;
    }
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

function currentActiveChat() {
    return $(".chat.active").attr("data-reactid");
}

function selectChat(chatId) {
    if (currentActiveChat() == chatId) {
        return;
    }
    var chat = $("[data-reactid='" + chatId + "']");
    chat.click();
}

//
// Loading
//

function onLoad(callBack, authCallBack){
    var app = $(".app-wrapper");
    app.on("DOMNodeInserted", function() {
        var main = $(".app-wrapper-main");
        if (main.length > 0) {
            var centralImage = $("div.intro-image");
            if (centralImage.length > 0) {
                callBack();
            }
            return;
        }

        var loadingSpinner = $("#startup > .spinner-container");
        if (loadingSpinner.length > 0) {
            // FIXME: This is just for loading
            return;
        }

        var qrcode = $("div.qrcode");
        if (qrcode.length > 0) {
            var img = $("img", qrcode);
            if (img.length) {
                var src = img.attr("src");
                if (src && src.length) {
                    authCallBack(src);
                } else {
                    setTimeout(function() {
                        var src = img.attr("src");
                        if (src && src.length) {
                            authCallBack(src);
                            return;
                        }
                        // FIXME: what now?
                    }, 100);
                }
                return;
            }

            return;
        }

        // FIXME: Call a seperate callback if failed to load
        var popupError = $(".popup-container");
        if (popupError.length > 0) {
            return;
        }

        return;
    });

    // app-wrapper app-wrapper-main

    // Monitor app-wraper
    // contains "#startup"
}
