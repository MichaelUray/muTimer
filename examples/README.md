# Documentation for muTimer Examples

This document provides an overview of the example sketches included in the `muTimer` library. These examples demonstrate various use cases for non-blocking timer functionality in Arduino projects, ranging from simple LED control to advanced serial communication and timer resets.

---

## Example: `ButtonAndLedBlinkingCycleOnOff.ino`

**Description:**
This sketch demonstrates how to use the `cycleOnOff` function to make an LED blink when a button is pressed. The LED toggles on and off in a timed cycle as long as the button remains pressed.

**Key Features:**
- Utilizes the `cycleOnOff` function for timed LED control.
- Starts and stops the blinking based on button input.
- Demonstrates how to create a simple user interface using a button and LED.

---

## Example: `ButtonAndLedBlinkingDelayOnOff.ino`

**Description:**
This example shows how to use the `delayOnOff` function to control an LED. When a button is pressed, the LED turns on after a specified delay and turns off after another delay.

**Key Features:**
- Implements separate delays for turning the LED on and off.
- Uses button input to demonstrate non-blocking delay functionality.
- Suitable for projects requiring precise timing for user interactions.

---

## Example: `ButtonDebounceDelayOnOffAndLedFlashingCycleOnOff.ino`

**Description:**
This sketch combines button debouncing with timer functionality. It uses `delayOnOff` for LED control and `cycleOnOff` to make the LED flash while a button is pressed.

**Key Features:**
- Integrates debouncing to prevent false triggers from the button.
- Demonstrates advanced timer functionality with multiple modes of operation.
- Suitable for projects with complex button and LED interactions.

---

## Example: `ButtonDelayOnOffSwitchesLed.ino`

**Description:**
This example demonstrates how to use `delayOnOff` to switch an LED on and off based on button input, with configurable delays for both states.

**Key Features:**
- Allows customization of both on and off delay durations.
- Simplifies implementation of delayed actions in response to user input.
- Ideal for beginners learning to work with timers and inputs.

---

## Example: `LedBlinkingCycleOnOffTrigger.ino`

**Description:**
This sketch uses the `cycleOnOff` function to create a triggered LED blinking pattern. The blinking starts and stops based on specific conditions.

**Key Features:**
- Demonstrates conditional triggering of the `cycleOnOff` function.
- Useful for projects requiring visual feedback triggered by external events.
- Easy to adapt for other outputs beyond LEDs.

---

## Example: `SerialCycleTrigger.ino`

**Description:**
This example shows how to use the `cycleOnOff` function with serial input to create a cyclic pattern. It demonstrates how to start and stop a timer-controlled operation using serial commands.

**Key Features:**
- Integrates serial communication with timer functionality.
- Enables dynamic control of cycles via serial commands.
- Suitable for projects with remote control or debugging needs.

---

## Example: `SerialDelayOn.ino`

**Description:**
This sketch demonstrates the use of the `delayOn` function with serial input. It turns on an LED after a delay when triggered via serial input.

**Key Features:**
- Highlights the `delayOn` function for delayed activation.
- Shows how to trigger actions programmatically via serial communication.
- Ideal for testing or automation scenarios.

---

## Example: `SerialDelayOnTrigger.ino`

**Description:**
This example shows how to trigger a delayed operation using serial commands. It uses the `delayOn` function to control an LED based on serial input.

**Key Features:**
- Combines serial input with timer functionality for precise control.
- Demonstrates the flexibility of the `delayOn` function.
- Suitable for real-time applications requiring controlled delays.

---

## Example: `SerialDelayOnTriggerRepeatWithReset.ino`

**Description:**
This sketch extends the functionality of `SerialDelayOnTrigger` by adding a reset feature. The delay can be restarted or interrupted using serial commands.

**Key Features:**
- Implements reset functionality for ongoing timers.
- Useful for iterative testing and real-time adjustments.
- Demonstrates advanced control of delayed operations.

---

## Example: `SerialDelayOnTriggerResetIsRunning.ino`

**Description:**
This example includes a feature to check if a timer is currently running. It uses `delayOn` to implement delayed triggering with a reset functionality.

**Key Features:**
- Adds status checking to determine timer activity.
- Enhances control over timer-based operations.
- Ideal for debugging or managing multiple timers.

---

## Example: `SerialMsecOverflowSafeTest.ino`

**Description:**
This sketch tests the timer's behavior in case of millisecond overflow. It ensures that the library handles timer overflows correctly, maintaining accurate timing.

**Key Features:**
- Verifies the library's reliability over extended run times.
- Highlights the robustness of `muTimer` in handling edge cases.
- Useful for validating the timer's suitability for long-term projects.

---
