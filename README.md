# Project GT

I don't want to spoil what this project will be, but for the time being it's a learning sandbox to build up my knowledge around MicroController architecture on an enterprise level.

This means Continuous Integration/Deployment over OTA, and a whole host of of features such as multi-tasking and modular devices.

More on all of this later!

# Work In Progress

This is a giant work in progress, and I'm a bit rusty on a LOT of things, so bare with me!

I WILL be growing this documentation, sorry it's so bare right now!

You can find me Working In Public on Twitch and Youtube: https://twitch.tv/CodexHere

This started as PlatformIO in the similar vein (as in, devcontainers, etc), but I found it really disappointing that [PIO doesn't support ESPIDF Components](https://github.com/platformio/platform-espressif32/issues/453#issuecomment-1814823010) out of the box, and doesn't sound like they plan to. There are [workarounds](https://docs.platformio.org/en/latest/frameworks/espidf.html#esp-idf-components), but in my opinion they're more work than they're worth, and it practically takes the value of PIO completely away for me.

However, I've ported the environment and project to native ESP-IDF, which so far is working out fine. In this setup IDF is preinstalled into the image (customizable with build args), as well as all dependencies needed to build and deploy your projects.

### Current State

Currently, a simple app starts a Task responsible for cycling an [onboard] RGB LED through GPIO via RMT. The component used is the LED Strip Component by Espressif from the Component Registry. The trick I learned with this setup is how the app starts up (slightly different than freeRTOS docs indicate), and working with the pointer logic for parameters passed into tasks and queues.

I've added a common `includes` path to be accessible throughout the project.

There's a new `KILL_LOGGING` build parameter you can add that will disable logging throughout my code.

I've also spit the code into "private" Components so they are separated and the logic is cleaner.

## Docker

A fully functioning Docker Image and Compose file is supplied, but the initial intent is to use it as a DevContainer within VSCode.

Of course, you can use the image in CI/CD as well, or explicitly by hand via CLI should you want to cheat and use it as if it were local (note, this likely will not work with tooling other than shell scripts or CLI access).

(FIXME: Add alias command as example, and expand on how to use compose, binds, volumes, etc)

## VSCode

On a fresh install of VSCode and Docker, you should be able to open the folder in VSCode and you'll either be prompted to reopen in the container, or you can [manually open in the DevContainer](https://code.visualstudio.com/docs/devcontainers/containers#_quick-start-open-an-existing-folder-in-a-container).

With a simple click, you can have the entire dev environment setup and ready to flash and monitor in however long it takes to build the image on your system (typically just a few minutes)! You don't have to worry about having the right python, virtual environments, GCC/cmake/etc dependencies or anything, just Docker and VSCode!
