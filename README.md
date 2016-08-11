#PubNub Arduino Library

This library allows your sketches to communicate with the PubNub cloud message passing system using your board from Particlio.io. Your application can receive and send messages.

##Getting Started with Particle and PubNub Tutorial: https://www.pubnub.com/blog/2016-07-12-getting-started-with-pubnub-and-particle-devices/

##Copy-and-Paste-Ready Code!
See how easy it is to [Publish](examples/PubNubPublisher) and [Subscribe](examples/PubNubSubscriber)!

###Synopsis


	void setup() {
		Serial.begin(9600);
		Ethernet.begin(mac);
		PubNub.begin(pubkey, subkey);
	}

	void loop() {
		/* Maintain DHCP lease. */
		Ethernet.maintain();

		/* Publish message. */
		EthernetClient *pclient = PubNub.publish(pubchannel, "\"message\"");
		if (pclient)
			pclient->stop();

		/* Wait for news. */
		PubSubClient *sclient = PubNub.subscribe(subchannel);
		if (!sclient) return; // error
		char buffer[64]; size_t buflen = 0;
		while (sclient->wait_for_data()) {
			buffer[buflen++] = sclient->read();
		}
		buffer[buflen] = 0;
		sclient->stop();

		/* Print received message. You will want to look at it from
		 * your code instead. */
		Serial.println(buffer);
		delay(10000);
	}

##Library Reference

``bool PubNub.begin(char *publish_key, char *subscribe_key, char *origin)``

To start using PubNub, use PubNub.begin().  This should be called after
Ethernet.begin().

Note that the string parameters are not copied; do not overwrite or free the
memory where you stored the keys! (If you are passing string literals, don't
worry about it.) Note that you should run only one of publish, subscribe and
history requests each at once.

The origin parameter is optional, defaulting to "pubsub.pubnub.com".

``TCPClient *publish(char *channel, char *message, int timeout)``

Send a message (assumed to be well-formed JSON) to a given channel.

Returns NULL in case of error, instead an instance of EthernetClient
that you can use to read the reply to the publish command. If you
don't care about it, call ``client->stop()`` right away.

The timeout parameter is optional, defaulting to 305. See also
a note about timeouts below.

``PubSubClient *subscribe(char *channel)``

Listen for a message on a given channel. The function will block
and return when a message arrives. NULL is returned in case of error.
The return type is PubSubClient, but from user perspective, you can
work with it exactly like with EthernetClient; it also provides
an extra convenience method ``wait_for_data()`` that allows you
to wait for more data with sensible timeout.

Typically, you will run this function from loop() function to keep
listening for messages indefinitely.

As a reply, you will get a JSON array with messages, e.g.:

```
	["msg1",{msg2:"x"}]
```

and so on. Empty reply [] is also normal and your code must be
able to handle that. Note that the reply specifically does not
include the time token present in the raw reply from PubNub;
no need to worry about that.


Receive list of the last messages published on the given channel.
The limit argument is optional and defaults to 10.

The timeout parameter is optional, defaulting to 305. See also
a note about timeouts below.

##Installation

Upload the library to Particle Build and include it in your 
sketch to get started!
Try out the examples!


