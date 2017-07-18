# Tools, Problems, Solutions analysis

This page discussed the choice of tools for this project, the problems that have arisen,
and solutions / mitigations we have found.

# Tools

Openframeworks
Aruco
Arduino platform
Electronics, guitar

# Problems and their solution approaches

Minor problems have occurred all over the project, but when we were able to deal with them 100%,
we don't list them here. Quality of the teaching matrial and user experience are not a major concern since we
see this as an exploratory project for giving us a starting point for doing more work on detecting a guitar's state
electronically and making that useful to the user.

Problems that were dealt with to our satisfaction at the final project presentations were:
  - ARuCo tracking dissatisfactory
  - Virtually no prior knowledge of electronics - but built the electronic guitar setup in short of 3 weeks!
  - Modeling of chords and their variations, scales, ... that were necessary for describing "lessons" for the user to play along with the usb guitar.
  - An electric guitar has a metallic bridge which is hard to isolate against thin metallic strings that eventually rub through all kinds of insulation. We ended up using a small western acoustic guitar which also has conductive strings but a wooden bridge.
  - all sorts of small problems while building the electronic guitar. aside from the problem with it discussed below, we think it's a real nice piece of DIY Human interface device electronics! :)

## Reading out the electronic guitar state

In the process of building the guitar, we realized we had misinterpreted some claims of a similar project that gave us the original idea for the electronic guitar approach. With multiple strings pressed on frets so that they make contact with other strings, we can not read the exact on/off state of all positions within a bounding box of those connected pressed fret positions. We originally thought, an approach that "scans" the strings one by one would disable all the switchingcapabilities of strings that are not "active" (connecting to GND) at that time, but forgot we cannot disable them being conductive. Thus, all fret positions that have contact with another string through a fret form a bounding box (see below) in which we cannot be sure how many positions are actually touching a fret.


!!!image

This is a problem with the general approach. After consulting with a few knowledgeable persons we confirmed our suspicion that we can just not do better than this approach with a string-fret-switches-kind-of approach. Thus, we implemented it anyway.

Keep in mind, if you press down just one finger on the guitar, say, for playing a simple melody - we can read that out perfectly and virtually without lag! Same goes for pressing down positions that are not connected via the frets. For full-blown chord detection though, we just get probable positions inside a bounding box. In this form, we can't perfectly detect a chord but it is still useful for user input via this guitar -- selecting a certain note and giving position information of the hand of the player. This may be complementary information for a computer vision or audio analysis approach.

## Quirks of the desktop app

 - we have not gotten the application to feature full-screen resolution for the day of the presentation which is admittedly a bit embarassing, We just have not gotten around to that in due time.
 - No play-along music for the lessons, it is hard to keep with the track in the lessons.
