#include <Eventually.h>
#include <EventuallyStateMachine.h>
#include <EventuallyCommand.h>

#include <Arduino.h>

const byte IDLE = 0;
const byte PENDING = 1;
const byte IN_PROGRESS = 2;

const byte BUTTON_PIN = 3;
const byte BLINK_PIN = 4;

bool startBlinking();
bool stopBlinking();
bool blink();

EvtManager mgr;
EvtStateMachineListener stateMachine;
EvtPinListener startBlinkListener(BUTTON_PIN, (EvtAction)startBlinking);
EvtPinListener stopBlinkListener(BUTTON_PIN, (EvtAction)stopBlinking);
EvtTimeListener blinkListener(500, true, (EvtAction)blink);

void wakeUp();
bool idle();
bool pending();
bool inProgress();