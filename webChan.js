
new QWebChannel(qt.webChannelTransport, function(channel) {

    console.log("EEEEE");

    var testObj = channel.objects.testObj;
    testObj.fire();

    /*
    // Connect to a signal:
    channel.objects.foo.mySignal.connect(function() {
        // This callback will be invoked whenever the signal is emitted on the C++/QML side.
        console.log(arguments);
    });

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
