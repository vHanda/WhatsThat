* Select a contact
* Scrolling through any list
* Real time updates for messages

* Add a help menu with all the commands

* Block linenoise until loading finished
  -> Add some kind of "Loading ..." (with animation on the dots)
  ->

---------

Some kind of state of the interface?


Small Tasks
-----------
* Some kind of messageList API?

* Initial loading -> add some kind of signal caching
                  -> Remove the loadEvent

* Add a Message class
  - Add a Image Type
  - Add the image url in the fetchMessages functions
  - Add a VoiceNote type
  - Add VoiceType support in fetchMessages

* Conserve network usage by not loading images
  - Not currentl possible with Qt 5.5

* unread messages signal
  - Give message count
  - Give if chat is muted

BIG PROBLEMS
------------

* Sending multiple messages
* Regenerating the chat list
* Better UI - should give errors and not silently fail
* Serializing different operations
* The concept of Contacts!
