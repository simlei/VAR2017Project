# Why we need a microcontroller

At the start of the project, I spent a week looking at existing papers and projects
with goals similar to ours: to be able to tell what the hand of the guitar player
is doing, i. e. which combination of finger positions is in effect. Because we already
watch the player through a webcam, the computer vision approach seems like a natural
choice, there is indeed work on how to tell the finger position by analyzing a video feed. [???]

[??? why not CV]



# Building the electronically augmented guitar

The plan is to modify a usual guitar so that the attached computer
(and thus, the frontend application) knows instantly which string is pressed down at
which fret.

How to do it? The guitar strings on western guitars and on electric guitars are usually
metallic and conduct electricity. That enables us to think about a guitar string
touching a fret as a switch. If a guitar string is pressed down, a circuit is closed. A microcontroller can read the switch configuration and transfer it to the application.

Unfortunately, there is a bit of difficulty here. If we just attach a microchip to a string, we can only tell by a logical "1" that this string had contact with a fret, but we don't have the information which fret it is. Thus, we need to be a little bit clever about it: we read out that switch bit one-by-one for each string, and do it so fast that it is not noticeable. A fret spans all 6 strings of the guitar. If two strings have contact with the same fret, the two switched circuits are connected, so we have to make sure that the currently active string (which we want to read out at this point) is the only string conducting digital information.

This is a sketch of the proposed switch circuit:

[???]

Note, that we use a "pull-up resistor"


[OpenChord](http://www.laboratoryspokane.com/openchord/the-openchord-v1-guitar/)
already built such a guitar and sold it. The project is dead now, but the author
published instructions on how to DIY. The project was first based off an Arduino.

Since we initially had only very limited experience with the design of digital circuits and microcontrollers, we decided to keep it as simple as possible. Arduino is a platform that is well documented, has a huge community and is supposed to be very beginner-friendly. Before going for the setup with a real guitar, we can try out the circuit on a breadbord, simulating a fret contact by just pressing a switch or bringing two wires into contact.
