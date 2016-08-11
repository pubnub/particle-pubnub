/*
  PubNub sample client

  This sample client will use just the minimal-footprint raw PubNub
  interface where it is your responsibility to deal with the JSON encoding.

  It will just send a hello world message and retrieve one back, reporting
  its deeds on serial console.

  This code is in the public domain.
  */

#include <PubNub.h>


char pubkey[] = "demo";
char subkey[] = "demo";
char channel[] = "hello_world";

void setup()
{

	Serial.begin(9600);
	Serial.println("Serial set up");

	PubNub.begin(pubkey, subkey);
	Serial.println("PubNub set up");
}

void loop()
{

	TCPClient *client;

	Serial.println("publishing a message");
	client = PubNub.publish(channel, "\"\\\"Hello world!\\\" she said.\"");
	if (!client) {
		Serial.println("publishing error");
		delay(1000);
		return;
	}
	while (client->connected()) {
		while (client->connected() && !client->available()) ; // wait
		char c = client->read();
		Serial.print(c);
	}
	client->stop();
	Serial.println();

	Serial.println("waiting for a message (subscribe)");
	TCPClient *pclient = PubNub.subscribe(channel);
	if (!pclient) {
		Serial.println("subscription error");
		delay(1000);
		return;
	}
	while (pclient->wait_for_data()) {
		char c = pclient->read();
		Serial.print(c);
	}
	pclient->stop();
	Serial.println();

	Serial.println("retrieving message history");
	client = PubNub.history(channel);
	if (!client) {
		Serial.println("history error");
		delay(1000);
		return;
	}
	while (client->connected()) {
		while (client->connected() && !client->available()) ; // wait
		char c = client->read();
		Serial.print(c);
	}
	client->stop();
	Serial.println();

	delay(10000);
}
