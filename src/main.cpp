#include "main.h"

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    pinMode(13, OUTPUT);

    // set the initial state
    stateMachine.transition(IDLE);

    // define states and transitions
    stateMachine.when(IDLE, (EvtAction)idle, PENDING, STATE_FAILED, 5000);
    stateMachine.when(PENDING, (EvtAction)pending, IN_PROGRESS);
    stateMachine.when(IN_PROGRESS, (EvtAction)inProgress, IDLE, STATE_FAILED, 2000);
    stateMachine.whenInterrupted(IDLE, PENDING);

    // register the listener
    mgr.addListener(&stateMachine);

    pinMode(2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(2), wakeUp, FALLING);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    mgr.addListener(&startBlinkListener);
    // mgr.addListener(&stopBlinkListener);
    // mgr.addListener(&blinkListener);

    // stopBlinkListener.disable();
    // blinkListener.disable();

    Serial.println(F("Setup complete, continuing..."));
}

void loop()
{
    mgr.loopIteration();
}

bool startBlinking()
{
    // blinkListener.enable();
    mgr.reset();
    mgr.addListener(&blinkListener);
    mgr.addListener(&stopBlinkListener);
    return true;
}

bool stopBlinking()
{
    // stopBlinkListener.disable();
    mgr.reset();
    mgr.addListener(&stopBlinkListener);
    return true;
}

bool blink()
{
    bool currentState = digitalRead(BLINK_PIN);
    digitalWrite(BLINK_PIN, !currentState);
    return true;
}

void wakeUp()
{
    stateMachine.onInterrupt();
}

bool idle()
{
    Serial.println(F("Idling..."));
    digitalWrite(13, LOW);
    return true;
}

bool pending()
{
    Serial.println(F("Pending..."));
    return true;
}

bool inProgress()
{
    Serial.println(F("In progress..."));
    digitalWrite(13, HIGH);
    return true;
}