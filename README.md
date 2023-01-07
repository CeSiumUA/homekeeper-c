# homekeeper

This peoject is created in order to get notifications about electricity/internet outage on the home server. `homekeeper-client` - app that runs on home server (named client), `homekeeper-relay` - app that runs on the remote server (as for instance, cloud or VPS).
Client periodically sends requests on the relay, while relay accepts requests, and updates `last_online` field for client record. If the client was last online more than 2 minutes ago, the notification is sent in Telegram via bot.


For security reason, the client-relay communication is conducted with ed25519 signature, which is verified on the relay side. The ed25519 implementations are stored in folders `ed_crypto`, and are taken from: [this repo](https://github.com/orlp/ed25519).

## Building and configuring

#### Building relay

Relay depends on [telebot](https://github.com/smartnode/telebot), building instructions could be found in that repository.
After building `telebot`, please also run:
```
$ make install
```

and

```
$ sudo ldconfig
```

Afterwards, turn back to this repo folder
```
$ cd homekeeper-relay/
$ make
```

Also, telegram chat id and bot token should be provided via environment variables TL_CHAT and TL_TOKEN respectively, or via file .TL_CHAT and .TL_TOKEN

#### Building client

```
$ cd homekeeper-client/
$ make
```

Then, you should generate a "server file", in order to put it on the relay.
Run:
```
$ homekeeper-client -g
```

It will prompt a client id, just use some unique numeric identifier

Than, copy generated file (name is the same as entered client id) to the relay in `$HOME/.homekeeper-relay/records/`
Client program is supposed to run with `crontab`, because it sends request only once.