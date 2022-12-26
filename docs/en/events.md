# Events

CLEO Redux 1.0.6 adds initial support for event-driven scripting. This feature allows you to write scripts that react to events that happen in the game.

- [Listening to events](#listening-to-events)
- [List of events](#list-of-events)
  - [OnVehicleCreate](#onvehiclecreate)
  - [OnPedCreate](#onpedcreate)
  - [OnObjectCreate](#onobjectcreate)
  - [OnVehicleDelete](#onvehicledelete)
  - [OnPedDelete](#onpeddelete)
  - [OnObjectDelete](#onobjectdelete)
- [Creating your own events](#creating-your-own-events)

## Listening to events

A globally available `addEventListener` function creates a new event listener. It takes two arguments: a [predefined event name](#list-of-events) and a function that will be called when the event is triggered (a callback). The callback receives an argument that is an object with a particular structure depending on the event.

> Event listeners only work in [async context](./async.md). Scripts willing to react to game events must not use a blocking `wait` function. Use `asyncWait` instead.

```js
addEventListener("OnVehicleCreate", (event) => {
  log("A vehicle is created!");
});
```

`addEventListener` returns a function that can be used to stop listening to the event. This is useful when you want to stop listening to the event after a certain condition is met.

```js
const cancel = addEventListener("OnVehicleCreate", (event) => {
  log("A vehicle is created!");
});

// ...

cancel(); // the event callback won't be called anymore
```

## List of events

> The following documentation describes the Events.cleo plugin shipped with CLEO Redux 1.0.6+. Other plugins may add their own events.
> Events are game- and version- specific. Some of them might not be available on certain games or versions.

### OnVehicleCreate

Triggered after the game creates a new vehicle of any type in the world. An event's `data` object contains the address of the vehicle structure.

Supported in: `re3`, `reVC`, `GTA III`, `GTA VC`, `GTA SA`, `GTA III: DE (1.0.8.11827)`, `GTA VC: DE (1.0.8.11827)`, `GTA SA: DE (1.0.8.11827)`

```ts
interface OnVehicleCreateEvent {
  name: string;
  data: {
      address: int;
  }
}

addEventListener("OnVehicleCreate", (event: OnVehicleCreateEvent) => {
  const name = event.name;
  log(`Event ${name} is triggered!`}); // logs "Event OnVehicleCreate is triggered!"

  const address = event.data.address;
  log("A vehicle is created! Its address is " + address); // logs "A vehicle is created! Its address is 0x12345678"
});
```

### OnPedCreate

Triggered after the game creates a new ped of any type in the world. An event's `data` object contains the address of the ped structure.

Supported in: `re3`, `reVC`, `GTA III`, `GTA VC`, `GTA SA`, `GTA III: DE (1.0.8.11827)`, `GTA VC: DE (1.0.8.11827)`, `GTA SA: DE (1.0.8.11827)`

```ts
interface OnPedCreateEvent {
  name: string;
  data: {
    address: int;
  };
}

addEventListener("OnPedCreate", (event: OnPedCreateEvent) => {
  const name = event.name;
  log(`Event ${name} is triggered!`); // logs "Event OnPedCreate is triggered!"

  const address = event.data.address;
  log("A ped is created! Its address is " + address); // logs "A ped is created! Its address is 0x12345678"
});
```

### OnObjectCreate

Triggered after the game creates a new object of any type in the world. An event's `data` object contains the address of the object structure.

Supported in: `re3`, `reVC`, `GTA III`, `GTA VC`, `GTA SA`, `GTA III: DE (1.0.8.11827)`, `GTA VC: DE (1.0.8.11827)`, `GTA SA: DE (1.0.8.11827)`

```ts
interface OnObjectCreateEvent {
  name: string;
  data: {
    address: int;
  };
}

addEventListener("OnObjectCreate", (event: OnObjectCreateEvent) => {
  const name = event.name;
  log(`Event ${name} is triggered!`); // logs "Event OnObjectCreate is triggered!"

  const address = event.data.address;
  log("An object is created! Its address is " + address); // logs "An object is created! Its address is 0x12345678"
});
```

### OnVehicleDelete

Triggered _before_ the game deletes a vehicle from the world. An event's `data` object contains the address of the vehicle structure.

Supported in: `re3`, `reVC`, `GTA III`, `GTA VC`, `GTA SA`, `GTA III: DE (1.0.8.11827)`, `GTA VC: DE (1.0.8.11827)`, `GTA SA: DE (1.0.8.11827)`

```ts
interface OnVehicleDeleteEvent {
  name: string;
  data: {
    address: int;
  };
}

addEventListener("OnVehicleDelete", (event: OnVehicleDeleteEvent) => {
  const name = event.name;
  log(`Event ${name} is triggered!`); // logs "Event OnVehicleDelete is triggered!"

  const address = event.data.address;
  log("A vehicle is about to be deleted! Its address is " + address); // logs "A vehicle is about to be deleted! Its address is 0x12345678"
});
```

### OnPedDelete

Triggered _before_ the game deletes a ped from the world. An event's `data` object contains the address of the ped structure.

Supported in: `re3`, `reVC`, `GTA III`, `GTA VC`, `GTA SA`, `GTA III: DE (1.0.8.11827)`, `GTA VC: DE (1.0.8.11827)`, `GTA SA: DE (1.0.8.11827)`

```ts
interface OnPedDeleteEvent {
  name: string;
  data: {
    address: int;
  };
}

addEventListener("OnPedDelete", (event: OnPedDeleteEvent) => {
  const name = event.name;
  log(`Event ${name} is triggered!`); // logs "Event OnPedDelete is triggered!"

  const address = event.data.address;
  log("A ped is about to be deleted! Its address is " + address); // logs "A ped is about to be deleted! Its address is 0x12345678"
});
```

### OnObjectDelete

Triggered _before_ the game deletes an object from the world. An event's `data` object contains the address of the object structure.

Supported in: `re3`, `reVC`, `GTA III`, `GTA VC`, `GTA SA`, `GTA III: DE (1.0.8.11827)`, `GTA VC: DE (1.0.8.11827)`, `GTA SA: DE (1.0.8.11827)`

```ts
interface OnObjectDeleteEvent {
  name: string;
  data: {
    address: int;
  };
}

addEventListener("OnObjectDelete", (event: OnObjectDeleteEvent) => {
  const name = event.name;
  log(`Event ${name} is triggered!`); // logs "Event OnObjectDelete is triggered!"

  const address = event.data.address;
  log("An object is about to be deleted! Its address is " + address); // logs "An object is about to be deleted! Its address is 0x12345678"
});
```

## Creating your own events

[CLEO Redux SDK](./using-sdk.md) provides a method called `TriggerEvent` that can be used to emit a new event along with some payload. The plugin must decide when the event should be triggered (usually by hooking into a game function). See the [Events.cleo](https://github.com/cleolibrary/CLEO-Redux/tree/master/plugins/Events) plugin source code for an example.

`TriggerEvent` has two parameters: an event name and a serialized JSON. It will be passed to the event listeners as the `data` property of the event object.
